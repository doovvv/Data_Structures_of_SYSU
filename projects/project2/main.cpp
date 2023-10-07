#include "arithmetic.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    arithmetic w;
    w.show();
    w.setWindowTitle("doov's 计算器");
    //QtGui.QIcon q("D:\8725529_calculator_alt_icon.png");
    w.setWindowIcon(QIcon("D:/8725529_calculator_alt_icon.png"));
    return a.exec();
}
