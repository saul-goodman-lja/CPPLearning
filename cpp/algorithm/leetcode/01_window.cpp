#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int wordSize = words[0].size();  // 每个单词的长度
        int numWords = words.size();     // 单词的数量
        int totalSize = numWords * wordSize;  // 所有单词连接起来的总长度
        vector<int> result;  // 存储结果的向量

        // 如果源字符串的长度小于总长度，直接返回空结果
        if (s.size() < totalSize) return result;

        // 使用unordered_map统计每个单词的出现次数
        unordered_map<string, int> wordCount;
        for (const string& word : words) {
            wordCount[word]++;
        }

        // 外层循环：尝试每个可能的起始位置，范围是0到wordSize-1
        for (int i = 0; i < wordSize; ++i) {
            int start = i;  // 当前窗口的起始位置
            unordered_map<string, int> seen;  // 记录当前窗口内各个单词的出现次数
            int matched = 0;  // 记录已经匹配的单词数量

            // 内层循环：从当前起始位置开始，每次移动wordSize长度
            for (int j = i; j <= s.size() - wordSize; j += wordSize) {
                string word = s.substr(j, wordSize);  // 提取当前窗口中的单词

                // 如果当前单词在words列表中
                if (wordCount.find(word) != wordCount.end()) {
                    seen[word]++;  // 增加当前单词在seen中的计数
                    matched++;  // 增加匹配的单词数量

                    // 如果seen中某个单词的次数超过了wordCount中的次数
                    while (seen[word] > wordCount[word]) {
                        string leftWord = s.substr(start, wordSize);  // 提取窗口最左边的单词
                        seen[leftWord]--;  // 减少左边单词的计数
                        start += wordSize;  // 窗口右移一个单词长度
                        matched--;  // 减少匹配的单词数量
                    }

                    // 如果匹配的单词数量等于单词列表中的单词数量
                    if (matched == numWords) {
                        result.push_back(start);  // 将当前窗口的起始位置加入结果
                        string leftWord = s.substr(start, wordSize);  // 提取窗口最左边的单词
                        seen[leftWord]--;  // 减少左边单词的计数
                        start += wordSize;  // 窗口右移一个单词长度
                        matched--;  // 减少匹配的单词数量
                    }
                } else {
                    // 如果当前单词不在words列表中，重置窗口
                    seen.clear();
                    matched = 0;
                    start = j + wordSize;  // 窗口右移到下一个可能的起始位置
                }
            }
        }

        return result;  // 返回结果
    }
};

int main() {
    Solution solution;
    string s = "barfoothefoobarman";
    vector<string> words = {"foo", "bar"};
    vector<int> result = solution.findSubstring(s, words);
    for (int index : result) {
        cout << index << " ";
    }
    cout << endl;
    return 0;
}
