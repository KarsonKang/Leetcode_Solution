#include<iostream>
#include<vector>

using namespace std;

class Solution{
public:
    //方法一：利用STL的erase函数
    int removeElement(vector<int> nums, int val){
        vector<int>::iterator it = nums.begin();
        while(it != nums.end()){
            if(*it == val){
                nums.erase(it);
            }
            else{
                it++;
            }
        }
        return nums.size();
    }
    //方法二：双指针优化，覆盖值的方法
    int removeElement2(vector<int> nums, int val){
        int left = 0;
        int right = nums.size();
        while(left < right){
            if(nums[left] == val){
                nums[left] = nums[right];
                right--;
            }
            else{
                left++;
            }    
        }
        return left;
    }
};