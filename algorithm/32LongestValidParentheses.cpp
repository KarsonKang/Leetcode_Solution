#include<iostream>
#include<string>
#include<stack>

using namespace std;

class Solution{
public:
    int longestValidParentheses(string s){
        stack<int> stk;
        int n = s.size();
        int cnt = 0;
        int max = 0;

        //这里使用栈的思路发生了变化，为了方便输出最长有效字符的长度
        //放入栈的是字符对应的下标，此时方便通过坐标的差值，计算最长有效子串
        //先将-1压入栈的目的是为了更好地计算长度
        stk.push(-1);
        for(int i = 0; i < n; i++){
            if(s[i] == ')'){
                if(stk.top() != -1 && s[stk.top()] =='('){
                    stk.pop();
                    //计算此时的有效字符串的长度
                    cnt = i - stk.top();
                }
                else{
                    //当出现‘)’，但没有匹配时，当前有效字符串一定结束
                    stk.push(i);
                    max = cnt > max ? cnt : max;
                    cnt = 0;
                }
            }
            else{
                stk.push(i);
            }
            max = cnt > max ? cnt : max;
        }
        
        return max;
    }
};
