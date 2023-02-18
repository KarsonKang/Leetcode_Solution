#include<iostream>

using namespace std;

class Solution{
    /*
    个人思路：将数字反转，与原数字进行比较
    */

public:
    bool isPalindrome(int x){
        if(x < 0){
            return false;   //判断如果小于0，则直接输出false
        }
        int x1 = x;
        int ans = 0;
        int temp = 0;
        while(x != 0){
            if(ans < INT_MIN / 10 || ans > INT_MAX / 10){   
                return false;   //判断反转后的数字是否越界，如果越界一定不是回文数
            }
            
            temp = x % 10;          //数字反转过程1
            x /= 10;                //数字反转过程2
            ans = ans * 10 + temp;  //数字反转过程3
        }
        if (ans == x1)              //判断反转之后的数字与原数是否相等
            return true;
        else
            return false;
    }

    /*方法二：反转一半数字
    用时更快
    比自己的写法简单
    */
    bool isPalindrome2(int x){
        if(x < 0 || (x % 10 == 0 && x != 0)){
            return false;
        }

        int reverseNum = 0;
        while(x > reverseNum){
            reverseNum = reverseNum * 10 + x % 10;
            x /= 10; 
        }

        return reverseNum == x || reverseNum / 10 == x;
    }
};

int main(){
    Solution s;
    int x = 123321;
    if(s.isPalindrome(x))
        cout << "1" << endl;
    else
        cout << "0" << endl;
}