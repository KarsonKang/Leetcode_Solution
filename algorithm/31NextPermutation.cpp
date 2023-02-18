#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
    //这个题目有点不好理解，最终目的是，找到比当前排列顺序大的另一个顺序，但只大了一个等级
    //即将当前所有数字进行排列，得到的数字从小到大排列，找到当前排列的下一个排列
    void nextPermutation(vector<int>& nums){
        int i = nums.size() - 2;
        //第一步找出一个顺序对(i, i + 1),满足a[i] < a[i + 1],此时[i + 1, n)必然是下降序列
        while(i >= 0 && nums[i] >= nums[i + 1]){
            i--;
        }

        //之后，在区间[i + 1, n)中从后向前查找第一个元素j，满足a[i] < a[j]
        if(i >= 0){
            int j = nums.size() - 1;
            while(j > i && nums[i] >= nums[j]){
                j--;
            }

            //找到后，交换元素a[i],a[j]的位置
            swap(nums[i], nums[j]);
        }

        //最后将a[i]之后的元素进行翻转
        reverse(nums.begin() + i + 1, nums.end());

        //最后的结果就是下一个排序的结果
    }

};