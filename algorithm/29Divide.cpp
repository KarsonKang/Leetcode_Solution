#include<iostream>

using namespace std;

class Solution{
public:
    //方法一：除法可以认为是在做减法，例如20 / 3，可以认为是20减了6次3，剩下的2小于被除数3，所以作为余数
    //也可以认为是20 - 12*1 - 6*1 - 3*0 = 2，得到的结果是 4 + 2 = 6
    //也可以利用这种方法进行计算，每次使用 << 或 >> 平移符号时，相当于*2 或 /2
    int divide(int dividend, int divisor){
        //考虑被除数为最小值的情况
        if(dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        
        bool sign = true;

        //考虑符号对于结果的影响
        if(dividend > 0 && divisor < 0 || dividend < 0 && divisor > 0){
            sign = false;
        }

        //为了避免在计算绝对值过程中出现overflow的问题
        long new_dividend = abs((long)dividend);
        long new_divisor = abs((long)divisor);
        long result = 0;

        //为了加快计算速度，使power尽可能的变大，但又不超过被除数
        int power = 0;
        while(new_divisor <= (new_dividend >> 1)){
            new_divisor = new_divisor << 1; //每次将除数乘2，使power值+1, 
            //最后2的power次方代表着对于结果的贡献值
            power++; 
            //算出使结果为0的被除数的最大的2的n次方倍
        }

        while(power >= 0){
            if(new_dividend >= new_divisor){
                result += (1 << power);
                new_dividend -= new_divisor;
            }
            power--;
            new_divisor -= new_divisor >> 1;
        }
        return sign ? result : -result;
    }
    
    int divide(int dividend, int divisor){
        //考虑被除数为最小值的情况
        if(dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        
        bool sign = true;

        //考虑符号对于结果的影响
        if(dividend > 0 && divisor < 0 || dividend < 0 && divisor > 0){
            sign = false;
        }

        //为了避免在计算绝对值过程中出现overflow的问题
        long new_dividend = abs((long)dividend);
        long new_divisor = abs((long)divisor);
        long result = 0;

        //为了加快计算速度，使power尽可能的变大，但又不超过被除数
        int power = 0;
        while(new_divisor <= (new_dividend >> 1)){
            new_divisor = new_divisor << 1; //每次将除数乘2，使power值+1, 
            //最后2的power次方代表着对于结果的贡献值
            power++; 
            //算出使结果为0的被除数的最大的2的n次方倍
        }

        while(power >= 0){
            if(new_dividend >= new_divisor){
                result += (1 << power);
                new_dividend -= new_divisor;
            }
            power--;
            new_divisor -= new_divisor >> 1;
        }
        return sign ? result : -result;
    }
};