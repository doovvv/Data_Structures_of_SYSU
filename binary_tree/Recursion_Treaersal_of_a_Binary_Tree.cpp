#include "Binary_Tree.h"
#include <iostream>
using namespace std;
    void travel_strata_order(TreeNode* root){
        if(root == nullptr) {
            return;
        }
        // visit
        travel_strata_order(root->left);
        travel_strata_order(root->right);
    }
//
// Created by doov on 2023/8/3.
//
