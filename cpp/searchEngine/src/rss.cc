#include "../include/offline/Configuration.hh"
#include "tinyxml2.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <vector>
#include <filesystem>

using std::cin, std::cout, std::endl, std::string, std::istringstream;
using std::ofstream, std::vector;
using std::vector;

struct RssItem
{
    string title;
    string link;
    string description;
    // string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss(const string &filename);
    void dump(const string&, size_t &);

private:
    void parseAndPrintChannelContent(tinyxml2::XMLElement*);
    void removeHtml(RssItem &);
private:
    vector<RssItem> _rss;
};

RssReader::RssReader() {}

void RssReader::parseRss(const string &filename)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file." << std::endl;
        return;
    }
    tinyxml2::XMLElement* channel = doc.FirstChildElement("rss")->FirstChildElement("channel");
    if (!channel) {
        std::cerr << "No channel element found." << std::endl;
        return ;
    }
    parseAndPrintChannelContent(channel);
}
void RssReader::dump(const string& filename, size_t &index)
{
    ofstream ofs(filename, std::ios::app);
    for (int i = 0; i < _rss.size(); i++) {
        if(_rss[i].title.empty() || _rss[i].link.empty() || _rss[i].description.empty()){
            continue;
        }
        ofs << "<Webpage>" << endl;
        ofs << "   <docid>" << index++ << "</docid>" << endl;
        ofs << "   <title>" << _rss[i].title << "</title>" << endl;
        ofs << "   <link>" << _rss[i].link << "</link>" << endl;
        ofs << "   <description>" << _rss[i].description << "</description>" << endl;
        // ofs << "   <content>" << _rss[i].content << "</content>" << endl;
        ofs << "</Webpage>" << endl;
    }
    ofs.close();
}

void RssReader::parseAndPrintChannelContent(tinyxml2::XMLElement* channel)
{
    RssItem rssItem;
    tinyxml2::XMLElement* item = channel->FirstChildElement("item");
    while (item) {
        rssItem.title = item->FirstChildElement("title")->GetText();
        rssItem.link = item->FirstChildElement("link")->GetText();
        vector<string> descriptions = {"description", "content", "content:encoded"};
        for(const auto & description : descriptions){
            if(item->FirstChildElement(description.c_str())){
                rssItem.description = item->FirstChildElement(description.c_str())->GetText();
                break;
            }
        }
        removeHtml(rssItem);
        _rss.emplace_back(rssItem);
        item = item->NextSiblingElement("item");
    }
}

void RssReader::removeHtml(RssItem & rssItem){
    std::regex pattern("<[^>]+>");
    rssItem.title = std::regex_replace(rssItem.title, pattern, "");
    rssItem.link = std::regex_replace(rssItem.link, pattern, "");
    rssItem.description = std::regex_replace(rssItem.description, pattern, "");
    // rssItem.content = std::regex_replace(rssItem.content, pattern, "");
}

int main(int argc, char* argv[])
{   
    Configuration config;
    string yuliao_path = config.getparameter("webpage_yuliao");
    string new_ripe_page = config.getparameter("new_ripe_page");
    vector<string> xml_files;
    // c++ 17 写法
    for (const auto& entry : std::filesystem::directory_iterator(yuliao_path)) {
        xml_files.emplace_back(yuliao_path + "/" + entry.path().filename().string());
    }
    size_t index = 0;
    // RssReader rssReader;
    // rssReader.parseRss("/home/lja/user/CppLearning/cpp/searchEngine/resources/模块二/人民网语料/book.xml");
    // rssReader.dump(new_ripe_page, index);
    for(const auto & filename : xml_files){
        RssReader rssReader;
        rssReader.parseRss(filename);
        rssReader.dump(new_ripe_page, index);
    }
    std::cout << "new_ripe_page 已存储在 " << new_ripe_page << std::endl; 
    return 0;
}