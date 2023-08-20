/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) {
            return list2;
        }
        if (!list2) {
            return list1;
        }
        ListNode* res;
        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            res = list1;
        }
        else {
            list2->next = mergeTwoLists(list1, list2->next);
            res = list2;
        }
        return res;
    }
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) {
            return list2;
        }
        if (!list2) {
            return list1;
        }
        ListNode* head;
        if (list1->val < list2->val) {
            head = list1;
            list1 = list1->next;
        }
        else {
            head = list2;
            list2 = list2->next;
        }

        ListNode* it = head;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                it->next = list1;
                list1 = list1->next;
            }
            else {
                it->next = list2;
                list2 = list2->next;
            }
            it = it->next;
        }
        if (list1) {
            it->next = list1;
        }
        else {
            it->next = list2;
        }
        return head;
    }
};
