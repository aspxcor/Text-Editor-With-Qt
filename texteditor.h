#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include "finddlg.h"
#include <QTextCharFormat>
#include "edit.h"
namespace Ui {
class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();
    void newFile();   // 新建操作
    bool maybeSave(); // 判断是否需要保存
    bool save();      // 保存操作
    bool saveAs();    // 另存为操作
    bool saveFile(const QString &fileName); // 保存文件
    bool loadFile(const QString &fileName); // 加载文件
    int replaceIndex;//替换文本下标
    int replaceLength;//替换文本长度
    int lastIndex;//上一个查找到的文本下标
    int lastLength;//上一个查找到的文本的长度
    void mergeformat(const QTextCharFormat &fmt);
    void textBold();//加粗
    void textItalic();//斜体
    void textUnderline();//下划线
    void textColor();
    void textCurrentFormatChanged(const QTextCharFormat & fmt);//根据光标处格式改变菜单栏
    void textFont();
    QStack<QString> strUndo;
    QStack<QString> strRedo;
    void refreshStack();
    void resetStack();
    void textCopy();
    void textCut();
    void textPaste();
    QString pasteBoard;
    //void createPdf();
public slots:
    void on_action_Undo_triggered();
private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SavaAs_triggered();

    void on_action_Open_triggered();


    void on_action_Find_triggered();

    void receiveIndex(int index, int length);  //接受替换信号的槽函数

    void receiveQString(QString replaceStr);

    void on_action_Bold_triggered();

    void on_action_Italic_triggered();

    void on_action_Underline_triggered();

    void on_action_Left_triggered();

    void on_action_Right_triggered();

    void on_action_Center_triggered();



    void on_action_Color_triggered();

    void on_action_Font_triggered();
    void on_action_Just_triggered();
    void on_action_Y_triggered();
    void on_textEdit_textChanged();
    void on_action_selectAll_triggered();
    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Cut_triggered();

private:
    Edit edit;
    Ui::TextEditor *ui;
    // 为真表示文件没有保存过，为假表示文件已经被保存过了
    bool isUntitled;
    // 保存当前文件的路径
    QString curFile;
    // 查找
    FindDlg *f;  // 查找子窗体
    bool isUndo=0;
    bool isRedo=0;
    bool isLoadFile=0;
    bool undoIsUsed=0;
};

#endif // TEXTEDITOR_H
