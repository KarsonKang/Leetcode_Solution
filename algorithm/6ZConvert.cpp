#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution{
public:
    /*
    方法一：利用二维矩阵模型，寻找变化的周期
    设n为字符串的长度，r = numRows。对于r = 1或r >= n，可以直接返回s。
    根据题意，在矩阵上填写字符时，会向下填写r个字符，然后向右上填写r-2个字符
    最后回到第一行，完成一个周期，因此一个周期t = r + r - 2 = 2r-2
    每个周期占用1 + r - 2 = r - 1列。一共有⌈n/t⌉（向上取整）个周期，乘上每个周期的列数
    得到所需矩阵的行数c = ⌈n/t⌉ * (r - 1)
    创建一个r行c列的矩阵，遍历字符串s按照Z字形填写。
    当前字符下标i满足i % t < r - 1时向下填写，否则向右上填写
    填写完成后，扫描非空字符，组成答案
    */
    string convert(string s, int numRows){
        int n = s.length();
        int r = numRows;                //矩阵的行数
        if(r == 1 || r >= n){
            return s;
        }           
        int t = 2 * r - 2;            //周期
        int c = (n + t - 1) / t * (r - 1);   //(n + t - 1 )/ t 为(n / t)向上取整的写法 c为矩阵列数
        vector<string> mat(r, string(c, 0));
        for(int i = 0, x = 0, y = 0; i < n; i++){
            mat[x][y] = s[i];
            if(i % t < r - 1){
                x++;
            }
            else{
                x--;
                y++;
            }
        }
        string ans;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(mat[i][j]){
                    ans.push_back(mat[i][j]);
                }
            }
        }           //这种for循环相对更花时间

        for (auto &row : mat) {     //***注意auto在循环中的用法***
            for (char ch : row) {   //**使用auto时，对二维数组的遍历的写法**
                if (ch) {
                    ans += ch;
                }
            }
        }           //这种for循环的写法花费时间较少
        return ans;
    }

    /*方法二：压缩矩阵空间
    方法一中的矩阵有大量的空间没有被使用，可以进行优化
    注意到，每次在往矩阵的某一行添加字符时，都会添加到该行上一个字符的右侧，
    且最后组成答案时，只会用到每行的非空字符，我们可以将矩阵的每一行初始化为一个空列表
    将字符添加到该行列表的末尾即可
    **这种方法用时更快，内存占用更少**
    */
    string convert2(string s, int numRows){
        int n = s.length(), r = numRows;
        if(r == 1 || r >= n){
            return s;
        }

        int t = r * 2 - 2;
        int c = (n + t - 1) / t * (r - 1);
        vector<string> mat(r);
        for(int i = 0, x = 0; i < n; i++){
            mat[x].push_back(s[i]);
            //mat[x] += s[i];
            if(i % t < r - 1){
                x++;
            }
            else{
                x--;
            }
        }
        string ans;
        for(auto &row : mat){
            ans += row;
        }
        return ans;
    }
    /*方法三：直接构造
    研究方法一的矩阵中，每个非空字符会对应到字符串s的那个下标，idx，找出规律，得出答案
    Z字形变化的周期为t = 2r - 2，因此第一行的非空字符为t的下标为t的整数倍即(i % t) = 0
    最后一行的字符满足(i % t) = r - 1,
    其余行每个周期内有两个字符，设行号为R，第一个字符满足 (i % t) = R，第二个字符满足(i % t) = t - R
    */
    string convert3(string s, int numRows){
        int n = s.length(), r = numRows;
        if(r == 1 || r >= n){
            return s;
        }

        int t = r * 2 - 2;
        string ans;
        for(int i = 0; i < r; i++){
            for(int j = 0; j + i < n; j += t){ //枚举每个周期的下标
                ans += s[j + i];        //当前周期的第一个字符
                if(i > 0 && i < r - 1 && j + t - i < n){
                    ans += s[j + t - i];    //当前周期的第二个字符
                }
            }
        }
        return ans;
    }
};

int main(){
    string s = "PAYPALISHIRING";
    Solution s1;
    cout << s1.convert2(s, 3) << endl;
    return 0;
}