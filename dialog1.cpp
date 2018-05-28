#include "dialog1.h"
#include "ui_dialog1.h"
#include "mainwindow.h"
Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_pushButton_clicked()
{

    int count = 0;

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

                    count++;


                    }
                }
            }
            ui->lineEdit_2->setText(QString::number(count));

        }
    }






void Dialog1::on_pushButton_2_clicked()
{
    close();
}
