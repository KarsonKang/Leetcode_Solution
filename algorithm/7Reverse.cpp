#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Solution{
public:
    int reverse(int x){
        /*自己写的方法，漏洞较多，且没有考虑溢出和负数的情况
        思路是将每个位上的数字取出来，之后反转输出
        */
        vector<int> v;
        for(int i = 1; x / i != 0; i *= 10){
            int temp = (x % (10 * i)) / i;
            v.push_back(temp);
        }
        int ans = 0;
        int n = v.size();
        for(int i = 0; i < n; i++){
            int j = pow(10, (n - i - 1));
            cout << j << endl;
            //cout << v[i] << endl;
            ans += v[i] * j;
            //cout << ans << endl;
        }
        return ans;
    }

    /*答案给出的更简单的方法
    在没有辅助栈或数组的帮助下，用纯数组的方式弹出和推入数字
        //弹出x末尾的数字digit
        digit = x % 10；
        x /= 10

        //将数字digit推入到rev末尾
        rev = rev * 10 + digit
    实现了弹出推入之后，在此之前需要判断反转之后的数字是否超过了有符号整数的范围
    因此，需要判断  INT_MIN <= rev * 10 + digit <= INT_MAX 是否成立
    */

    int reverse2(int x){
        int rev = 0;
        while(x != 0){
            if(rev < INT_MIN / 10 || rev > INT_MAX / 10){   //判断rev的范围，溢出时返回0
                return 0;                                   //rev不可能小于INT_MIN,因此采用INT_MIN/10与rev进行比较
            }
            int digit = x % 10;         //在没有数据栈帮助下，实现弹出推入的代码
            x /= 10;

            rev = rev * 10 + digit;
        }
        return rev;
    }
};

int main(){ 
    int x = 152258;
    Solution s1;
    cout << s1.reverse2(x) << endl;
}

