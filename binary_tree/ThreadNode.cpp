#include"ThreadNode.h"
void InitThread(ThreadNode* p,ThreadNode* pre){
    if(p != nullptr){
        InitThread(p->left,pre);//递归左子树
        if(pre != nullptr && pre->right == nullptr){ //根
            pre->right = p;
            pre->rtag = 1;
        }
        pre = p;
        InitThread(p->right,pre);

    }
}