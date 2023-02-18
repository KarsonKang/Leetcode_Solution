#include<iostream>
#include<list>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution{
public:
    /*思路：和我们进行加法计算的思路相同，利用进位carry，计算每个位相加的值
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        ListNode *head = nullptr;
        ListNode *tail = nullptr;   //作为结果的返回链表的头部和尾部
        int carry = 0;              //作为进位值
        while(l1 || l2){            //当l1，l2其中一个不为空时，就进行计算
            int n1 = (l1 ? l1->val : 0);    //如果l1节点不为空，获取其val值，为空时，值为0；
            int n2 = (l2 ? l2->val : 0);
            int sum = n1 + n2 + carry;
            if(!head){      //插入第一个值的情况
                head = tail = new ListNode(sum % 10);
            }
            else{
                tail->next = new ListNode(sum % 10);
                tail = tail->next;      //将新值插入尾节点，之后更新尾节点
            }
            carry = sum / 10;
            if(l1){
                l1 = l1->next;
            }
            if(l2){
                l2 = l2->next;
            }
        }
        if(carry > 0){
            tail->next = new ListNode(carry);
            tail = tail->next;      //此时不更新尾节点也可以
        }
        return head;
    }
};