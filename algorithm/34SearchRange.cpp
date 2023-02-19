#include <iostream>
#include <vector>

using namespace std;

//花了较长时间才搞清楚为什么 ans = mid 这句代码放置的位置非常重要
class Solution { 
public:
    //利用二分法，寻找边界。
    int searchborder(vector<int>& nums, int target, bool border){
        int left = 0, right = nums.size() - 1;
        int mid = (left + right) / 2;
        int ans = nums.size();
        while(left <= right){
            mid = (left + right) / 2;
            if(nums[mid] < target || (border && nums[mid] <= target)){
                left = mid + 1;
            }
            else {
                right = mid - 1;
                ans = mid;          //** 注意点 **这句代码放置的位置非常关键
            }
            
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        //因为返回的是一个范围，所以需要分别找到这个范围的边界
        int left = searchborder(nums, target, false);
        int right = searchborder(nums, target, true) - 1;
        if(left <= right && right < nums.size()){
            return vector<int> {left, right};
        }
        return {-1, -1};
    }
};
