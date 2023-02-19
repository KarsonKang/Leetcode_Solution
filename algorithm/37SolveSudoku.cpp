#include<iostream>
#include<vector>

using namespace std;
class Solution {
public:
    //定义三个数组记录每行，每列，每个子宫格中数字的出现情况
    bool row[9][9], column[9][9], subbox[3][3][9];

    //利用递归，不断回溯的方式，根据规则，找出最优解
    bool dfs(vector<vector<char>>& board, int x, int y){
        //x, y起始位置
        if(y == 9){     //如果一行结束，进行下一行
            x++;
            y = 0;
        }
        if(x == 9){
            return true;    //如果程序执行到了最后，说明填充完成，返回true
        }
        if(board[x][y] != '.'){ //如果当前枚举的位置有数字，则跳过当前位置，继续调用此函数
            return dfs(board, x, y+1);  //*注意*，这里不能使用++y，这会改变当前y的值，是程序出问题。
        }

        //枚举当前位置可以填入的数字
        for(int i = 0; i < 9; i++){
            //当枚举的数字在所在的行，列，或子宫格中已经出现的时候，跳过当前数字
            if(row[x][i] || column[y][i] || subbox[x/3][y/3][i]){
                continue;
            }
            //如果不存在，则尝试将当前枚举的数字放入
            board[x][y] = i + '1';
            //并在三个数组中对应的位置上进行记录
            row[x][i] = column[y][i] = subbox[x / 3][y / 3][i] = true;
            //之后跳到下一个位置，继续调用该函数，如果返回值依然是true，说明这一组的解成立
            if(dfs(board, x, y+1)){
                return true;
            }
            //如果返回值为false，则说明当前的枚举值不能放入此位置，对此前的值放入操作进行回退
            row[x][i] = column[y][i] = subbox[x / 3][y / 3][i] = false;
            board[x][y] = '.';
        }
        //如果枚举的所有数字都没有解，则返回false
        return false;
    }


    void solveSudoku(vector<vector<char>>& board) {
        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));
        memset(subbox, 0, sizeof(subbox));

        //记录已有的数独中的数字
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] != '.'){
                    int ch = board[i][j] - '0' - 1; //1~9对应数组中0~8的下标
                    row[i][ch] = column[j][ch] = subbox[i/3][j/3][ch] = true;   //数字出现过，则在对应的位置记录为true
                }
            }
        }

        //记录完已有的数字后，开始填写每一个空位上的数字
        //这里利用的方法是回溯法，也是递归。从0，0开始调用dfs函数，将数字填入board中。
        dfs(board, 0, 0);
    }
};