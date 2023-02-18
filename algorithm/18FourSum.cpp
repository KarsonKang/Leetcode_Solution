#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
    /*方法一：排序，双循环，双指针
    时间复杂度O(n^3)
    */
    vector<vector<int>> fourSum(vector<int>& nums, int target){
        
        vector<vector<int>> ans;
        if(nums.size() < 4){
            return ans;
        }
        sort(nums.begin(), nums.end());
        int n = nums.size(); //记录数据长度

        for(int i = 0; i < n - 3; i++){
            //测试例中有过大的数据
            if((long) nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target){
                break;
            }
            if((long) nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target){
                continue;
            }
            //为了防止数据溢出，将nums[i]临时转换成long型
            //增加上面的两种判断情况之后，运行速度明显加快

            if(i > 0 && nums[i] == nums[i - 1]){
                continue;
            }
            for(int j = i + 1; j < n - 2; j++){

                if((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target){
                    break;
                }
                if((long) nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target){
                    continue;
                }
                //为了防止数据溢出，将nums[i]临时转换成long型
                //增加上面的两种判断情况之后，运行速度明显加快

                if(j > i + 1 && nums[j] == nums[j - 1]){
                    continue;
                }
                int left = j + 1;       //左指针
                int right = n - 1;      //右指针

                while(left < right){
                    //long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
                    //也可以使用上面的这种写法，来防止数据溢出
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    
                    if(sum > target){
                        right--;
                    }
                    else if(sum < target){
                        left++;
                    }
                    else if(sum == target){
                        ans.push_back({nums[i], nums[j], nums[left], nums[right]});
        //注意：这里要先判断left < right，因为left + 1可能会导致nums[left + 1]溢出？？？？在使用{0,0,0,0} 0 的测试用例时总是报错
        //先判断大小之后，代码可以正常运行
                        while(left < right && nums[left] == nums[left + 1]){
                            left++;
                        }
                        left++;

                        while(left < right && nums[right] == nums[right - 1]){
                            right--;
                        } 
                        right--;
                    }
                }
            }
        }
        return ans;
    }
};