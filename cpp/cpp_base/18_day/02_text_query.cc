#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <memory>
#include <cctype>

using std::cin, std::cout, std::endl;
using std::string, std::vector, std::map, std::set;
using std::shared_ptr;
using std::ifstream, std::ofstream, std::istringstream, std::ostringstream;
using line_no = vector<string>::size_type;
using std::ostream;
using std::make_shared;

class QueryResult;
class TextQuery{
public:
    TextQuery(std::ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
    static void processWord(string&);
};

TextQuery::TextQuery(ifstream& ifs) : file(new vector<string>){
    string text;
    while(std::getline(ifs, text)){
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while(line >> word){
            processWord(word);
            if(word.size() == 0){
                continue;
            }
            auto& lines = wm[word];
            if(!lines){
                lines.reset(new set<line_no>);
            }
            lines->insert(n);
        }
    }
}

void TextQuery::processWord(string & word){

    for(char & c : word){
        if(isupper(c)){
            // c = tolower(c);
            c ^= ' ';
        }
    }
    auto removeComparator = [](char c){
        return !std::isalpha(c);
    };

    word.erase(std::remove_if(word.begin(), word.end(), removeComparator), word.end());
}

class QueryResult{
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) 
    : sought(s)
    , lines(p)
    , file(f) {}
    auto begin() const { return lines->begin(); }
    auto end() const { return lines->end(); }
    auto get_file() const { return file; }
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};

QueryResult TextQuery::query(const string& s) const{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(s);
    if(loc == wm.end()){
        return QueryResult(s, nodata, file);
    }
    else{
        return QueryResult(s, loc->second, file);
    }
}

ostream& print(ostream& os, const QueryResult& qr){
    os << "\t" << qr.sought << " occurs " << qr.lines->size() << " times" << endl;
    for(auto num : *qr.lines){
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
    }
    return os;
}

class Query_base{
friend class Query;
protected:
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

class Query{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string &);
    QueryResult eval(const TextQuery& t) const{
        return q->eval(t);
    }
    string rep() const{
        return q->rep();
    }

private:
    Query(shared_ptr<Query_base> query) : q(query) {}
    shared_ptr<Query_base> q;
};

ostream &operator<<(ostream& os, const Query& query){
    return os << query.rep();
}

class WordQuery : public Query_base{
    friend class Query;
    WordQuery(const string& s) : query_word(s) {}
    QueryResult eval(const TextQuery& t) const{
        return t.query(query_word);
    }
    string rep() const{
        return query_word;
    }
    string query_word;
};

inline Query::Query(const string &s) : q(new WordQuery(s)) {}

class NotQuery : public Query_base{
    friend Query operator~(const Query&);
    NotQuery(const Query& q) : query(q) {}
    string rep() const{
        return "~(" + query.rep() + ")";
    }
    QueryResult eval(const TextQuery&) const;
    Query query;
};

inline Query operator~(const Query& operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query& l, const Query& r, string s) : lhs(l), rhs(r), opSym(s) {}
    string rep() const{
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }
    Query lhs, rhs;
    string opSym;
};

class AndQuery : public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query& left, const Query& right) : BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& left, const Query& right) : BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text) const{
    auto result = query.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    auto beg = result.begin(), end = result.end();
    for(size_t n = 0; n != result.get_file()->size(); ++n){
        if(beg == end || *beg != n){
            ret_lines->insert(n);
        }else if (beg != end) {
            ++beg;
        }
    }
    return QueryResult(rep(),ret_lines, result.get_file());
}

void test1(){
    Query q = Query("fiery") & Query("bird");
    cout << q << endl;
}

void test2(){
    string file = "china_daily.txt";
    ifstream ifs(file);
    TextQuery tq(ifs);
    // Query q = ~Query("link");
    Query q = Query("link") & Query("china") | Query("the");
    cout << "\tExecuting Query for: " << q << endl;
    print(cout, q.eval(tq));
}

int main(void){
    test2();
    return 0;
}