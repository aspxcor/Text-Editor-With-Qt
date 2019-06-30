#include "texteditor.h"
#include "ui_texteditor.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>
#include <cstring>
#include "finddlg.h"
#include <QTimer>
#include <QShortcut>
TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    // 初始化文件为未保存状态
    isUntitled = true;
    // 初始化文件名为"未命名.txt"
    curFile = tr("未命名.txt");
    // 初始化窗口标题为文件名
    setWindowTitle(curFile + tr(" - TextEditor"));
    strUndo.push(ui->textEdit->toPlainText());
    connect(ui->textEdit,SIGNAL(textChanged(QString)),this,SLOT(on_textEdit_textChanged));
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::newFile()
{

//   strUndo.push(ui->textEdit->toPlainText());
   if (maybeSave()) {
       isUntitled = true;
       curFile = tr("未命名.txt");
       setWindowTitle(curFile);
       ui->textEdit->clear();
       ui->textEdit->setVisible(true);
//       strUndo.push(ui->textEdit->toPlainText());
   }
   resetStack();
   strUndo.push(ui->textEdit->toPlainText());
}

bool TextEditor::maybeSave()
{
    // 如果文档被更改了
    if ((ui->textEdit->document()->isModified())||((undoIsUsed)&&(!strUndo.isEmpty()))) {
    // 自定义一个警告对话框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);
       box.setText(curFile + tr(" 尚未保存，是否保存？"));
       QPushButton *yesBtn = box.addButton(tr("是(&Y)"),
                        QMessageBox::YesRole);
       box.addButton(tr("否(&N)"), QMessageBox::NoRole);
       QPushButton *cancelBut = box.addButton(tr("取消"),
                        QMessageBox::RejectRole);
       box.exec();
       if (box.clickedButton() == yesBtn)
            return save();
       else if (box.clickedButton() == cancelBut)
            return false;
   }
   // 如果文档没有被更改，则直接返回true
   return true;
}

bool TextEditor::save()
{
   if (isUntitled) {
       return saveAs();
   } else {
       return saveFile(curFile);
   }
}

bool TextEditor::saveAs()
{
   QString fileName = QFileDialog::getSaveFileName(this,
                                         tr("另存为"),curFile);
   if (fileName.isEmpty()) return false;
   return saveFile(fileName);
}
void TextEditor::resetStack()
//实现每次打开新文件时的重置堆栈
{
    strUndo.clear();
    strRedo.clear();
    undoIsUsed=0;
}

bool TextEditor::saveFile(const QString &fileName)
{
   QFile file(fileName);

   if (!file.open(QFile::WriteOnly | QFile::Text)) {

       // %1和%2分别对应后面arg两个参数，/n起换行的作用
       QMessageBox::warning(this, tr("多文档编辑器"),
                   tr("无法写入文件 %1：/n %2")
                  .arg(fileName).arg(file.errorString()));
       return false;
   }
   QTextStream out(&file);
   // 鼠标指针变为等待状态
   QApplication::setOverrideCursor(Qt::WaitCursor);
   out << ui->textEdit->toPlainText();
   // 鼠标指针恢复原来的状态
   QApplication::restoreOverrideCursor();
   isUntitled = false;
   // 获得文件的标准路径
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile);
   return true;
}

bool TextEditor::loadFile(const QString &fileName)
{
   //resetStack();
   QFile file(fileName); // 新建QFile对象
   if (!file.open(QFile::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
       return false; // 只读方式打开文件，出错则提示，并返回false
   }

   QTextStream in(&file); // 新建文本流对象
   QApplication::setOverrideCursor(Qt::WaitCursor);
   // 读取文件的全部文本内容，并添加到编辑器中
//   isLoadFile=1;
//   resetStack();
   ui->textEdit->setPlainText(in.readAll());
   resetStack();
   strUndo.push(ui->textEdit->toPlainText());
   QApplication::restoreOverrideCursor();

   // 设置当前文件
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile + tr(" - TextEditor"));
   //   strRedo.push(ui->textEdit->toPlainText());

//      strRedo.push(ui->textEdit->toPlainText());
      ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
   return true;
}

void TextEditor::receiveIndex(int index, int length)
{
    replaceIndex = index;
    replaceLength = length;

    //先把之前的格式清除
    QTextCursor cursor = ui->textEdit->textCursor(); //获取当前光标
    cursor.setPosition(lastIndex);                       //定位到下标index的位置
    cursor.setPosition(lastIndex+lastLength, QTextCursor::KeepAnchor);   //文本选择范围[index,index + length]
    //选中完成
    QTextCharFormat fmt;//定义突出显示
    fmt.setBackground(Qt::white);//定义显示的格式
    cursor.mergeCharFormat(fmt);//显示

    //再显示当前的格式
    //QTextCursor cursor = ui->textEdit->textCursor(); //获取当前光标
    cursor.setPosition(index);                       //定位到下标index的位置
    cursor.setPosition(index+length, QTextCursor::KeepAnchor);   //文本选择范围[index,index + length]
    //选中完成
    //QTextCharFormat fmt;//定义突出显示
    fmt.setBackground(Qt::yellow);//定义显示的格式
    cursor.mergeCharFormat(fmt);//显示

    lastIndex = index;
    lastLength = length;
}

void TextEditor::receiveQString(QString replaceStr)
{
    ui->textEdit->setPlainText(((ui->textEdit->toPlainText()).replace(replaceIndex, replaceLength, replaceStr)));
}


void TextEditor::on_action_New_triggered()
{
    newFile();
}


void TextEditor::on_action_Save_triggered()
{
    save();
}


void TextEditor::on_action_SavaAs_triggered()
{
    saveAs();
}
void TextEditor::on_action_Undo_triggered()
{
    //测试用
//    isUndo=1;
//    ui->textEdit->setPlainText(strSave.pop());
//    Sleep(2000);
//    if(strSave.isEmpty())
//        ui->textEdit->setPlainText("in undo:empty");
//    else {
//        ui->textEdit->setPlainText("in undo:not empty");
//    }
//    isUndo=0;
    //QString test=strSave.pop();
    //QMessageBox::information(this,tr("hello"),tr(strSave.pop()));
    undoIsUsed=1;
    isUndo=1;
    if(strUndo.size()>1)
    {
        strRedo.push(strUndo.pop());
        ui->textEdit->setPlainText(strUndo.pop());
        strRedo.push(ui->textEdit->toPlainText());
        ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }
    isUndo=0;
}
void TextEditor::on_action_Y_triggered()
{
    isRedo=1;
    if(strRedo.size()>1)
    {
        strUndo.push(strRedo.pop());
        ui->textEdit->setPlainText(strRedo.pop());
        strUndo.push(ui->textEdit->toPlainText());
        ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }
    isRedo=0;
}
void TextEditor::on_action_Open_triggered()
{
//    resetStack();
//    isLoadFile=1;
    if (maybeSave()) {

        QString fileName = QFileDialog::getOpenFileName(this);

        // 如果文件名不为空，则加载文件
        if (!fileName.isEmpty()) {
             loadFile(fileName);
             ui->textEdit->setVisible(true);
        }
    }
}


void TextEditor::on_action_Find_triggered()
{
    //QWidget *new_win = new QWidget();
    //(*new_win).show();
    f = new FindDlg();
    f->nowText = ui->textEdit->toPlainText();
    //连接
    connect(f,SIGNAL(sendIndex(int, int)),this,SLOT(receiveIndex(int, int)));
    connect(f,SIGNAL(sendQString(QString)),this,SLOT(receiveQString(QString)));
    //显示子对话框
    f->show();
    //QMessageBox::information(this,tr("hello"),tr("Mars"));
}

void TextEditor:: mergeformat(const QTextCharFormat &fmt)
{/*设置光标的选区，使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符*/
    QTextCursor cursor =ui->textEdit->textCursor();

    if ( !cursor.hasSelection() )

           cursor.select( QTextCursor::WordUnderCursor );

    cursor.mergeCharFormat( fmt );

    ui->textEdit->mergeCurrentCharFormat( fmt );

}

void TextEditor::textBold()
{
    QTextCharFormat fmt;

    fmt.setFontWeight( ui->action_Bold->isChecked() ? QFont::Bold : QFont::Normal );

    mergeformat( fmt );
}

void TextEditor::textItalic()
{
    QTextCharFormat fmt;

    fmt.setFontItalic( ui->action_Italic->isChecked() );

    mergeformat( fmt );
}

void TextEditor::textUnderline()
{
    QTextCharFormat fmt;

    fmt.setFontUnderline( ui->action_Underline->isChecked() );

    mergeformat( fmt );
}

void TextEditor::textColor()
{
    QColor c =QColorDialog::getColor(Qt::red, this );//调用颜色对话框
    if ( c.isValid() )
    {
         QTextCharFormat fmt;

         fmt.setForeground( c );

         mergeformat( fmt );
    }
}

void TextEditor::textFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok);//调用字体对话框
    if(ok){
        QTextCharFormat fmt;

        fmt.setFont(f );

        mergeformat( fmt );
    }
}


void TextEditor::textCopy()
{
    /*设置光标的选区，
    将选中的字符存入剪贴板*/
    pasteBoard="";
    QTextCursor cursor =ui->textEdit->textCursor();

    pasteBoard=cursor.selectedText();
}

void TextEditor::textCut()
{
    /*设置光标的选区，
    将选中的字符存入剪贴板，同时删除选中内容*/
    QTextCursor cursor =ui->textEdit->textCursor();

    pasteBoard=cursor.selectedText();

    cursor.removeSelectedText();
}

void TextEditor::textPaste()
{
    /*删除当前选中内容，插入剪贴板文本*/
    QTextCursor cursor =ui->textEdit->textCursor();

    cursor.removeSelectedText();

    cursor.insertText(pasteBoard);
}


void TextEditor::textCurrentFormatChanged(const QTextCharFormat &fmt)
{// 当光标所在处字符格式有变化，工具栏做出相应改变
    ui->action_Bold->setChecked( fmt.font().bold() );

    ui->action_Italic->setChecked( fmt.fontItalic() );

    ui->action_Underline->setChecked( fmt.fontUnderline() );
}


void TextEditor::on_action_Bold_triggered()
{
    textBold();
}

void TextEditor::on_action_Italic_triggered()
{
    textItalic();
}

void TextEditor::on_action_Underline_triggered()
{
    textUnderline();
}

void TextEditor::on_action_Left_triggered()
{//左对齐
    ui->textEdit->setAlignment( Qt::AlignLeft );
    if(ui->action_Left->isChecked())//设置成单选
    {
            ui->action_Right->setChecked(false);
            ui->action_Center->setChecked(false);
    }
     else ui->action_Left->setChecked(true);
}

void TextEditor::on_action_Right_triggered()
{//右对齐
    ui->textEdit->setAlignment( Qt::AlignRight );
    if(ui->action_Right->isChecked())//设置成单选
    {
            ui->action_Left->setChecked(false);
            ui->action_Center->setChecked(false);
            ui->action_Just->setChecked(false);
    }
    else ui->action_Right->setChecked(true);
}

void TextEditor::on_action_Center_triggered()
{//居中
    ui->textEdit->setAlignment( Qt::AlignCenter );
    if(ui->action_Center->isChecked())//设置成单选
    {
            ui->action_Just->setChecked(false);
            ui->action_Right->setChecked(false);
            ui->action_Left->setChecked(false);
    }
    else ui->action_Center->setChecked(true);
}

void TextEditor::on_action_Color_triggered()
{
    textColor();
}

void TextEditor::on_action_Font_triggered()
{//字体设置
    textFont();
}

void TextEditor::on_action_Just_triggered()
{//两端对齐
    ui->textEdit->setAlignment( Qt::AlignJustify );
    if(ui->action_Center->isChecked())//设置成单选
    {
            ui->action_Center->setChecked(false);
            ui->action_Right->setChecked(false);
            ui->action_Left->setChecked(false);
    }
    else ui->action_Just->setChecked(true);
}
void TextEditor::on_textEdit_textChanged()
{
    //文本框更新时更新堆栈

//测试代码
    //if(!isUndo)
//        strSave.push(ui->textEdit->toPlainText());
//    if(!strSave.isEmpty()&&!isUndo)
//    {
//        QMessageBox::information(this,tr("hello"),tr("textChanged"));
//    }
    //strSave.push("1234");
//    strRedo.push(ui->textEdit->toPlainText());
//    printf("%d",undoIsUsed);
    if((!isUndo)&&(!isRedo)&&(!isLoadFile))
    {
        strUndo.push(ui->textEdit->toPlainText());
    }
}

void TextEditor::on_action_selectAll_triggered()
{
    ui->textEdit->selectAll();
}
void TextEditor::on_action_Copy_triggered()
{
    textCopy();

}

void TextEditor::on_action_Paste_triggered()
{
    textPaste();
}

void TextEditor::on_action_Cut_triggered()
{
    textCut();
}
