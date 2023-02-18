#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

class Solution{
public:
    int myAtoi(string s){
        /*字符串转化问题，在这首先要进行模式识别，一旦涉及到整数的运算，一定要注意是否会溢出
        本题中，可能产生溢出的步骤在于将数字推入，乘以10和累加操作时可能导致溢出，在这里我们需要
        进行第六题一样的判断处理，将INT_MAX/10，来判断某个数乘以10之后是否会溢出

        ***这道题比较脑瘫，重点学习官方给出的方法一，使用自动机***

        自己的方法：
        */
        int sign = 1;
        long ans = 0;
        int n = s.length();
        bool start = false;
        for(int i = 0; i < n; i++){
            if(ans && !isdigit(s[i])){
                return sign * ans;
            }

            else if(isspace(s[i])){
                if(start)
                    return 0;
                else
                    continue;
            }
            else if(s[i] == '+' || s[i] == '-'){
                sign = s[i] == '+' ? 1 : -1;
                start = true;
            }

            else if(isdigit(s[i])){
                ans = ans * 10 + int(s[i] - '0');
                cout << ans << endl;
                if(sign * ans >= INT_MAX){
                    return INT_MAX;
                }
                else if(sign * ans <= INT_MIN){
                    return INT_MIN;
                }
            }
            else{
                return 0;
            }
        }
        return ans * sign;
    }
};


    /*方法一：自动机
    为了防止写出极其臃肿的代码，为了有条理地分析每个输入的字符的处理方法，使用了自动机这个概念
    程序在每个时刻有一个状态 s ，每次从序列中输出一个字符 c ，根据字符 c 转移到下一个状态 s'。
    
    这个方法主要使用了自动机这个概念，可以套用在许多其他的问题中

    */
class Automaton{
    string state = "start";
    map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };
    //将8t表格中的内容抄进代码，后续只要转移到下一个状态时为 in_number 时，更新输出的数字

    int get_col(char c){       //
        if(isspace(c))
            return 0;
        else if(c == '+' || c == '-')
            return 1;
        else if(isdigit(c))
            return 2;
        else
            return 3;
    }

public:
    int sign = 1;
    long ans = 0;
    void get(char c){
        state = table[state][get_col(c)];   //获取当前的状态；
        if(state == "in_number"){
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans , (long)INT_MAX) : min(ans, -(long)INT_MIN);
        }
        else if(state == "signed"){
            sign = c == '+' ? 1 : -1;
        }
        
    }
};

class Solution2{
public:
    int myAtoi(string s){
        Automaton automaton;
        for(char c : s){
            automaton.get(c);
        }
        return automaton.ans * automaton.sign;
    }
};
    
int main(){
    Solution2 s1;
    string s("words and 987");
    cout << s1.myAtoi(s) << endl;
}