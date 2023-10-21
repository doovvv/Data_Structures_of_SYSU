#include "Binary_Tree.h"
#include <iostream>
using namespace std;
    //递归前序遍历
    void travel_strata_order(TreeNode* root){
        if(root == nullptr) {
            return;
        }
        // visit
        travel_strata_order(root->left);
        travel_strata_order(root->right);
    }

    //递归中序遍历
    void midOrder(TreeNode* root){
        if(root == NULL){
            return;
        }
        midOrder(root->left);
        //visit;
        midOrder(root->right);
    }
    void postOrder(TreeNode* root){
        if(root == NULL){
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        //visit;
    }
//
// Created by doov on 2023/8/3.
//
