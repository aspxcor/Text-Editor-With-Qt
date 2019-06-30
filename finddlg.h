#ifndef FINDDLG_H
#define FINDDLG_H

#include <QDialog>
#include <QStack>

namespace Ui {
class FindDlg;
}

class FindDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindDlg(QWidget *parent = nullptr);
    ~FindDlg();
    bool find();
    bool findNext();
    bool findPrevious();
    bool replace();
    //当前文本框存的值
    QString nowText;
    //上次查到的值
    int lastIndex;
    //堆栈用于存储已经找到的字符的位置
    QStack<int> stk;

signals:
    void sendIndex(int, int);
    void sendQString(QString);

private slots:
    void on_findButton_clicked();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

    void on_replaceButton_clicked();

private:
    Ui::FindDlg *ui;
};

#endif // FINDDLG_H
