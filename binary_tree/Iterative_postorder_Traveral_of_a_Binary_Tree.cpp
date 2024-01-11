#include"Binary_Tree.h"
#include"stack"
#include<vector>
using namespace std;
//将“根右左”的前序遍历倒转过来即为后序遍历
void travel_postorder(TreeNode* root,vector<int>& answer){
    stack<TreeNode*> ans;
    root->val = 0;
    ans.push(root);
    TreeNode*p = root;
    while(!ans.empty()){
        p = ans.top();
        //visit p
        answer.push_back(p->val);
        ans.pop();
        if(p->left){
            ans.push(p->left);
        }
        if(p->right){         //push leftchild into stack temporarily, next cycle will get it and visit it;
            ans.push(p->right);
        }

    }
    answer.reserve(answer.size());
}