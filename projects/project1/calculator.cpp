#include "calculator.h"
#include "ui_calculator.h"
#include<Qbuttongroup.h>
#include<vector>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    iniUI();
}

Widget::~Widget()
{
    delete ui;
    Node* prev = heada;
    while(prev){
        Node* post = prev->next;
        delete prev;
        prev = post;
    }
}


void Widget::iniUI(){
    //找到所有按钮，放到一个按钮组里面
    auto buttonGroup = new QButtonGroup(this);
    auto btnList = findChildren<QPushButton*>();
    for (auto btn:btnList) {
      buttonGroup->addButton(btn);
    }
    connect(buttonGroup,&QButtonGroup::buttonClicked,this,&Widget::onButtonGroupClicked);
    //ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    //ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);

    heada = new Node();
    tempa = heada;
    headb = new Node();
    tempb = headb;
    check = 0;
    c_or_i =0;
    lengtha = 0;
    lengthb = 0;
    x0.resize(1);
}

void Widget::Input(Node* head){
    //clear(head);
    c_or_i = 0;
    if(head == heada){
      check = 0;
      ui->lineEdit->clear();
      ui->lineEdit->setFocus();
      lengtha = 0;
      ui->lineEdit->insert("请输入多项式a: ");
    }
    else{
      check = 1;
      ui->lineEdit_2->clear();
      ui->lineEdit_2->setFocus();
      lengthb = 0;
      ui->lineEdit_2->insert("请输入多项式b: ");
    }

}

double Widget::Last_num(QLineEdit* le){
    int currentPosition = le->cursorPosition();
    int pos;// 获取当前光标位置
    for( pos = currentPosition-1;pos>=0;pos--){
      if(pos>= 0 && le->text().at(pos) == ' '){
          break;
      }
    }
    le->setSelection(pos,currentPosition);
    double val = le->selectedText().toDouble();
    le->setCursorPosition(currentPosition);
    return val;
}

void Widget::Input_num(QLineEdit* le,QString name){
    int currentPosition = le->cursorPosition(); // 获取当前光标位置
    int selectionStart = currentPosition - 2; // 上一个字符的位置
    int selectionEnd = currentPosition;

    if (selectionStart >= 0) { // 确保不会越界
      le->setSelection(selectionStart, selectionEnd);
    }
    if(le->selectedText() == " 0" && name != "."){
      le->insert(" "+name);
      le->setCursorPosition(selectionEnd);

    }
    else{
      le->setCursorPosition(selectionEnd);
      le->insert(name);
    }
}

void Widget::Space(QString name){
    if(check == 0){
      double val = Last_num(ui->lineEdit);
      qInfo()<<val;
      //if(c_or_i == 0){
          //lengtha =2* val;
      //}
      if(c_or_i % 2 == 0){
          Node* node = new Node(val);
          tempa = node;
      }
      else if(c_or_i% 2 == 1){
          tempa->index = val;
          if(c_or_i == 1){
              heada->next = tempa;
          }
          else{
              qInfo()<<tempa->index;
              insert(tempa,heada);
          }
      }

      ui->lineEdit->insert(" ");
    }
    else if(check == 1){
      double val = Last_num(ui->lineEdit_2);
      //if(c_or_i == 0){
          //lengthb = 2*val;
      //}
       if(c_or_i % 2 == 0){
          Node* node = new Node(val);
          tempb = node;
      }
      else if(c_or_i% 2 == 1){
          tempb->index = val;
          if(c_or_i == 1){
              headb->next = tempb;
          }
          else{
              insert(tempb,headb);
          }
      }
      ui->lineEdit_2->insert(" ");
      qInfo()<<lengthb;
    }
    c_or_i++;
}

void Widget::Exchange(Node* heada,Node* headb){
    Node* temp = heada->next;
    heada->next = headb->next;
    headb->next = temp;
}

void Widget::Integral(Node* head){
    Node* headc = new Node();
    for(Node* node = head->next;node;node = node->next){
      Node* nodec = new Node(node->coefficient/(node->index+1),node->index+1);
      insert(nodec,headc);
    }
    display(headc);
    clear(headc);
    delete headc;
}


void Widget::insert(Node* node,Node* head){
    Node* temp = head->next;
    Node* prev = head;
    int flag = 0;
    for(;temp;temp = temp->next){
      if(temp->index<node->index){
          node->next = temp;
          prev->next = node;
          flag = 1;
          break;
      }
      else if(temp->index == node->index){
          temp->coefficient += node->coefficient;
          flag = 1;
          delete node;
          break;
      }
      prev = prev->next;
    }
    if(flag == 0){
      prev->next = node;
    }
}

void Widget::display(Node* head){
    Node* node = head->next;
    ui->lineEdit_3->clear();
    for(;node;node= node->next){
      if(node->coefficient != 1 && node->coefficient>0 && node!=head->next){
          ui->lineEdit_3->insert("+"+QString::number(node->coefficient));
      }
      else if(node == head->next && node->coefficient!=1 && node->coefficient>0){
          ui->lineEdit_3->insert(QString::number(node->coefficient));
      }
      else if(node->coefficient == 1 && node!=head->next && node->index != 0){
          ui->lineEdit_3->insert("+");
      }
      else if(node->coefficient!=-1 && node->coefficient<0){
          ui->lineEdit_3->insert(QString::number(node->coefficient));
      }
      else if(node->coefficient == -1 && node->index!= 0){
          ui->lineEdit_3->insert("-");
      }
      else if(node->coefficient == 0 && node != head->next){
          continue;
      }
      else if(node->coefficient == 0 && node == head->next){
          ui->lineEdit_3->insert("0");
          continue;
      }
      else if(node->coefficient == 1 && node->index == 0 && node !=head->next ){
          ui->lineEdit_3->insert("+1");
      }
      else if(node->coefficient == 1 && node->index == 0 && node ==head->next){
          ui->lineEdit_3->insert("1");
      }
      else if(node->coefficient == -1 && node->index == 0){
          ui->lineEdit_3->insert("-1");
      }
      int num = node->index;
      int minus_sign = 0;
      if(num<0){
          minus_sign = 1;
          num = -num;
      }
      std::vector<int> bits;
      while(num){
          int bit = num%10;
          bits.push_back(bit);
          num /= 10;

      }
      for(int i = bits.size()-1;i>=0;i--){
          if(i == (bits.size()-1)){
              ui->lineEdit_3->insert(("x"));
              if(minus_sign ==1){
                  ui->lineEdit_3->insert(("\u207B"));
              }
          }
          switch(bits[i]){
          case 0:if(i == bits.size()-1)break;else ui->lineEdit_3->insert("⁰");break;
          case 2:ui->lineEdit_3->insert("\u00B2");break;
          case 3:ui->lineEdit_3->insert("\u00B3");break;
          case 4:ui->lineEdit_3->insert("\u2074");break;
          case 5:ui->lineEdit_3->insert("\u2075");break;
          case 6:ui->lineEdit_3->insert("\u2076");break;
          case 7:ui->lineEdit_3->insert("\u2077");break;
          case 8:ui->lineEdit_3->insert("\u2078");break;
          case 9:ui->lineEdit_3->insert("\u2079");break;
          }
          if(bits[i] == 1){
              if(bits.size()>1){
                  ui->lineEdit_3->insert("\u00B9");
              }
          }
      }
    }
}

void Widget::clear(Node* head){
    Node* prev = head->next;
    while(prev){
      Node* post = prev->next;
      delete prev;
      prev = post;
    }
}

bool Widget::is_empty(Node* head){
    return head->next == nullptr;
}

double Widget::calculate_x(Node* head,int x0){
    double sum = 0;
    Node* node = head->next;
    for(;node;node = node->next){
      double num = node->coefficient;
      int i = node->index;
      while(i--){
          num *= x0;
      }
      sum += num;
    }
    return sum;
}

void Widget::Derivation(Node* head){
    Node* node = head->next;
    Node* headc = new Node();
    Node* nodec = headc;
    for(;node;node = node->next){
      if(node->index == 0){
          continue;
      }
      else{
          Node* tempc = new Node(node->coefficient*node->index,node->index-1);
          nodec->next = tempc;
          nodec = tempc;
      }
    }
    display(headc);
    clear(headc);
    delete headc;
}

void Widget::Enter(){
    if(check == 0){
      ui->lineEdit->setFocus();
      int currentPosition = ui->lineEdit->cursorPosition();
      int pos;// 获取当前光标位置
      for( pos = currentPosition-1;pos>=0;pos--){
          if(pos>= 0 && ui->lineEdit->text().at(pos) == ' '){
              break;
          }
      }
      ui->lineEdit->setSelection(pos,currentPosition);
      double val = ui->lineEdit->selectedText().toDouble();
      if(c_or_i % 2 == 0){
          ui->lineEdit->clear();
          ui->lineEdit->insert("wrong input");
      }
      else{
          tempa->index = val;
      }
      if(c_or_i == 1){
          heada->next = tempa;
      }
      else{
          insert(tempa,heada);
      }

    }
    else if(check == 1){
      ui->lineEdit_2->setFocus();
      int currentPosition = ui->lineEdit_2->cursorPosition();
      int pos;// 获取当前光标位置
      for( pos = currentPosition-1;pos>=0;pos--){
          if(pos>= 0 && ui->lineEdit_2->text().at(pos) == ' '){
              break;
          }
      }
      ui->lineEdit_2->setSelection(pos,currentPosition);
      double val = ui->lineEdit_2->selectedText().toDouble();
      if(c_or_i % 2 == 0){
          ui->lineEdit_2->clear();
          ui->lineEdit_2->insert("wrong input");
      }
      else{
          tempb->index = val;
      }
      if(c_or_i == 1){
          headb->next = tempb;
      }
      else{
          insert(tempb,headb);
      }

    }
}

void Widget::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
      Enter();
    }
    else if((event->key() >= Qt::Key_0 && event->key()<=Qt::Key_9) || (event->text() == "-")||(event->text() == ".")){

      if(check == 0){
          qInfo()<<event->text();
          Input_num(ui->lineEdit,event->text());
      }
       else if(check ==1){
          Input_num(ui->lineEdit_2,event->text());
      }
      else if(check == 2){
          Input_num(ui->lineEdit,event->text());
      }
    }
    else if(event->key() == Qt::Key_Space){
      Space(event->text());
    }
    //QWidget::keyPressEvent(event);
}

void Widget::Multiply(Node* heada,Node* headb){
    Node* headc = new Node();
    Node* nodec = headc;
    Node* nodea = heada->next;
    Node* nodeb;
    for(;nodea;nodea = nodea->next){
      for(nodeb = headb->next;nodeb;nodeb = nodeb->next){
          Node* tempc = new Node(nodea->coefficient*nodeb->coefficient,nodea->index+nodeb->index);
          insert(tempc,headc);
      }
    }
    display(headc);
    clear(headc);
    delete headc;
}


void Widget:: onButtonGroupClicked(QAbstractButton* btn){
    qInfo()<<btn->text();
    QString name = btn->text();

    //决定输入a还是b
    if(name == "输入多项式a"){
      Input(heada);
    }
    else if(name =="输入多项式b"){
      Input(headb);
    }

    //输入空格，把系数指数存进链表中
    else if(name == "空格"){
      Space(name);
    }

    //输入在a中的数字
    else if((name >="0" && name<="9" && check == 0) || (name == "." && check == 0) ||(name =="-" && check == 0)){
      Input_num(ui->lineEdit,name);
    }



    //输入在b中的数字
    else if((name >="0" && name<="9" && check == 1) || (name == "." && check == 1)||(name == "-" && check == 1)){
      Input_num(ui->lineEdit_2,name);
    }

    else if((name >="0" && name<="9" && check == 2) || (name == "." && check == 2)||(name == "-" && check == 2)){
      int currentPosition = ui->lineEdit->cursorPosition(); // 获取当前光标位置
      int selectionStart = currentPosition - 2; // 上一个字符的位置
      int selectionEnd = currentPosition;

      if (selectionStart >= 0) { // 确保不会越界
            ui->lineEdit->setSelection(selectionStart, selectionEnd);
      }
      if(ui->lineEdit->selectedText() == " 0" && name != "."){
            ui->lineEdit->insert(" "+name);
            ui->lineEdit->setCursorPosition(selectionEnd);

      }
      else{
            ui->lineEdit->setCursorPosition(selectionEnd);
            ui->lineEdit->insert(name);
      }
    }

    else if(name == "展示a"){
      display(heada);
    }


    else if(name == "展示b"){
      display(headb);
    }



    else if(name == "a+b"){
      ui->lineEdit_3->clear();
      Node* headc = new Node();
      int lengthc = 0;
      Node* nodea = heada->next;
      Node* nodeb = headb->next;
      Node* nodec;
      for(;nodea;nodea = nodea->next){
            for(nodeb = headb->next;nodeb;nodeb = nodeb->next){
              if(nodea->index == nodeb->index){
                  nodec = new Node((nodea->coefficient+nodeb->coefficient),(nodea->index));
                  if(lengthc == 0){
                      headc->next = nodec;
                  }
                  else{
                      qInfo()<<nodec->coefficient;
                      insert(nodec,headc);
                  }
                  lengthc++;
              }
              else if(nodea->index>nodeb->index){
                  break;
              }
            }

      }
      int flag;
      for(nodea = heada->next;nodea;nodea = nodea->next){
            flag = 0;
            for(nodec = headc->next;nodec;nodec = nodec->next){
              if(nodea->index == nodec->index){
                  flag = 1;
              }
            }
            if(flag == 0){
              Node* node = new Node(nodea->coefficient,nodea->index);
              insert(node,headc);
            }
      }
      for(nodeb = headb->next;nodeb;nodeb = nodeb->next){
            flag = 0;
            for(nodec = headc->next;nodec;nodec = nodec->next){
              if(nodeb->index == nodec->index){
                  flag = 1;
              }
            }
            if(flag == 0){
              Node* node = new Node(nodeb->coefficient,nodeb->index);
              insert(node,headc);
            }
      }
      display(headc);
      clear(headc);
    }


    else if(name == "a-b"){
      ui->lineEdit_3->clear();
      Node* headc = new Node();
      int lengthc = 0;
      Node* nodea = heada->next;
      Node* nodeb = headb->next;
      Node* nodec;
      for(;nodea;nodea = nodea->next){
            for(nodeb = headb->next;nodeb;nodeb = nodeb->next){
              if(nodea->index == nodeb->index){
                  nodec = new Node((nodea->coefficient-nodeb->coefficient),(nodea->index));
                  if(lengthc == 0){
                      headc->next = nodec;
                  }
                  else{
                      qInfo()<<nodec->coefficient;
                      insert(nodec,headc);
                  }
                  lengthc++;
              }
              else if(nodea->index>nodeb->index){
                  break;
              }
            }

      }
      int flag;
      for(nodea = heada->next;nodea;nodea = nodea->next){
            flag = 0;
            for(nodec = headc->next;nodec;nodec = nodec->next){
              if(nodea->index == nodec->index){
                  flag = 1;
              }
            }
            if(flag == 0){
              Node* node = new Node(nodea->coefficient,nodea->index);
              insert(node,headc);
            }
      }
      for(nodeb = headb->next;nodeb;nodeb = nodeb->next){
            flag = 0;
            for(nodec = headc->next;nodec;nodec = nodec->next){
              if(nodeb->index == nodec->index){
                  flag = 1;
              }
            }
            if(flag == 0){
              Node* node = new Node(-nodeb->coefficient,nodeb->index);
              insert(node,headc);
            }
      }
      display(headc);
      clear(headc);
    }

    else if(name == "输入x₀"){
       ui->lineEdit->clear();
       ui->lineEdit->insert("请输入x₀: ");
      ui->lineEdit->setFocus();
       x0.clear();
      check = 2;
    }
    else if(name == "计算x₀"){
      if(x0.empty()){
            int currentPosition = ui->lineEdit->cursorPosition();
            int pos;// 获取当前光标位置
            for( pos = currentPosition-1;pos>=0;pos--){
              if(pos>= 0 && ui->lineEdit->text().at(pos) == ' '){
                  break;
              }
            }
            ui->lineEdit->setSelection(pos,currentPosition);
            double val = ui->lineEdit->selectedText().toDouble();
            x0.push_back(val);
      }
      ui->lineEdit_3->clear();
      ui->lineEdit_3->insert(QString::number(calculate_x(heada,x0[0])));
    }

    else if(name == "对a求导"){
      Derivation(heada);
    }

    else if(name == "a*b"){
      Multiply(heada,headb);
    }
    else if(name == "确认"){
      Enter();
    }
    else if(name == "a<->b"){
      Exchange(heada,headb);
    }
    else if(name == "对a积分"){
      Integral(heada);
    }

}
