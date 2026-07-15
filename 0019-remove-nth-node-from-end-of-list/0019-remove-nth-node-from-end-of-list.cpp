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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* temp=head;
     ListNode* ahead=head;
     for(int i=1;i<=n;i++){
        ahead=ahead->next;
     }
     if(ahead==NULL){
        return temp->next;
     }
     
     while(ahead->next!=NULL)
     {
         temp=temp->next;
         ahead=ahead->next;
     }
     temp->next=temp->next->next;
     return head;
    }
};