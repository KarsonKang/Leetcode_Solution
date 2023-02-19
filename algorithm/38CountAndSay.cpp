#include <iostream>
#include <string>

using namespace std;

/*
注意点1:递归

注意点2:双指针，分别记录出现的次数和出现的数字

    i                   i = 1
    1 1 1 2 2 1
        j               j = 3

    及有 3 个 1，所以在ans中加入“31”。
*/



class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";

        string str = countAndSay(n - 1);
        string ans;
        
        //使用双指针分别记录数字，和出现的次数
        for(int i = 0, j = 0; i < str.length(); i++){
            while(j < str.length() && str[i] == str[j]){
                j++;
            }
            //ans += (char)(j - i) + str[i];       　*注意*这里不能使用(char)将数字转型，这会使两个char型变量相加，得到另一个char型，无法获得string型输出。
            ans += to_string(j - i) + str[i];
            i = j - 1;
        }
        return ans;
    }
};