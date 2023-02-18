#include<iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) :  val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {} 
};

class Solution{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n){
        ListNode* it = head;
        //ListNode* it = new ListNode(0, head); 另一种写法
        int num = 0;        //记录链表长度
        while(it != nullptr){
            num++;          //首先获取链表的长度
            it = it->next;
        }
        if(n == num){       //特殊情况，删除头结点是的情况
            head = head->next;
        }
        int delnum = num - n + 1;
        it = head;
        for(int i = 1; it != nullptr; it = it->next, i++){
            if(i == delnum - 1){
                it->next = it->next->next;
            }
        }
        delete it;  //新建内存，之后删除
        return head;
    }
};