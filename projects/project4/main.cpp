#include "expression.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    expression w;
    w.show();
    return a.exec();
}
