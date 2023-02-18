#include<iostream>
#include<vector>

using namespace std;

class Solution{
public:
    /*方法一：双for循环
    好写，最先想到，但是太耗时间，会超时。
    */
    int maxArea1(vector<int>& height){
        int maxarea = 0;
        int n = height.size();
        int area = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                area = min(height[i], height[j]) * (j - i);
                maxarea = max(area, maxarea);
            }
        }
        return maxarea;
    }

    /*方法二：双指针***
    更快速，双指针是一个重要的方法，要活用
    双指针代表得是可以作为容器边界的所有位置的范围。
    两个指针从数据的两端向中间靠拢，每次靠拢的都是高度较小的指针，因为对应数字小的指针
    不可能在作为容器的边界，当移动高度较大的指针时，容积一定是减小的（短板效应）
    因此，使高度较小的指针向内靠拢才有机会获得更大的容积
    */
    int maxArea(vector<int>& height){
        int maxarea = 0;
        int i = 0, j = height.size() - 1;
        int area = 0;
        while(i < j){
            area = min(height[i], height[j]) * (j - i);
            maxarea = max(area, maxarea);
            height[i] <= height[j] ? i++ : j--;
        }
        return maxarea;
    }

};

int main(){
    Solution s1;
    vector<int> height;
    height.push_back(1);
    height.push_back(8);
    height.push_back(6);
    height.push_back(2);
    height.push_back(5);
    height.push_back(4);
    height.push_back(8);
    height.push_back(3);
    height.push_back(7);
    cout<< s1.maxArea(height);
    return 0;
}
