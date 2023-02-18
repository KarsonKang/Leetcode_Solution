#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution{
public:
    string longestPalindrome1(string s){
        /*方法一：动态规划
        对于一个子串，如果他是回文串而且长度大于2，那么将收尾两个字母去掉后，依然是回文串
        用P(i, j)表示字符串S的第i到第j个字母组成的串是否是回文串即，
        当P(i,j) = true时，子串Si~Sj是回文串
        当P(i,j) = false时，其他情况(S[i,j]本身不是回文串，或i > j,S[i,j]本身不合法)
        动态规划的状态转移方程为
            P(i,j) = P(i + 1, j + 1) ^ (Si == Sj)
        也就是说只有当S[i + 1: j - 1]是回文串，且Si和Sj字母相同时，S[i:j]才会是回文串

        当一个子串长度小于等于2时，长度为1的子串一定是回文串，长度为2的子串如果两个字符相同则是回文串
            P(i,i) = true
            P(i, i + 1) = (Si == S(i + 1) )
        最终答案为P(i,j) = true中j - i + 1的最大值。
        在状态转移方程中，我们从长度较短的字符串向长度较长的字符串进行转移，因此要注意动态规划的循环顺序
        */
        int sLength = s.size();
        if(sLength < 2){
            return s;
        }
        
        int begin = 0;          //记录最长子串的开始下标
        int maxLength = 1;      //记录最长子串的长度

        vector<vector<bool>> dp(sLength, vector<bool>(sLength));  //二维数组的声明*
        //在dp[i][j]中表示字符串S[i:j]是否是回文串
        for(int i = 0; i < sLength; i++){
            //初始化，所有长度为1的字符串都是回文串
            dp[i][i] = true;
        }

        //开始递推
        for(int L = 2; L <= sLength; L++){
            //遍历所有长度为L的子串，记录是回文串的子串
            for(int i = 0; i < sLength; i++){
                int j =  i + L - 1;         //记录子串的末尾下标
                if(j > sLength - 1){        //当超出字符串的长度时，结束本轮循环
                    break;
                }

                if(s[i] != s[j]){           //不相等时，不是回文串
                    dp[i][j] = false;
                }
                else{
                    if(j - i == 1){         //当子串长度为2，且Si = Sj时，是回文串
                        dp[i][j] = true;
                    }
                    else{
                        dp[i][j] = dp[i + 1][j - 1];    //当长度不为2时，S[i+1:j-1]为回文串，且s[i]=s[j]时，S[i:j]是回文串
                    }
                }

                if(dp[i][j] && j - i + 1 > maxLength){
                    //记录回文串的起始下标和长度
                    begin = i;
                    maxLength = L;
                }
            }
        }
        return s.substr(begin, maxLength);      //使用substr(i, length)函数获取子串；i为起始下标
    }


    string longestPalindrome2(string s){
        /*方法二：中心扩展算法，这种方法用时更短，内存消耗更少，推荐
        方法一种的状态转移方程为：
            P(i, i) = true;
            P(i, i+1) = (Si == S(i + 1))
            P(i, j) = P(i + 1, j - 1) ^ (Si == Sj)
        其中的状态转移链为：
        P(i,j) ← P(i+1,j−1) ← P(i+2,j−2) ←⋯← 某一边界情况
        可以发现所有的状态在转移的时候的可能性是唯一的。
        我们可以从每一种边界情况开始拓展，可以得出所有的状态对应的答案
        方法二的本质就是，枚举所有得回文中心并尝试扩展，直到无法扩展为止。
        在所有长度中求出最大值，和最大值时的回文中心。
        */
        int begin = 0;                      //记录回文串起始下标
        int maxLengh = 1;                   //记录最长回文串的长度
        for(int i = 0; i < s.size(); i++){
            int length1 = expandAroundCenter(s, i, i);          //aba型回文串的长度计算
            int length2 = expandAroundCenter(s, i, i + 1);      //abba型回文串的长度计算
            int length = max(length1, length2);                 //获取跟大的长度
            if(length > maxLengh){                              //更新最大长度，和回文串起始下标
                maxLengh = length;
                if (length1 == length)
                {
                    begin = i - maxLengh / 2;
                }
                else{
                    begin = i - maxLengh / 2 + 1;
                }
            }
        }
        return s.substr(begin, maxLengh);

    }
    string longestPalindrome3(string s){
        //使用expandAroundCenter2时的另一种写法
        int begin = 0, end = 0;
        for(int i = 0; i < s.size(); i++){
            auto [left1, right1] = expandAroundCenter2(s, i, i);
            auto [left2, right2] = expandAroundCenter2(s, i, i + 1);
            //在这里注意auto的用法，第一次见到
            /*
            auto是c++程序设计语言的关键字。用于两种情况
            （1）声明变量时根据初始化表达式自动推断该变量的类型
            （2）声明函数时函数返回值的占位符
            */
           //在声明变量时，根据变量的初始值类型自动选择匹配的类型
            if(right1 - left1 > end - begin){
                begin = left1;
                end = right1;
            }
            if(right2 - left2 > end - begin){
                begin = left2;
                end = right2;
            }
        }
        return s.substr(begin, end - begin + 1);
    }

    int expandAroundCenter(const string& s, int left, int right){
        //计算能扩展出的最大长度
        while(left >= 0 && right < s.size() && s[left] == s[right]){
            left--;     
            right++;
        }
        return right - left - 1;    //注意，当不能扩展时，此时的s[left] != s[right]
                                    //返回的回文数长度应该为 (right - 1) - (left + 1) + 1
    }

    pair<int, int> expandAroundCenter2(const string& s, int left, int right){
        //计算扩展的另一种写法
        while(left >= 0 && right < s.size() && s[left] == s[right]){
            left--;     
            right++;
        }
        return {left + 1, right - 1};   //注意pair返回值的写法。
    }

};

int main(){
    string s = "abbbcde";
    Solution s1;
    cout << s1.longestPalindrome3(s) << endl;
    return 0;
}
