#include<iostream>
#include<algorithm>
class Node{
    public:
    int data,height;
    Node *left,*right;
};
Node* newNode(int v){
    Node* root =  new Node();
    root->data = v;
    root->height = 1;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}
int getHeight(Node* root){
    return (root == nullptr)? 0 : root->height;
}
int getBanlanceFactor(Node* root){
    return getHeight(root->left)-getHeight(root->right);
}
void updateHeight(Node* root){
    root->height = std::max(getHeight(root->left),getHeight(root->right))+1;
}
void search(Node* root,int v){
    if(root == nullptr){
        return;
    }
    if(root->data == v){
        std::cout<<"Found "<<v<<std::endl;
        return;
    }
    if(v<root->data){
        search(root->left,v);
    }
    else{
        search(root->right,v);
    }
}
void leftRotation(Node*& root){
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}
void rightRotation(Node*& root){
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}
void insert(Node*& root,int x){
    if(root == nullptr){
        root = newNode(x);
        return;
    }
    else if(x == root->data){
        std::cout<<"插入节点失败，节点已存在";
        return;
    }
    else if(x<root->data){
        insert(root->left,x);
        updateHeight(root);
        if(getBanlanceFactor(root) == 2){
            if(getBanlanceFactor(root->left) == 1){
                rightRotation(root);
            }
            else{
                leftRotation(root->left);
                rightRotation(root);
            }
        }
    }
    else{
        insert(root->right,x);
        updateHeight(root);
        if(getBanlanceFactor(root) == -2){
            if(getBanlanceFactor(root->right) == -1){
                leftRotation(root);
            }
            else{
                rightRotation(root->right);
                leftRotation(root);
            }
        }
    }
}
int main(){
    Node* root = nullptr;
    for(int i = 0;i<10;i++){
        insert(root,i);
    }
    return 0;
}
