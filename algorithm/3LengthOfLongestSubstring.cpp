#include <iostream>
#include <map>

using namespace std;


class Solution{             
public:

    int lengthOfLongestSubstring1(string s){
                                                //利用hashmap优化滑动窗口的方法，时间复杂度：O(n) 空间复杂度：O(n)
        int ans = 0;                            //记录最长子串的长度
        int start = 0;                          //滑动窗口的起始位置
        int end = 0;                            //滑动窗口的末尾位置
        map<char, int> mp;                      //hashmap，记录组字符串起始字符（char）的起始位置（int）
        for(int i = 0; i < s.size(); i++){
            if(!mp.count(s[i])){                        //当map中没有出现遍历到的字符时
                mp.insert(make_pair(s[i], i + 1));      //记录字符的位置
                end = i + 1;                            //记录子串结尾的位置
            }
            else{                                       //当map中出现了遍历到的字符时
                start = (mp[s[i]] > start) ? mp[s[i]] : start;  //判断重复出现的字符的位置，大于窗口起始值start时，将start更新
                mp[s[i]] = i + 1;                               //记录对应字符新的起始值
                end = i + 1;                                    //记录末尾值
            }
            ans = (end - start > ans) ? (end - start) : ans;    //记录最长子字符串的长度
        }
        return ans;
    }


};


int main(){
    Solution s1;
    string s = "abcdede";
    cout << s1.lengthOfLongestSubstring1(s);
    return 0;
}