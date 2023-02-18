#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr){}
    ListNode(int x) : val(x), next(nullptr){}
    ListNode(int x, ListNode* next) : val(x), next(next){}
};

class Solution{
public:
    /*方法一：
    在21题中，实现了合并两个链表
    合并多个链表时，可以利用多个循环，每个循环合并两个，知道最后完全合并
    时间复杂度较大
    */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        ListNode* head = new ListNode();
        ListNode* end = head;
        while(l1 && l2){
            if(l1->val <= l2->val){
                end->next = l1;
                l1 = l1->next;
            }
            else{
                end->next = l2;
                l2 = l2->next;
            }
            end = end->next;
        }
        end->next = l1 ? l1 : l2;
        return head->next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists){
                                        //***
        ListNode* ans = nullptr;        //注意，这里不要将ans初始化为new ListNode(),因为ListNode()中，
                                        //val的默认值为0，当遇到-1时，链表的表头数据会发生变化，导致错误
                                        //这一点在合并2个以上的链表时，需要注意
        int n = lists.size();
        for(int i = 0; i < n - 1; i++){
            ans = mergeTwoLists(ans, lists[i]);
        }
        return ans;
    }
};

class Solution2{
public:
    //方法二：使用优先队列合并 ***有点难，多看看***
    /*我们需要维护当前每个链表没有被合并的元素的最前面一个，k个链表就最多有 k个满足这样条件的元素，
    每次在这些元素里面选取val属性最小的元素合并到答案中。
    */
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;   //运算符重载
        }
    };

    priority_queue <Status> q;      //声明优先队列
                                    //可以将放入的数据从小到大排列

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) {
            if (node) q.push({node->val, node});
        }
        ListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top(); q.pop();
            tail->next = f.ptr;
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};
