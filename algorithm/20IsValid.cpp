#include<iostream>
#include<string>
#include<stack>
#include<map>

using namespace std;

class Solution{
public:
    //方法一：利用栈，直接判断
    bool isValid(string s){
        stack<char> stk;
        int n = s.length();
        stk.push(' ');  //防止第一个字符便是']','}',')'时，出现stk.top()为空的情况
        for(int i = 0; i < n; i++){
            if(s[i] == '(' || s[i] == '{' || s[i] == '['){
                stk.push(s[i]);
            }
            else if(s[i] == ')'){
                if(stk.top() == '('){
                    stk.pop();
                }
                else{
                    return false;
                }
            }
            else if(s[i] == '}'){
                if(stk.top() == '{'){
                    stk.pop();
                }
                else{
                    return false;
                }
            }
            else{
                if(stk.top() == '['){
                    stk.pop();
                }
                else{
                    return false;
                }
            }
        }
        if(stk.top() == ' '){
            return true;
        }
        return false;
    }

    //方法二：利用map，和栈，进行判断，提高运行速度，减少判断逻辑
    bool isValid2(string s){
        stack<char> stk;
        int n = s.size();
        if(n % 2 == 1){
            return false;
        }

        map<char, char> mp = {      //利用map，可以加快判断时间
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        for(char ch : s){
            if(mp.count(ch)){       //如果字符为后括号
                if(stk.empty() || stk.top() != mp[ch]){
                    return false;
                }
                stk.pop();
            }
            else{
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};
