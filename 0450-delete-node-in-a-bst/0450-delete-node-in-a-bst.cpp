/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode *successive(TreeNode *curr){
        curr=curr->right;
        while(curr!=NULL && curr->left!=NULL){
            curr=curr->left;
        }
        return curr;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==NULL){
            return root;
        }
        else if(root->val<key){
            root->right=deleteNode(root->right,key);
        }
        else if(root->val>key){
            root->left=deleteNode(root->left,key);
        }
        else if(root->left==NULL){
            TreeNode *temp=root;
            root=root->right;
            delete temp;
        }
        else if(root->right==NULL){
            TreeNode *temp=root;
            root=root->left;
            delete temp;
        }
        else{
            TreeNode *succ=successive(root);
            root->val=succ->val;
            root->right=deleteNode(root->right,succ->val);
        }
        return root;
    }
};