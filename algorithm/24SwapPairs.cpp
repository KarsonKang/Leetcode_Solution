#include<iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr){}
    ListNode(int x) : val(x), next(nullptr){}
    ListNode(int x, ListNode* next) : val(x), next(next){};
};

class Solution{
public:
    ListNode* swapParis(ListNode* head){
        //在交换链表中结点的位置时，一定要注意，设置一个结点指向头结点，防止头结点换位或丢失
        ListNode* temp = new ListNode();
        ListNode* front = new ListNode(0, head);
        temp = front;
        while(temp->next && temp->next->next){
            //在交换两个结点时，相当于交换三个指针的值
            ListNode* n1 = temp->next;
            ListNode* n2 = temp->next->next;
            temp->next = n2;
            n1->next = n2->next;
            n2->next = n1;
            temp = n1;
        }
        return front->next;
    }
};

