#include<iostream>
#include<string>
#include<map>

using namespace std;

class Solution{
public:
    /*方法一：暴力判断法*/
    int romanToInt(string s){
        int num = 0;
        int n = s.length();
        for(int i = 0; i < n; i++){
            if(s[i] == 'M'){
                num += 1000;
            }
            else if(s[i] == 'D'){
                num += 500;
            }
            else if(s[i] == 'C'){   //判断CM，CD出现的情况
                if(s[i+1] == 'M' && i+1 < n){
                    num += 900;
                    i++;
                }
                else if(s[i+1] == 'D' && i+1 < n){
                    num += 400;
                    i++;
                }
                else{
                    num += 100;
                }
            }
            else if(s[i] == 'L'){
                num += 50;
            }
            else if(s[i] == 'X'){   //判断XC，XL出现的情况
                if(s[i+1] == 'C' && i+1 < n){
                    num += 90;
                    i++;
                }
                else if(s[i+1] == 'L' && i+1 < n){
                    num += 40;
                    i++;
                }
                else{
                    num += 10;
                }
            }
            else if(s[i] == 'V'){
                num += 5;
            }
            else if(s[i] == 'I'){   ////判断IV，IX出现的情况
                if(s[i+1] == 'X' && i+1 < n){
                    num += 9;
                    i++;
                }
                else if(s[i+1] == 'V' && i+1 < n){
                    num += 4;
                    i++;
                }
                else{
                    num += 1;
                }
            }
        }
        return num;
    }

    /*方法二：模拟法，从右边开始遍历，当出现s[i] < s[i + 1]的情况时，例如IX，可视为 -1 + 10 = 9*/
private:
    map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

public:
    int romanToInt2(string s){
        int num = 0;
        int n = s.length();
        for(int i = 0; i < n; i++){
            if(i < n - 1 && symbolValues[s[i]] < symbolValues[s[i + 1]]){
                num -= symbolValues[s[i]];
            }
            else{
                num += symbolValues[s[i]];
            }
            cout << symbolValues[s[i]] << endl;
            cout << num << endl;
        }
        return num;
    }
};

int main(){
    Solution s2;
    string s("LVIII");
    cout << s2.romanToInt2(s);
    return 0;
}