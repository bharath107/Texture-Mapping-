#include "texture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    texture w;
    w.show();
    return a.exec();
}
