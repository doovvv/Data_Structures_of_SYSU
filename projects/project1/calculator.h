#ifndef WIDGET_H
#define WIDGET_H
#include "ui_calculator.h"
#include <QWidget>
#include <QAbstractButton>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Node{
public:
    double coefficient;
    double index;
    Node* next;
    Node(double c = 0,int i = 0,Node* n = nullptr):coefficient(c),index(i),next(n){}
};
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void iniUI();
    void Input(Node* head);//用于确定用户输入多项式a还是b
    double Last_num(QLineEdit* le);
    void Input_num(QLineEdit* le,QString name);
    void Enter();
    void Space(QString name);
    void Exchange(Node* heada,Node* headb);
    void Integral(Node* head);
    void display(Node* head);
    void insert(Node* node,Node* head);
    void clear(Node* head);
    bool is_empty(Node* head);
    double calculate_x(Node* head,int x0);
    void Derivation(Node* head);
    void Multiply(Node* heada,Node* headb);
    void keyPressEvent(QKeyEvent* event);
public slots:
    void onButtonGroupClicked(QAbstractButton* btn);

private:
    Ui::Widget *ui;
    Node* heada;
    Node* tempa;
    Node* headb;
    Node* tempb;
    int check;
    int c_or_i;
    int lengtha;
    int lengthb;
    std::vector<double> x0;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if ((obj == ui->lineEdit || obj == ui->lineEdit_2 || ui->lineEdit_3) && event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            // 然后将事件传递给 QWidget 的事件处理函数S
            QApplication::sendEvent(this, keyEvent);
            return true; // 表示事件已处理
        }

        return QWidget::eventFilter(obj, event);
    }

};
#endif // WIDGET_H
