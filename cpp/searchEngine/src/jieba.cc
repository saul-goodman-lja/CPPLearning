#include "simhash/cppjieba/Jieba.hpp"
#include "simhash/Simhasher.hpp"
#include <iostream>
#include <string>

using namespace std;

const char* const JIEBA_DICT_PATH = "dict/jieba.dict.utf8";
const char* const HMM_MODEL_PATH = "dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "dict/user.dict.utf8";

int main() {
    cppjieba::Jieba jieba(JIEBA_DICT_PATH, HMM_MODEL_PATH, USER_DICT_PATH);
    string s1 = "我来到北京清华大学";
    vector<string> words;
    jieba.Cut(s1, words, true);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;


    return 0;
}
