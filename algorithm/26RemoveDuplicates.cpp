#include<iostream>
#include<vector>

using namespace std;

class Solotion{
public:
    //注：这种用STL中erase函数的方法很难行得通。
    int removeDuplicates1(vector<int>& nums){
        vector<int>::iterator it = nums.begin();
        while(it != nums.end()){
            if(*it == *(it++)){
                it--;
                nums.erase(it);
            }
            else{
                it++;
            }
        }    
        return nums.size();
    }

    //不采用erase函数删除元素的方法，而是采用覆盖的方式
    int removeDuplicates(vector<int>& nums){
        int n = nums.size();
        int p = 1;
        int q = 1;
        for(q; q < n; q++){
            if(nums[q] != nums[q - 1]){
                nums[p] = nums[q];
                p++;
            }
        }
        return p;
    }
};