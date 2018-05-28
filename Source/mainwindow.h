#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMessageBox>
#include <QMainWindow>
#include "type.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCreate_Root_triggered();

    void on_pushButtonUpdate_clicked();

    void on_actionEdit_triggered();

    void on_actionAdd_triggered();

    void on_pushButtonStore_clicked();

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_actionRemove_triggered();

    void on_actionStore_triggered();

    void on_actionRestore_triggered();

    void on_actionQuery1_triggered();

    void on_actionQuery2_triggered();

    void on_pushButtonExit_clicked();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;
    void setButtonState(bool, bool, bool);
    void showCity();
    void showEmployee(employee* pE);
    void showZhek(zhek* pZ);
    void showProfession(profession* pP);
    void showTree();
    int selectedLevel();
    int selectedIndex(int offset);
};

#endif // MAINWINDOW_H
