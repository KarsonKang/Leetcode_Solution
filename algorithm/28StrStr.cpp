#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution{
public:
    int strStr(string haystack, string needle){
        int l = needle.length();
        if(l == 0)
            return 0;
        if(l > haystack.length())
            return -1;
        for(int i = 0; i < haystack.length(); i++){
            if(haystack[i] == needle[0]){
               for(int j = 0; j < needle.length(); j++){
                    if(needle[j] != haystack[i + j]){
                        break;
                    }
                    if(j == needle.length() - 1){
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    //方法二：KMP算法**
    //KMP算法是一个查找匹配串的算法，他的作用是：如何快速在“原字符串”中找到“匹配的字符串”。
    //算法主要分为两个部分第一个部分是：计算next数组
    //第二个部分是：
    int strStrKMP(string haystack, string needle){
        int l = needle.length();
        if(l == 0)
            return 0;
        if(l > haystack.length())
            return -1;
        
        //开始计算next数组
        // 我们举个例子说明：字符串 aabaaab 的前缀函数值依次为 0,1,0,1,2,2,3
        // next(0) = 0，因为 a 没有真前缀和真后缀，根据规定为 0（可以发现对于任意字符串next(0)=0 必定成立）
        // next(1) = 1，因为 aa 最长的一对相等的真前后缀为 a，长度为 1；
        // next(2) = 0，因为 aab 没有对应真前缀和真后缀，根据规定为 0；
        // next(3) = 1，因为 aaba 最长的一对相等的真前后缀为 a，长度为 1；
        // next(4) = 2，因为 aabaa 最长的一对相等的真前后缀为 aa，长度为 2；
        // next(5) = 2，因为 aabaaa 最长的一对相等的真前后缀为 aa，长度为 2；
        // next(6) = 3，因为 aabaaab 最长的一对相等的真前后缀为 aab，长度为 3。
        // 有了前缀函数，我们就可以快速地计算出模式串在主串中的每一次出现。

        vector<int> next(l);//next中的默认值均为0。
        for(int i = 1, j = 0; i < l; i++){
            while(j > 0 && needle[i] != needle[j]){
                j = next[j - 1];
            }
            if(needle[i] == needle[j]){
                j++;
            }
            next[i] = j;
        }

        for (int i = 0, j = 0; i < haystack.length(); i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == l) {
                return i - l + 1;
            }
        }
        return -1;
    }

};
