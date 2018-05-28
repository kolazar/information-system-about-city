#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "dialog1.h"
#include "dialog2.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonState(bool store, bool update, bool exit)
{
    ui->pushButtonStore->setVisible(store);
    ui->pushButtonUpdate->setVisible(update);
    ui->pushButtonExit->setVisible(exit);
}

void MainWindow::showCity()
{
    ui->stackedWidget->setCurrentWidget(ui->pageCity);
    city* pC = getRoot();
    if(pC!=NULL)
    {
        ui->lineEditCityName->setText(pC->nameCity);
        ui->lineEditCityBoss->setText(pC->nameBoss);
        ui->lineEditCityMoney->setText(QString::number(pC->moneyCity));
    }
    else
    {
        ui->lineEditCityName->setText("");
        ui->lineEditCityBoss->setText("");
        ui->lineEditCityMoney->setText("");
    }
}

void MainWindow::showEmployee(employee* pE)
{
    ui->stackedWidget->setCurrentWidget(ui->pageEmployee);
    ui->lineEditEmployeeName->setText(pE->nameEmployee);
    ui->lineEditEmployeeSalary->setText(QString::number(pE->money));
}

void MainWindow::showZhek(zhek* pZ)
{
    ui->stackedWidget->setCurrentWidget(ui->pageZhek);
    ui->lineEditZhekName->setText(pZ->rayon);
    ui->lineEditZhekNumber->setText(QString::number(pZ->numberZhek));
    ui->lineEditZhekMoney->setText(QString::number(pZ->moneyZhek));
}

void MainWindow::showProfession(profession* pP)
{
    ui->stackedWidget->setCurrentWidget(ui->pageProfession);
    ui->lineEditProfessionName->setText(pP->nameProfession);
    ui->lineEditProfessionVakansiy->setText(QString::number(pP->countVakansiy));
    ui->lineEditProfessionWorkPlace->setText(QString::number(pP->countWorkPlaces));
}

void MainWindow::showTree()
{
    delete ui->treeWidget->takeTopLevelItem(0);
    showCity();
    if(getRoot()==NULL)
        return;
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget);
    city* pC = (city*)getRoot();
    rootItem->setText(0,pC->nameCity);
    zhek** zhekArray = pC->childArray;
    int zhekCount = pC->childCount;
    if(zhekArray == NULL || zhekCount == 0)
        return;

    for(int iZ=0; iZ<zhekCount; iZ++)
    {
        zhek* pZ = zhekArray[iZ];

        QTreeWidgetItem *zItem = new QTreeWidgetItem(rootItem);
        zItem->setText(0,pZ->rayon);
        profession** professionArray = pZ->childArray;
        int professionCount = pZ->childCount;
        if(professionArray == NULL || professionCount == 0)
            continue;

        for(int iP=0;iP<professionCount;iP++)
        {
            profession* pP = professionArray[iP];

            QTreeWidgetItem* pItem = new QTreeWidgetItem(zItem);
            pItem->setText(0,pP->nameProfession);
            employee** employeeArray = pP->childArray;
            int employeeCount = pP->childCount;
            if(employeeArray == NULL || employeeCount == 0)
                continue;

            for(int iE=0;iE<employeeCount;iE++)
            {
                employee* pE = employeeArray[iE];

                QTreeWidgetItem* eItem = new QTreeWidgetItem(pItem);
                eItem->setText(0,pE->nameEmployee);
            }
        }
    }
    ui->treeWidget->expandAll();
}

int MainWindow::selectedLevel()
{
    QTreeWidgetItem* item = ui->treeWidget->selectedItems().at(0);
    int level = 0;
    while((item = item->parent())!=NULL)
        level++;
    return level;
}

int MainWindow::selectedIndex(int offset)
{
    QTreeWidgetItem* item = ui->treeWidget->selectedItems().at(0);
    for(int i = 0;i<offset; i++)
        item = item->parent();
    return item->parent()->indexOfChild(item);
}

void MainWindow::on_actionCreate_Root_triggered()
{
    if(getRoot()!=NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Root already exist!");
        errorMessage.exec();
        return;
    }
    city* pC = createCity();
    setRoot(pC);

    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget);

    rootItem->setSelected(true);
    ui->treeWidget->setCurrentItem(rootItem);

    ui->stackedWidget->setCurrentWidget(ui->pageCity);

    setButtonState(false,true,false);
}

void MainWindow::on_pushButtonUpdate_clicked()
{
    setButtonState(false,false,false);
    int level = selectedLevel();
    if(level==0)
        updateCity(ui->lineEditCityName->text(),
                   ui->lineEditCityBoss->text(),
                   ui->lineEditCityMoney->text().toInt());
    else if(level==1)
    {
        int idxZ = selectedIndex(0);
        zhek* pZ = getRoot()->childArray[idxZ];
        updateZhek(pZ,ui->lineEditZhekNumber->text().toInt(),
                      ui->lineEditZhekName->text(),
                      ui->lineEditZhekMoney->text().toInt());
    }
    else if(level==2)
    {
        int idxZ = selectedIndex(1);
        zhek* pZ = getRoot()->childArray[idxZ];
        int idxP = selectedIndex(0);
        profession* pP = pZ->childArray[idxP];
        updateProfession(pP,ui->lineEditProfessionWorkPlace->text().toInt(),
                         ui->lineEditProfessionName->text(),
                         ui->lineEditProfessionVakansiy->text().toInt());
    }
    else if(level==3)
    {
        int idxZ = selectedIndex(2);
        zhek* pZ = getRoot()->childArray[idxZ];
        int idxP = selectedIndex(1);
        profession* pP = pZ->childArray[idxP];
        int idxE = selectedIndex(0);
        employee* pE =pP->childArray[idxE];
        updateEmployee(pE,ui->lineEditEmployeeName->text(),
                       ui->lineEditEmployeeSalary->text().toInt());
    }
    else
    {
        setButtonState(true,true,true);
        return;
    }
    showTree();
}

void MainWindow::on_actionEdit_triggered()
{
    if(ui->treeWidget->selectedItems().count()==0)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Node was not selected");
        errorMessage.exec();
        return;
    }
    setButtonState(false,true,true);
}

void MainWindow::on_actionAdd_triggered()
{
    if(ui->treeWidget->selectedItems().count()==0)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Node was not selected");
        errorMessage.exec();
        return;
    }
    setButtonState(true,false,true);
    int level = selectedLevel();
    if(level==0)
        ui->stackedWidget->setCurrentWidget(ui->pageZhek);
    else if(level==1)
    {
        ui->stackedWidget->setCurrentWidget(ui->pageProfession);
    }
    else if(level==2)
    {
        ui->stackedWidget->setCurrentWidget(ui->pageEmployee);
    }
}

void MainWindow::on_pushButtonStore_clicked()
{
    setButtonState(false,false,false);
    int level = selectedLevel();
    if(level == 0)
    {
        zhek* pZ = createZhek();
        updateZhek(pZ,ui->lineEditZhekNumber->text().toInt(),
                      ui->lineEditZhekName->text(),
                      ui->lineEditZhekMoney->text().toInt());
        addZhekSort(getRoot(),pZ);
    }
    else if(level == 1)
    {
        int idxZ = selectedIndex(0);
        zhek* pZ = getRoot()->childArray[idxZ];

        profession* pP = createProfession();
        updateProfession(pP,ui->lineEditProfessionWorkPlace->text().toInt(),
                         ui->lineEditProfessionName->text(),
                         ui->lineEditProfessionVakansiy->text().toInt());
        addProfessionSort(pZ,pP);
    }
    else if(level == 2)
    {
        int idxZ = selectedIndex(1);
        zhek* pZ = getRoot()->childArray[idxZ];

        int idxP = selectedIndex(0);
        profession* pP =  pZ->childArray[idxP];
        employee* pE = createEmployee();
        updateEmployee(pE,ui->lineEditEmployeeName->text(),
                       ui->lineEditEmployeeSalary->text().toInt());
        addEmployeeSort(pP,pE);
    }
    else
    {
        setButtonState(true, true, true);
        return;
    }

    showTree();
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    setButtonState(false,false,false);
    int level = selectedLevel();
    if (level ==0)
        showCity();
    else if(level == 1)
    {
        int idxZ = selectedIndex(0);
        zhek* pZ = getRoot()->childArray[idxZ];
        showZhek(pZ);
    }
    else if (level == 2)
    {
        int idxZ = selectedIndex(1);
        zhek* pZ = getRoot()->childArray[idxZ];
        int idxP = selectedIndex(0);
        profession* pP = pZ->childArray[idxP];
        showProfession(pP);
    }
    else if(level == 3)
    {
        int idxZ = selectedIndex(2);
        zhek* pZ =getRoot()->childArray[idxZ];
        int idxP = selectedIndex(1);
        profession* pP = pZ->childArray[idxP];
        int idxE = selectedIndex(0);
        employee* pE = pP->childArray[idxE];
        showEmployee(pE);
    }
}

void MainWindow::on_actionRemove_triggered()
{
    int level = selectedLevel();
    if(level==0)
        removeCity();
    else if(level == 1)
    {
        int idxZ = selectedIndex(0);
        removeZhek(idxZ);
    }
    else if(level == 2)
    {
        int idxZ = selectedIndex(1);
        zhek* pZ = getRoot()->childArray[idxZ];
        int idxP = selectedIndex(0);
        removeProfession(pZ,idxP);
    }
    else if(level == 3)
    {
        int idxZ = selectedIndex(2);
        zhek* pZ = getRoot()->childArray[idxZ];
        int idxP = selectedIndex(1);
        profession* pP =pZ->childArray[idxP];
        int idxE = selectedIndex(0);
        removeEmployee(pP,idxE);
    }
    showTree();
}

void MainWindow::on_actionStore_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(NULL,
                    QString::fromUtf8("Choose fileName for tree"),
                    QDir::currentPath(),"(*.*)");
    char* fName =(char*) qPrintable(fileName);
    FILE* fp = fopen(fName,"wb");
    if(fp==NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage(fileName+"File open Error");
        errorMessage.exec();
        return;
    }
    storeToFile(getRoot(),fp);
}

void MainWindow::on_actionRestore_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(NULL,
                 QString::fromUtf8("Choose fileName for tree"),
                           QDir::currentPath(),"(*.*)");
    char* fName =(char*) qPrintable(fileName);
    FILE* fp = fopen(fName,"rb");
    if(fp==NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage(fileName+"File open Error");
        errorMessage.exec();
        return;
    }
    city* root = restoreFromFile(fp);
    setRoot(root);
    showTree();
}

void MainWindow::on_actionQuery1_triggered()
{
    if(getRoot() == NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Root does not exist!");
        errorMessage.exec();
        return;
    }
    Dialog *wnd = new Dialog(this);
    wnd->setWindowTitle("Search Employee With Highest Salary");
    wnd->show();
}

void MainWindow::on_actionQuery2_triggered()
{
    if(getRoot() == NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Root does not exist!");
        errorMessage.exec();
        return;
    }
    int count = 0;
    QString res = "";

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
        res+="Zhek"+QString::fromStdString(ptrZ->rayon)+"\n";

        for(int j = 0;j<ptrZ->childCount;j++)
        {


            profession* ptrP = ptrZ->childArray[j];


            for(int t = 0;t<ptrP->childCount;t++){

                count++;
            }
        }
        res+="\t Count of employees:"+QString::number(count)+"\n";
        count = 0;
    }
    QMessageBox::about(this,"Count of employees ",res);
}




void MainWindow::on_pushButtonExit_clicked()
{
    exit(0);
}

void MainWindow::on_actionInfo_triggered()
{
    Dialog2 *wnd = new Dialog2(this);
    wnd->setWindowTitle("About");
    wnd->show();
}
