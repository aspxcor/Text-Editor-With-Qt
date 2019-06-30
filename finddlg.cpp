#include "finddlg.h"
#include "ui_finddlg.h"

FindDlg::FindDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("查找/替换 - TextEditor"));
}

FindDlg::~FindDlg()
{
    delete ui;
}

/*******************************
 * 查找函数，用于从头查找
 * 进入查找对话框后，不可更改原文本内容
 *
 ******************************/
bool FindDlg::find()
{
    //获取当前文本内容
    QString str = nowText;
    //获取当前需要查找的字符串
    QString toBeFound = ui->findEdit->text();
    int index =  str.indexOf(toBeFound);
    if (index == -1)
    {
        ui->resultEdit->setText("没有找到"+toBeFound);
        return false;
    }
    else
    {
        ui->resultEdit->setText(QString::number(index));
        //保存上一次查找结果
        lastIndex = index;
        stk.push(index);
        return true;
    }
}

/*******************************
 * 查找函数，用于查找下一个
 * 进入查找对话框后，不可更改原文本内容
 *
 ******************************/
bool FindDlg::findNext()
{
    //获取当前文本内容
    QString str = nowText;
    //获取当前需要查找的字符串
    QString toBeFound = ui->findEdit->text();
    //循环从上一次搜索到的地方开始
    int i = lastIndex;
    //上一次搜到的结果
    for (; i<=str.length(); i++)
    {
       if(lastIndex != str.indexOf(toBeFound, i))
       {
           break;
       }
    }
    int index = str.indexOf(toBeFound, i);
    if (index == -1)
    {
        ui->resultEdit->setText("没有找到"+toBeFound);
        return false;
    }
    else
    {
        ui->resultEdit->setText(QString::number(index));
        lastIndex = index;
        stk.push(index);
        return true;
    }
}

bool FindDlg::findPrevious()
{
    if (!stk.isEmpty())
    {
        stk.pop();
    }
    if (stk.isEmpty())
    {
        ui->resultEdit->setText("已经是第一个");
        return false;
    }
    else
    {
        lastIndex = stk.top();
        ui->resultEdit->setText(QString::number(lastIndex));
        return true;
    }
}

bool FindDlg::replace()
{
    emit sendQString(ui->replaceEdit->text());//传递替换成的值
    return true;
}

/**********************
 * 查找按钮槽
 **********************/
void FindDlg::on_findButton_clicked()
{
    find();
    //emit sendQString(QString::number(lastIndex));
    emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
}
/***************************
 * 查找下一个按钮槽
 ***************************/
void FindDlg::on_nextButton_clicked()
{
    if (stk.isEmpty())
    {
        find();
        emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
    }
    else
    {
        findNext();
        emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
    }
}
/***************************
 * 查找上一个按钮槽
 ***************************/
void FindDlg::on_previousButton_clicked()
{
    findPrevious();
    emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
}

void FindDlg::on_replaceButton_clicked()
{
    replace();
}
