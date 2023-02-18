#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

class Solution{
public:
    int threeSumClosest(vector<int>& nums, int target){
        int n = nums.size();
        int sum = 0;
        int ans = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        for(int first = 0; first < n; first++){
            int second = first + 1;
            int third = n - 1;
            while(second < third){
                sum = nums[first] + nums[second] + nums[third];
                if(sum == target){
                    return sum;
                }
                ans = abs(target - sum) < abs(target - ans) ? sum : ans;
                if(sum > target){
                    third--;
                }
                else if(sum < target){
                    second++;
                }
                
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    vector<int> nums = {-1,2,1,-4};
    int target = 1;
    cout << s.threeSumClosest(nums, target) << endl;
    return 0;
}

