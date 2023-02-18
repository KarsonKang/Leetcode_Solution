#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

class Solution{
public:
    //使用了滑动窗口 + 哈希表的方法
    vector<int> findSubstring(string s, vector<string>& words){
        //首先设置结果变量，存放结果
        vector<int> ans;
        //如果输入字符串为空，则直接返回空的结果。
        if(s.empty()) return ans;

        //用n记录字符串s的长度
        int n = s.length();
        //用m记录单词组的单词个数
        int m = words.size();
        //w记录每个单词的长度（words中每个单词的长度都相同）
        int w = words[0].length();

        //利用一个哈希表记录每个单词出现的次数
        unordered_map<string, int> total;
        for(int i = 0; i < m; i++){
            //在哈希表中记录words中的每个单词
            total[words[i]]++;
        }

        for(int i = 0; i < w; i++){
            //利用新的哈希表记录滑动窗口中出现的字符串的次数
            unordered_map<string, int> window;
            //利用一个变量记录窗口中有效单词的个数
            int cnt = 0;

            //从下标i开始，进行滑动窗口的移动
            for(int j = i; j + w <= n; j += w){
                //窗口右移，记录下被移除窗口的单词
                if(j - i >= m * w){
                    string word = s.substr(j - m * w, w);
                    window[word]--;
                    //从window中删除单词后，如果total中也存在这个单词，则删除的是一个有效单词，有效单词数减一
                    if(window[word] < total[word]){
                        cnt--;
                    }
                }
                
                string word = s.substr(j, w);
                window[word]++;
                //判断窗口中的单词是否是有效单词
                if(window[word] <= total[word]){
                    cnt++;
                }
                
                //当有效单词数与words中的数量相同，则此时窗口中的子串就是一个有效的子串
                if(cnt == m){
                    ans.push_back(j - (m - 1) * w);
                }
            }
        }

        return ans;
    }
};