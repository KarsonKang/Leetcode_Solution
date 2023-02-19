#include<iostream>
#include<vector>

using namespace std;

//这道题中，如何去重是一个非常关键的地方，目前的方法，是比较容易理解的
//官方题解中给出的方法，使用了hashmap,没看懂，以后有想法的话，可以好好理解一下。

class Solution {
public:
    vector<vector<int>> ans;
    vector<int> combine;

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        //考虑到不能有重复数组的出现，如果依然使用39题的方法的话，需要先对数组进行排序
        sort(candidates.begin(), candidates.end());
        //之后再使用递归
        dfs(candidates, target, 0);
        return ans;
    }

    void dfs(vector<int>& candidates, int target, int i){
        if(target == 0){
            ans.push_back(combine);
            return;
        }
        if(i >= candidates.size()){
            return;
        }
        //统计重复元素的个数
        int cnt = 1;
        while(i + 1 < candidates.size() && candidates[i] == candidates[i+1]){
            cnt++;
            i++;
        }
        //考虑到重复出现的元素，一下代码是为了去除重复。
        for(int j = 0; j <= cnt && target >=j * candidates[i]; j++){
            dfs(candidates, target - j * candidates[i], i + 1);
            combine.push_back(candidates[i]);
        }
        for(int j = 0; j <= cnt && target >=j * candidates[i]; j++){
            combine.pop_back();
        }
    }
};