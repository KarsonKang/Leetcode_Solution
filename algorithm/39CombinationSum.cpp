#include <iostream>
#include <vector>

using namespace std;

//利用递归解决的问题，对于递归的应用熟练度不够，这类题要多看。

class Solution {
public:
    //先声明返回的结果，和每次结果中用于储存每一节的变量。
    vector<vector<int>> ans;
    vector<int> combine;

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        //调用递归函数，从0开始寻找。
        dfs(candidates, target, 0);
        return ans;
    }

    //利用到的递归,i为遍历到的数字的下标
    void dfs(vector<int>& candidates, int target, int i){
        if(target == 0){
            ans.push_back(combine);
            return;
        }
        if(i >= candidates.size()){ //当遍历完所有的数据后，直接返回
            return;
        }
        //进入递归模式，从最小的数开始寻找
        if(target >= candidates[i]){
            combine.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], i);
            combine.pop_back();
        }
        //之后，开始寻找的数字逐渐增大。
        dfs(candidates, target, i+1);

    }

};