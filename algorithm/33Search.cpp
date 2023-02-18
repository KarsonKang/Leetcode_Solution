#include <iostream>
#include <vector>

using namespace std;

class Solution{
public:
    int search(vector<int>& nums, int target){
        int n = nums.size();    //记录数组长度
        if(n == 0){
            return -1;
        }
        if(n == 1){
            return target == nums[0] ? 0 : -1;
        }

        int left = 0, right = n - 1;   //记录边界的位置
        
        while(left <= right){
            int mid = (left + right) / 2;    //记录二分位置的位置
            if(nums[mid] == target){
                return mid;
            }
            if(nums[left] <= nums[mid]){//当前一半为有序数组时
                if(nums[left] <= target && target < nums[mid]){
                    right = mid - 1;    //改变右边界的值
                }
                else{
                    left = mid + 1;    //改变左边界的值
                }
            }
            else{                       //当后一半为有序数组时
                if(nums[mid] < target && target <= nums[right]){
                    left = mid + 1;
                }
                else{
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
