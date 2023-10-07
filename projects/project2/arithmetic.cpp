#include "arithmetic.h"
#include "ui_arithmetic.h"
#include<QButtonGroup>
#include<math.h>
arithmetic::arithmetic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::arithmetic)
{
    ui->setupUi(this);
    iniUI();

    //nums_top = 0;
    //opre_top = 0;
    //nums_stack = new int[100];
    //opre_stack = new char[100];
}

arithmetic::~arithmetic()
{
    delete ui;
}

void arithmetic::iniUI(){
    //找到所有按钮，放到一个按钮组里面
    auto buttonGroup = new QButtonGroup(this);
    auto btnList = findChildren<QPushButton*>();
    for (auto btn:btnList) {
        buttonGroup->addButton(btn);
    }
    connect(buttonGroup,&QButtonGroup::buttonClicked,this,&arithmetic::onButtonGroupClicked);
    opre_stack.push_back(6);

}
void arithmetic:: record(){
    QString formula = ui->lineEdit->text();
    formula.push_back('#');
    int n = formula.length();
    for(int i = 0;i<n;i++){
        int j = i;
        while((formula[j]<='9' && formula[j]>='0') || formula[j] == '.' ){
            j++;
        }
        if(j != i){

            QString s = formula.mid(i,j-i);
            nums_stack.push_back(s.toDouble());
            i = j-1;
            //qInfo()<<s.toDouble();
        }
        else{
            int num;
            if(formula[i] == '+'){
                num = 0;
            }
            else if(formula[i] == '-'){
                num = 1;
            }
            else if(formula[i] == '*'){
                num = 2;
            }
            else if(formula[i] == '/'){
                num = 3;
            }
            else if(formula[i] == '('){
                num = 4;
            }
            else if(formula[i] == ')'){
                num = 5;
            }
            else if(formula[i] == '^'){
                num = 7;
            }
            else if(formula[i] == '%'){
                num = 8;
            }
            else/* if(formula[i] == '#')*/{
                num = 6;
            }
            while(!opre_stack.empty()){
                int num3 = opre_stack.back();
                if(prior[num3][num] == 0){
                    opre_stack.push_back(num);
                    qInfo()<<num3<<"0";
                    break;
                }
                else if(prior[num3][num] == 1){
                    double num1=0;//右操作数
                    if(!nums_stack.empty()){
                        num1 = nums_stack.back();
                    }
                    double num2=0;//左操作数
                    qInfo()<<nums_stack.empty();
                    nums_stack.pop_back();
                    if(!nums_stack.empty()){
                        num2 = nums_stack.back();
                    }



                    qInfo()<<num<<" "<<num3;
                        //if(num3 == 1 && (nums_stack.empty() || opre_stack[opre_stack.size()-2] == 4)){
                            //num2 = 0;
                        //}
                    nums_stack.pop_back();
                    opre_stack.pop_back();
                    switch(num3){
                    case 0:nums_stack.push_back(num1+num2);break;
                    case 1:nums_stack.push_back(num2-num1);break;
                    case 2:nums_stack.push_back(num1*num2);break;
                    case 3:nums_stack.push_back(num2/num1);break;
                    case 7:nums_stack.push_back(pow(num2,num1));break;
                    case 8:nums_stack.push_back((int)num2%(int)num1);break;
                    }
                }

                else if(prior[num3][num] == 2){opre_stack.pop_back();qInfo()<<"num2";break;}


                }
            }

            //opre_stack.push_back(formula[i]);
        }
    ui->lineEdit->clear();
    ui->lineEdit->insert(QString::number(nums_stack.back(),'g',10));
    int p = nums_stack.size();
    for(int i = 0;i<p;i++){
        qInfo()<<nums_stack[i];
    }
}
void arithmetic::clear(){
    nums_stack.clear();
    opre_stack.clear();
    opre_stack.push_back(6);
    ui->lineEdit->clear();
}
void arithmetic::onButtonGroupClicked(QAbstractButton* btn){
    QString name = btn->text();
    ui->lineEdit->insert(name);
    if(name == "="){
        record();
    }
    if(name == "C"){
        clear();
    }
}
