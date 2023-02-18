#include<iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){}
    ListNode(int x) : val(0), next(nullptr){}
    ListNode(int x, ListNode *next) : val(0), next(next){}
};

class Solution{
public:
    //翻转一个子链表，并返回首和尾
    pair<ListNode*, ListNode*> subReverse(ListNode* head, ListNode* tail){
        ListNode* prev = tail->next;
        ListNode* p = head;
        while(prev != tail){
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k){
        //在链表前添加一个新的结点，方便后续的返回和转换
        ListNode* hair = new ListNode();
        hair->next = head;
        ListNode* pre = hair;
        ListNode* tail = pre;
        while(head){
            for(int i = 0; i < k; i++){
                tail = tail->next;
                if(!tail){
                    return hair->next;
                }
            }
            ListNode* nex = tail->next;//记录下一个反转列表的起始位置
            //反转head和tail之间的链表
            //由于反转之后需要将子链表接回原链表，所以反转函数需要有头部和尾部作为返回值
            pair<ListNode*, ListNode*> result = subReverse(head, tail);

            //注意：翻转之后要将head和tail的值进行更新
            head = result.first;
            tail = result.second;

            //将子链表连接到原链表中
            pre->next = head;
            tail->next = nex;
            
            pre = tail;
            head = nex;
        }

        return hair->next;
    }
    
};
