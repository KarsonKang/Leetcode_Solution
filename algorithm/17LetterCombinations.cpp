#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class Solution{
private:
    /*
    使用哈希表存储每个数字对应的所有可能的字母，然后进行回溯操作
    回溯过程中维护一个字符串，表示已有的字母序列，每次取电话号码的一位数字
    从哈希表中获取该数字对应的所有可能的字母，并将其中的一个字母插入到已有的字母的后面
    之后继续处理电话号码的后一位数字，直到处理完电话号中的所有数字，得到一个完整的字母排列
    然后进行回溯操作，遍历其余的字母排列

    回溯算法用于寻找所有的可行解，如果发现一个解不可行，则会立刻舍弃。

    **注：当出现所有组合的字眼时，要想到使用回溯。
    */
    map<char, string> numberMap = {
        //首先制作一个对应的哈希表
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };

public:
    vector<string> letterCombinations(string digits){
        vector<string> combinations;        //返回的最终结果
        string combination;                 //字母的组合
        if(digits.empty()){
            return combinations;            //特殊情况，输入为空时的输出。
        }
        backTrack(combinations, numberMap, digits, 0, combination);
        return combinations;
    }

    /*利用了递归的思想*/
    void backTrack(vector<string>& combinations, const map<char, string>& numberMap, const string& digits, int index, string& combination){
        if(index == digits.length()){
            combinations.push_back(combination);    //当完成一个字符串的遍历后，将
        }
        else{
            char digit = digits[index];     //从输入中获取号码
            const string& letters = numberMap.at(digit);//获取哈希表中对应号码的字符串
            for(const char& letter : letters){
                combination.push_back(letter);          //将对应号码字符串的每一个字符，插入输出结果的后面
                backTrack(combinations, numberMap, digits, index + 1, combination);//利用递归，将第二个，第三个。。。等数字对应的可能的字符一一插入
                combination.pop_back();                 //每次进行递归之后，都要先将插入的字符删除，在进行新的一轮循环
            }
        }
    }
};