#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9][9];          //9*9宫格，所以由9行，每行都包含1~9，9个数字
        int column[9][9];       //9*9宫格，所以由9列，每列都包含1~9，9个数字
        int subbox[3][3][9];    //9*9宫格，包含了9个3*3的子宫格，所以[3][3]为子宫格的位置坐标,每个宫格包含了9个数字
        int var;
        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));
        memset(subbox, 0, sizeof(subbox));

        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] != '.'){
                    var = board[i][j] - '0' - 1;    //记录数字的位置
                    row[i][var]++;
                    column[j][var]++;
                    subbox[i / 3][j / 3][var]++;
                    //记录数字在行，列，子阵中出现的次数
                    if(row[i][var] > 1 || column[j][var] > 1 || subbox[i / 3][j / 3][var] > 1){
                        return false;
                    }
                }
            }
        }
        return true;
    }
};