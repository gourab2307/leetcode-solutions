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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
         int first = -1, last = -1;
        int minDist = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int pos = 1; // curr's index

        while (curr->next) {
            ListNode* nxt = curr->next;

            bool isCritical =
                (curr->val > prev->val && curr->val > nxt->val) ||
                (curr->val < prev->val && curr->val < nxt->val);

            if (isCritical) {
                if (first == -1) {
                    first = pos;
                } else {
                    minDist = min(minDist, pos - last);
                }
                last = pos;
            }

            prev = curr;
            curr = nxt;
            pos++;
        }

        if (first == -1 || first == last)
            return {-1, -1};

        return {minDist, last - first};
    }
};