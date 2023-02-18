#include <iostream>
#include <string>

using namespace std;

/*方法一：模拟，罗马数字是唯一表示法
通过建立一个数值-符号的列表，将数值从大到小排列。遍历列表中的每个数值，从num中不断减去
value，直到num小于value，然后遍历下一个数值-符号对，当num减为0时，跳出循环
这种方法也是利用了贪心的思想
贪心法则，每次尽量使用最大的数来表示，我们使用哈希表从大到小的顺序，
遍历哈希表，直到全部输入
*/
const pair<int, string> valueSymbols[] = {  //哈希表构建
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"},
};

class Solution{
public:
    string intToRoman(int num){
        string roman;
        for(const auto &[value, symbol] : valueSymbols){    //灵活使用auto，遍历valueSymbol哈希表
            while(num >= value){
                num -= value;
                roman += symbol;
            }
            if(num == 0){
                break;
            }
        }
        return roman;
    }
};

/*方法二：硬编码数字
于方法一类似，重新进行编码
*/
const string thousands[] = {"", "M", "MM", "MMM"};
const string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

class Solution2{
public:
    string intToRoman(int num){
        return thousands[num/1000] + hundreds[(num % 1000) / 100] + tens[num % 100 / 10] + ones[num % 10];
    }
};
/*方法三：贪心
贪心法则，每次尽量使用最大的数来表示，我们使用哈希表从大到小的顺序，
遍历哈希表，直到全部输入
*/


int main(){
    int num = 1994;
    Solution s1;
    Solution2 s2;
    cout << s1.intToRoman(num) << endl;
    cout << s2.intToRoman(num);
    return 0;
}