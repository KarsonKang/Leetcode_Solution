#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution{
public:
    /*方法一：纵向对比
    利用两个for循环,出现不相等的情况时，直接返回公共子串
    */
    string longestCommonPrefix(vector<string>& strs){
        string commonprofix("");                //初始化
        if(strs.size() == 0){
            return commonprofix;
        }
        
        int n = strs.size();
        int m = strs[0].size();
        for(int i = 0; i < m; i++){             //横向移动，表示字符串的第i个字母
            for(int j = 0; j < n - 1; j++){     //纵向移动，表示第j个字符串
                if(strs[j][i] != strs[j+1][i]){ 
                    return commonprofix;
                }
            }
            commonprofix += strs[0][i];
        }
        return commonprofix;
    }

    /*方法二：横向移动，遍历所有字符串，每遍历一个字符串，更新其最长公共前缀*/
    string longestCommonPrefix2(vector<string>& strs){
        string commenfix("");
        if(strs.size() == 0){
            return commenfix;
        }
        int n = strs.size();
        int m = strs[0].size();
        commenfix = strs[0];
        int sameNum = 0;

        for(int i = 1; i < n; i++){
            for(int j = 0; j < commenfix.size(); j++){
                if(strs[i][j] != commenfix[j]){
                    commenfix = strs[i].substr(0, j);
                    break;
                }
            }
        }
        return commenfix;
    }
};

int main(){
    Solution s;
    vector<string> strs;
    strs = {"flower","flow","flight"};
    cout << s.longestCommonPrefix2(strs);
    return 0;
}