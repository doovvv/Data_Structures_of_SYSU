#include "expression.h"
#include "ui_expression.h"

TreeNode* createNode(QChar data);
expression::expression(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::expression)
{
    ui->setupUi(this);
    opretion = 0;
    iniUI();
}

expression::~expression()
{
    delete ui;
}
void expression::iniUI(){
    //找到所有按钮，放到一个按钮组里面
    auto buttonGroup = new QButtonGroup(this);
    auto btnList = findChildren<QPushButton*>();
    for (auto btn:btnList) {
        buttonGroup->addButton(btn);
    }
    connect(buttonGroup,&QButtonGroup::buttonClicked,this,&expression::onButtonGroupClicked);
    ui->lineEdit->installEventFilter(this);
}
TreeNode* createNode(QChar data,int num) {
    TreeNode* node = new TreeNode;
    node->value = num;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}
bool isOperator(QChar c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||  c == '%');
}
TreeNode* prefixToBinaryTree(QString text,int& index){ //前缀表达式转成二叉树
    if(index >= text.size()){
        return nullptr;
    }
    QChar token = text[index];
    index++;
    if(isOperator(token)){
        TreeNode* node;

        node = createNode(token,0);

        node->left = prefixToBinaryTree(text,index);
        node->right = prefixToBinaryTree(text,index);
        return node;
    }
    else{
        return createNode(token,(QString(token).toInt()));
    }
}
QString BinaryTreeToinfix(TreeNode* root){ //二叉树转成前缀表达式
    if(root == nullptr){
        return "";
    }
    if(root->left == nullptr && root->right == nullptr){
        return QString(1,root->data);
    }
    QString leftstring = BinaryTreeToinfix(root->left);
    QString rightstring = BinaryTreeToinfix(root->right);
    return "("+leftstring+root->data+rightstring+")";
}
void expression::ReadExpr(){
    ui->lineEdit->clear();
    //ui->lineEdit->insert("input your prefix expression: ");
    opretion = 0;
}
void expression::WriteExpr(){
    ui->lineEdit->clear();
    if(root->left == nullptr && root->right == nullptr){
        ui->lineEdit->insert(root->data);
    }
    else{
        QString expr = BinaryTreeToinfix(root);
        ui->lineEdit->insert(expr);
    }

}
void expression::Assign(){
    opretion = 1;
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}
void expression::travel_assign(TreeNode* root,map<QChar,int> assign){
    if(root == nullptr){
        return;
    }
    else if(assign.find(root->data) != assign.end()){
        root->value = assign[root->data];
    }
    travel_assign(root->left,assign);
    travel_assign(root->right,assign);
}
void expression::enter(){
    if(opretion == 1){
        QString text = ui->lineEdit->text();
        map<QChar,int> assign;
        QChar c;
        int num;
        for(int i = 0;i<text.size();i++){
            if(text[i]<='9' && text[i]>='0'){
                num = ((QString)text[i]).toInt();
                assign[c] = num;
            }
            else if(text[i] != ' '){
                c = text[i];
            }
        }
        travel_assign(root,assign);
        ui->lineEdit->clear();
        ui->lineEdit->insert("Assign Done");
    }
    else if(opretion == 0){
        text = ui->lineEdit->text();
        ui->lineEdit->clear();
        ui->lineEdit->insert("which expression(E1 or E2): ");
        opretion = 2;
    }
    else if(opretion == 2){
        int index = 0;
        QString choose = ui->lineEdit->text();
        if(choose == "which expression(E1 or E2): E1"){
            root = prefixToBinaryTree(text,index);
            ui->lineEdit->clear();
            ui->lineEdit->insert("Choose Done");
        }
        else if(choose == "which expression(E1 or E2): E2"){
            anotherroot = prefixToBinaryTree(text,index);
            ui->lineEdit->clear();
            ui->lineEdit->insert("Choose Done");
        }
        else{
            ui->lineEdit->clear();
            ui->lineEdit->insert("wrong input");
        }
    }
    else if(opretion == 3){
        p = ui->lineEdit->text().back();
        TreeNode* root1 = root;
        root = createNode(p,0);
        root->left = root1;
        root->right = anotherroot;
        ui->lineEdit->clear();
        ui->lineEdit->insert("CompoundExpr Done");
    }
    else if(opretion == 4){
        v = ui->lineEdit->text().back();

    }
}
void expression::travel_diff(TreeNode* root){
    //if()
}
void expression::Value(){
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
    int output = travel_value( root);
    ui->lineEdit->insert(QString::number(output));
}
int expression::travel_value(TreeNode* root){
    if(root->left == nullptr&&root->right == nullptr){
        return root->value;
    }
    else{
        if(root->data == '+'){
            return travel_value(root->left)+travel_value(root->right);
        }
        else if(root->data == '-'){
            return travel_value(root->left)-travel_value(root->right);
        }
        else if(root->data == '*'){
            return travel_value(root->left)*travel_value(root->right);
        }
        else if(root->data == '/'){
            return travel_value(root->left)/travel_value(root->right);
        }
        else if(root->data == '%'){
            return travel_value(root->left)/travel_value(root->right);
        }
        else/*(root->data == '^')*/{
            return pow(travel_value(root->left),travel_value(root->right));
        }
    }
}
void expression::CompoundExpr(){
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
    ui->lineEdit->insert("please input p: ");
    opretion = 3;

}
void expression::Diff(){
    ui->lineEdit->clear();
    ui->lineEdit->insert("which veriable: ");
    opretion = 4;
}
void expression::onButtonGroupClicked(QAbstractButton* btn){
    QString btntext = btn->text();
    if(btntext == "ReadExpr"){
        ReadExpr();
    }
    else if(btntext == "WriteExpr"){
        WriteExpr();
    }
    else if(btntext == "Assign"){
        Assign();
    }
    else if(btntext == "Value"){
        Value();
    }
    else if(btntext == "CompoundExpr"){
        CompoundExpr();
    }
    else if(btntext == "Exchange"){
        TreeNode* temp = root;
        root = anotherroot;
        anotherroot = temp;
        ui->lineEdit->clear();
        ui->lineEdit->insert("Exchange Done");
    }
    else if(btntext == "MergeConst"){
        MergeConst();
    }
    else{
        ui->lineEdit->insert(btntext);
    }
}
void expression::MergeConst(){
    bool flag = true;
    while(flag){
        flag = travel_merge(root);
    }
}
bool expression::travel_merge(TreeNode* root){
    if(root->left == nullptr || root->right == nullptr){
        return false;
    }
    if(root->left->data<='9' && root->left->data>='0' && root->right->data<='9' && root->right->data>='0'){
        root->value = travel_value(root);
        root->data = QChar(root->value+'0');
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    else{
        return travel_merge(root->left) || travel_merge(root->right);
    }
}
void expression::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        enter();
    }
    else if(event->key() == Qt::Key_Space){
        ui->lineEdit->insert(" ");
    }
    else if(event->key() == Qt::Key_Backspace){
        ui->lineEdit->backspace();
    }
    else{
        ui->lineEdit->insert(event->text());
    }
}
