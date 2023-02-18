#include<iostream>
#include<set>
#include<vector>

using namespace std;

class Solution{
public:
    double findMedianSortedArray1(vector<int>& num1, vector<int>& num2){
            //方法一暴力排序，使用multiset容器，将数据排序，然后求中位数。
        multiset<int> ms;
        for(int i = 0; i < num1.size(); i++){
            ms.insert(num1[i]);                 //将num1中的数据放入multiset容器
        }
        for(int i = 0; i < num2.size(); i++){
            ms.insert(num2[i]);                 //将num2中的数据放入multiset容器
        }
        vector<int> v;                          //利用vector容器复制multiset容器中的数据（为了更方便的遍历排好序的数据）
        for(set<int>::iterator it = ms.begin(); it != ms.end(); it++){
            cout << *it << endl;
            v.push_back(*it);
        }
        int nums = ms.size();                   //获取multiset容器中元素的个数
        if(nums % 2 == 1){
            return v[nums/2];                   //个数为奇数时，返回的中位数
        }
        return (double)(v[nums/2] + v[nums/2 - 1]) / 2;     //个数为偶数时，返回的中位数
    }


    //方法二：二分查找。由于两个数组的长度已知，因此中位数对应的两个数组的下标之和也是已知的。
    //维护两个指针，初始时分别指向两个数组的下标 00 的位置，每次将指向较小值的指针后移一位
    //（如果一个指针已经到达数组末尾，则只需要移动另一个数组的指针），直到到达中位数的位置。
    int getKthElement(vector<int>& nums1, vector<int>& nums2, int k){
        /* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
         * 这里的 "/" 表示整除
         * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
         * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
         * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
         * 这样 pivot 本身最大也只能是第 k-1 小的元素
         * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
         * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
         * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
         */
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0;         //数组1中删除的元素的个数
        int index2 = 0;         //数组2中删除的元素的个数

        while(true){
            if(index1 == m){
                return nums2[index2 + k - 1];   //当其中一个数组到达边界值时，可以直接返回中位数
            }
            if(index2 == n){
                return nums1[index1 + k - 1];   //同上
            }
            if(k == 1){
                return min(nums1[index1], nums2[index2]);   //当k值变化到1时，比较此时两个数组中更新后的值的大小，小的一方为中位数
            }

            int newIndex1 = min(index1 + k / 2 - 1, m - 1);  //获取num1中需要进行比较的下标的值（跟m-1比较是为了防止越界）
            int newIndex2 = min(index2 + k / 2 - 1, n - 1);  //获取num2中需要进行比较的下标的值

            int pivot1 = nums1[newIndex1];          //获取nums1中需要进行比较的值
            int pivot2 = nums2[newIndex2];          //获取nums2中需要进行比较的值

            if(pivot1 <= pivot2){
                k -= newIndex1 - index1 + 1;             //更新k值，从寻找第k小的数，更新为寻找第（k - 本次循环删除元素的个数）小的数
                index1 = newIndex1 + 1;                  //删除的个数为下标值 + 1
            }
            else{
                k -= newIndex2 - index2 + 1;             //更新k值，从寻找第k小的数，更新为寻找第（k - 本次循环删除元素的个数）小的数
                index2 = newIndex2 + 1;                  //删除的个数为下标值 + 1
            }

        }
    }

    double findMedianSortedArray2(vector<int>& nums1, vector<int>& nums2){
        int totalLength = nums1.size() + nums2.size();
        if(totalLength % 2 == 1){
            return getKthElement(nums1, nums2, (totalLength / 2 + 1));
        }
        else{
            return (getKthElement(nums1, nums2, (totalLength / 2)) + getKthElement(nums1, nums2, (totalLength / 2 + 1))) / 2.0;
            //偶数个元素时，需要 /2.0 将int型转化成double型，或者使用(double)强制类型转换。
        }
    }
};

int main(){
    Solution s1;
    vector<int> v1;
    vector<int> v2;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);
    cout << s1.findMedianSortedArray2(v1, v2);
}