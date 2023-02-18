#include<iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution{
public:
    //方法一：迭代
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2){
        ListNode* head = new ListNode();
        ListNode* end = head;   
        ListNode* l1 = list1;   //这一步多余，可以省略
        ListNode* l2 = list2;
        while(l1 && l2){
            if(l1->val <= l2->val){
                end->next = l1;     //将end结点的指针指向小的结点
                l1 = l1->next;      //更新list结点
            }
            else{
                end->next = l2;
                l2 = l2->next;
            }
            end = end->next;        //更新end结点
        }

        end->next = l1 ? l1 : l2;   //当其中一方为空后，将end结点直接指向另一个结点即可
        return head->next;          //head的初始结点的值为空，所以开始结点为head->next
    }

    //方法二：递归，每次递归，list1，或list2都会继续后移。时间复杂度跟迭代一样O(m+n)，空间复杂度为O(m+n)
    ListNode* mergeTwoLists2(ListNode* list1, ListNode* list2){
        if(!list1){
            return list2;
        }
        else if(!list2){
            return list1;
        }
        else if(list1->val <= list2->val){
            list1->next = mergeTwoLists2(list1->next, list2);
            return list1;
        }
        else{
            list2->next = mergeTwoLists2(list1, list2->next);
            return list2;
        }
    }

};