#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Solution{
public:
    /*方法一：动态规划（官方算法，很巧妙，也很复杂） ***困难难度***
    这道题难度为困难，题目中的匹配是一个逐步匹配的过程：我们每次从字符串p中取出一个字符或
    或字符+星号的组合，并在s中进行匹配。对于p中一个字符而言，只能在s中匹配一个字符，匹配
    方法具有唯一性；对于p中字符+星号的组合，可以在s中匹配任意个相同字符。

    用f[i][j]表示s的前i个字符和p中前j个字符是否能够匹配，在进行状态转移时，考虑p的第j个
    字符的匹配情况：
        如果p的第j个字符是字母或是 . 那么s中必须匹配一个相同的字母，判断函数如下
            当s[i] = p[j]时， f[i][j] = f[i - 1][j - 1];
            当s[i] != p[j]时，f[i][j] = false;
        如果p[j]是“ * ”星号，考虑字符 + 星号的组合在匹配过程中本质上只会出现两种情况
            匹配s末尾的一个字符，将这个字符丢掉后，依然可以匹配
            不匹配字符，直接将组合丢掉，不再进行匹配  判断函数如下
            当s[i] = p[j - 1]时，f[i][j] = f[i - 1][j] or f[i][j - 2]
            当s[i] != p[j - 1]时，f[i][j] = f[i][j - 2]
            **多思考这段代码的逻辑**
    
    细节：动态规划的边界值f[0][0] = true，因为两个空字符串可以相互匹配，最终的答案为f[m][n]
          m，n分别是字符串s，p的长度
    */
    bool isMatch(string s, string p){
        int m = s.length();
        int n = p.length();

        auto matchs = [&](int i, int j){    //c++11的lambda表达式，匿名函数，速度更快，写法简洁
            if(i == 0){
                return false;       //s空字符串与任何字母都不匹配
            }
            if(p[j - 1] == '.'){
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for(int i = 0; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(p[j - 1] == '*'){
                    f[i][j] |= f[i][j - 2];  //因为每次出现*时，都能保证*前面有可以匹配的字符，不用担心j-2会溢出
                    if(matchs(i, j - 1)){
                        f[i][j] |= f[i - 1][j]; 
                    }
                }
                else{
                    if(matchs(i, j)){
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        cout << f[0][1] << endl;
        return f[m][n];
    }

    /*方法二：
    dp[i][j]表示s的前i个是否与p的前j个匹配
    状态转移方程
        已经求出了dp[i-1][j-1]，已知s[i],p[j]，求dp[i][j]，有几种情况
            1. s[i] == p[j] : dp[i][j] = dp[i - 1][j - 1];
            2. p[j] == '.' : dp[i][j] = dp[i - 1][j - 1];
            3. p[j] == '*':
                这里是第一个很难想出的点**，如何区分*的几种情况，也需要分情况讨论，需要考虑*号前面的元素p[j-1]
                3.1 p[j - 1] != s[i] : dp[i][j] = dp[i][j - 2]
                    这是与前一个字符不匹配的情况，比如s=ab, p=abc*。遇到*时，向前看两个数，
                    发现s[i]的 ab 与p[j-2]的ab相匹配，因为c*可看做匹配了0次c，相当于去掉c*，所以是true
                3.2 p[j - 1] == s[i] or p[j - 1] == '.'时，这里是第二个很难想出来的点***
                    如何判断前面的字符是否匹配
                    3.2.1 s = ###b, p = ###b*时，如果dp[i][j] = dp[i][j - 1]，则匹配
                    3.2.2 s = ###b, p = ###b*时，如果dp[i][j] = dp[i - 1][j]，则匹配（相当与###与###b*匹配的话，###b也一定与###b*匹配）
                    3.2.3 s = ###, p = ###b*时，如果dp[i][j] = dp[i][j - 2],则匹配
    */
    bool isMatch2(string s, string p){
        s = " " + s;
        p = " " + p;        //避免了s为空字符串时的特殊情况
        
        int m = s.size();
        int n = p.size();

        bool dp[m+1][n+1];
        memset(dp, false, sizeof(dp));      //memset函数，需要cstring头文件，将数组赋值为false
        dp[0][0] = true;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(s[i-1] == p[j-1] || p[j-1] == '.'){      //方法二的1,2判断
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if(p[j-1] == '*'){                     //方法二的3判断
                    if(s[i-1] != p[j-2] && p[j-2] != '.'){  
                        dp[i][j] = dp[i][j-2];              //3.1的判断
                        cout << dp[i][j] << endl;
                    }
                    else{
                        dp[i][j] = dp[i][j-1] || dp[i-1][j] || dp[i][j-2];  //3.2的判断
                    }
                }
            }
        }
        //cout << dp[2][2];
        return dp[m][n];
    }

};

int main(){
    Solution s1;
    string s("ad");
    string p(".*c");
    if(s1.isMatch2(s, p)){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }
    return 0;
}