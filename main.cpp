#include "lu_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LU_main_window w;
    w.show();

    return a.exec();
}
