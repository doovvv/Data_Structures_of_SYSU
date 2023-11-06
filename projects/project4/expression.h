#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "ui_expression.h"
#include <QWidget>
#include<QButtonGroup>
#include<QPushButton>
#include<QKeyEvent>
#include<QApplication>
#include<QString>
#include<QChar>
#include<map>
#include<math.h>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class expression; }
QT_END_NAMESPACE
struct TreeNode {
    int value;
    QChar data;
    TreeNode* left;
    TreeNode* right;
};
class expression : public QWidget
{
    Q_OBJECT

public:
    expression(QWidget *parent = nullptr);
    ~expression();
    void iniUI();
    void ReadExpr();
    void WriteExpr();
    void keyPressEvent(QKeyEvent* event);
    void Assign();
    void enter();
    void travel_assign(TreeNode* root,map<QChar,int> assign);
    void Value();
    int travel_value(TreeNode* root);
    void CompoundExpr();
    void MergeConst();
    bool travel_merge(TreeNode* root);
    void Diff();
    void travel_diff(TreeNode* root);
public slots:
    void onButtonGroupClicked(QAbstractButton* btn);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if ((obj == ui->lineEdit) && event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            // 然后将事件传递给 QWidget 的事件处理函数S
            QApplication::sendEvent(this, keyEvent);
            return true; // 表示事件已处理
        }

        return QWidget::eventFilter(obj, event);
    }

private:
    Ui::expression *ui;
    TreeNode* root;
    TreeNode* anotherroot;
    QString text;
    QChar p;
    QChar v;
    int opretion;
};

#endif // EXPRESSION_H
