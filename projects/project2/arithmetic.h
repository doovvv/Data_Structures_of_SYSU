#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <QWidget>
#include<QAbstractButton>
#include<vector>
using namespace  std;

QT_BEGIN_NAMESPACE
namespace Ui { class arithmetic; }
QT_END_NAMESPACE

class arithmetic : public QWidget
{
    Q_OBJECT

public:
    arithmetic(QWidget *parent = nullptr);
    ~arithmetic();
    void iniUI();
    void record();
    void clear();
public slots:
    void onButtonGroupClicked(QAbstractButton* btn);

private:
    Ui::arithmetic *ui;
    vector<double> nums_stack;
    vector<int> opre_stack;
    int nums_top;
    int opre_top;
    int prior[9][9] = {{1,1,0,0,0,1,1,0,0},
                       {1,1,0,0,0,1,1,0,0},
                       {1,1,1,1,0,1,1,1,1},
                       {1,1,1,1,0,1,1,1,1},
                       {0,0,0,0,0,2,0,0,0},
                       {1,1,1,1,1,0,1,1,1},
                       {0,0,0,0,0,0,2,0,0},
                       {1,1,1,1,0,1,1,1,1},
                       {1,1,1,1,0,1,1,1,1}};
    //int* nums_stack;
    //char* opre_stack;
};
#endif // ARITHMETIC_H
