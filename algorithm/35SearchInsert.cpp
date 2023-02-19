#include <iostream>
#include <vector>
using namespace std;
class Solution{
public:
    //二分法的应用
    int searchInsert(vector<int>& nums, int target){
        int left = 0, right = nums.size() - 1;
        int mid = (left + right) / 2;
        while(left < right){
            if(nums[mid] < target){
                left = mid + 1;
            }
            else if(nums[mid] > target){
                right = mid - 1;
            }
            else{
                return mid;
            }
            mid = (left + right) / 2;   //在最后更新mid，可以使循环结束时，
                                        //mid的值停留在最后一个循环的中间值上。
        }
        if(nums[mid] >= target)     //考虑到边界的情况，如果此时的mid指向的值大于目标值，
            return mid;             //要插入值的话，就要返回当前位置的下标。
        
        return mid + 1;             //当最大值都比目标值小时，将target插入数组的最后。
    }
};