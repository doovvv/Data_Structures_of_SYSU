#include "Binary_Tree.h"
#include "stack"
using namespace std;
int travel_prooredr(TreeNode* root){
    stack<TreeNode*> ans;
    root->val = 0;
    ans.push(root);
    TreeNode*p = root;
    while(!ans.empty()){
        p = ans.top();
        //visit p
        ans.pop();
        if(p->left){
            ans.push(p->left);
        }
        if(p->right){
            ans.push(p->right);
        }

    }
}
//
// Created by doov on 2023/7/29.
//
