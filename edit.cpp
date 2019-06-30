#include "edit.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "texteditor.h"
Edit::Edit(QWidget *parent) : QTextEdit(parent)
{

}
void Edit::contextMenuEvent(QContextMenuEvent *e)
//重定义右键菜单
{
//    QMenu* menu = new QMenu;
//    QAction* undo =menu->addAction("撤销",this,SLOT(Undo()));
//    undo->setEnabled(document()->isUndoAvailable());
//    menu->exec(e->globalPos());
//    delete menu;
}
