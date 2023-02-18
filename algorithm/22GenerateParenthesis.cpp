#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

class Solution{
public:
    //找出n个括号时的，所有有效组合
    //方法一：暴力法，枚举出所有组合，从中筛选出有效的组合
    bool isValid(string& str){
        //判断字符串是否有效
        int i = 0;
        for(char ch : str){
            if(ch == '('){
                i++;
            }
            else{
                i--;
            }
            if(i < 0){
                return false;
            }
        }
        return i == 0;
    }

    void generate_all(string& current, int num, vector<string>& result){
        //利用递归法，找出所有组合
        if(num == current.size()){
            //当数量到达最大时，判断当前括号组合是否有效
            if(isValid(current)){
                result.push_back(current);
            }
            return;
        }
        
        current += '(';
        generate_all(current, num, result);
        current.pop_back();
        
        current += ')';
        generate_all(current, num, result);
        current.pop_back();
    }
    vector<string> generateParenthesis1(int n){
        vector<string> result;
        string current;
        generate_all(current, n * 2, result);   //注意，这里n要乘2
        return result;
    }
};

class Solution2{
public:
    //方法二：回溯法，思想与17题相似
    void backTrack(string& str, int n, vector<string>& result, int left, int right){
        if(str.size() == n * 2){
            result.push_back(str);
            return;
        }

        if(left < n){
            str += '(';
            backTrack(str, n, result, left + 1, right);
            str.pop_back();
        }
        if(right < left){
            str += ')';
            backTrack(str, n, result, left, right + 1);
            str.pop_back();
        }
    }
    vector<string> generateParenthesis(int n){
        string current;
        vector<string> result;
        backTrack(current, n, result, 0, 0);
        return result;
    }
};