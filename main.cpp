#include "texteditor.h"
#include <QApplication>
#include <stack>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextEditor w;
    w.show();

    return a.exec();
}
