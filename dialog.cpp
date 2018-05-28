#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include<QString>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    zhek *tmp = getRoot()->childArray[0];
    int max_zp = 0;
    QString stroka;
    if(getRoot()->childCount == 0)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Zhek does not exist!");
        errorMessage.exec();
        return;
    }
    for(int i = 0; i < getRoot()->childCount;i++)
    {
        zhek* ptrZ = getRoot()->childArray[i];


        for(int j = 0;j<ptrZ->childCount;j++)
        {


            profession* ptrP = ptrZ->childArray[j];
            if(ui->lineEdit->text().toInt() == ptrZ->numberZhek)
            {

                for(int t = 0;t<ptrP->childCount;t++){
                    employee* ptrE = ptrP->childArray[t];
                    if(ptrE->money>=max_zp)
                    {
                        max_zp =ptrE->money;
                        stroka = ptrE->nameEmployee;

                    }
                }
            }
            ui->lineEdit_2->setText(stroka);
            ui->lineEdit_3->setText(QString::number(max_zp));
        }
    }


}



void Dialog::on_pushButton_2_clicked()
{
      close();
}
