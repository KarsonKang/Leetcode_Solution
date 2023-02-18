#include <iostream>
#include <vector>
#include <algorithm> //使用sort排序函数时，使用的库函数

using namespace std;

class Solution{
public:
    /*方法一：排序+双指针
    这个题与两数之和类似，非常经典，但是解决方法不同
    最先想到就是三重循环，但是直接使用的话，时间复杂度太大，因此需要进行优化。
    首先，三数之和为0，我们枚举的三个数（a,b,c）大小关系为a <= b <= c，
    可以通过从小到大的排序，减少遍历的次数，并且减少了(b,a,c) (c,a,b)这样的的重复
    另外，我们可以发现，当我们固定了前两重循环的元素a,b后，之后位移的一个c满足a+b+c = 0。
    当第二重循环往后枚举一个元素 b'时，由于b' > b,那么满足a + b' + c' = 0的c'，一定有c' < c
    即c'一定出现在c的左侧，因此，我们可以在从左到右枚举b的同时，从右向左枚举c，即二重循环
    和三重循环实际上是并列的关系。
    */
    vector<vector<int>> threeSum(vector<int>& nums){
        int n = nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());     //利用sort函数排序,默认升序
        for(int first = 0; first < n; first++){
            //和上一次枚举的值不相同
            if(nums[first] > 0){
                break;
            }
            if(first > 0 && nums[first] == nums[first - 1]){
                continue;
            }
            //c对应的指针初始位置在最右端
            int third = n - 1;
            int target = -nums[first];
            for(int second = first + 1; second < n; second++){
                //和上一次枚举的值不相同
                if(second > first + 1 && nums[second] == nums[second - 1]){
                    continue;
                }
                while(second < third && nums[second] + nums[third] > target){
                    third--;
                    //当大于目标值时，将third指针向左移动
                }
                if(second == third){
                    break;
                    //当指针重合时，随着b的增加，不会出现a+b+c = 0并且b<c的情况了
                }
                if(nums[second] + nums[third] == target){
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    vector<int> nums = {0,0,0};
    vector<vector<int>> ans = s.threeSum(nums);
    //利用auto遍历二维数组的一种写法
    for(const auto& i : ans){
        for(const auto& j : i){
            cout << j << endl;
        }
    }
    //利用正常方法遍历二维数组的写法
    for(vector<vector<int>>::iterator it = ans.begin(); it != ans.end(); it++){
        for(vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++){
            cout << *vit << endl;
        }
    }
   
    return 0;
}
