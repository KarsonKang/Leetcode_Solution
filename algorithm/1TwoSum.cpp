#include<iostream>
#include<map>
#include<vector>

using namespace std;

class Solution{
public:
    vector<int> twoSum(vector<int>& nums, int target){
        map<int, int> m;
        int n = nums.size();
        int x = 0;      
        for(int i = 0; i < n; i++){
            x = target - nums[i];
            if(m.count(x) == 0){
                m.insert(make_pair(nums[i], i));    //第一次出现的值，放入map中
            }
            else if(m.count(x) && i != m[x]){
                return {m[x], i};           //当map中有与之和为target的值时，输出结果
            }
        }
        return {};
    }
};

int main(){
    Solution s;
    vector<int> nums = {2,7,11,15};
    int target = 9;
    vector<int> ans = s.twoSum(nums, target);
    for(const auto& i : ans){
        cout << i << endl;
    }
    return 0;
}