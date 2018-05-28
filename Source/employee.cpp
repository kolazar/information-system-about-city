#include "type.h"
#include "mainwindow.h"

employee* createEmployee()
{
    employee* pE = new employee;
    return pE;
}

void updateEmployee(employee* pE, QString name, int salary)
{
    strncpy(pE->nameEmployee,qPrintable(name),NAME_SIZE - 1);
    pE->money = salary;
}

void addEmployeeSort(profession* pP, employee* pE)
{
    if(pP->childArray == NULL)
    {
        pP->childArray = reinterpret_cast<employee**>(malloc(sizeof(employee** [START_AR_SIZE])));
        pP->arLength = START_AR_SIZE;
        pP->childCount = 0;
    }
    if(pP->childCount == pP->arLength)
    {
     pP->arLength += START_AR_SIZE;
     unsigned int newSize = sizeof(pP->arLength);
     pP->childArray = reinterpret_cast<employee**>(realloc(pP->childArray,newSize));
    }
    int i = pP->childCount;
    for(;i > 0; i --)
    {
        if(strcmp(pE->nameEmployee,pP->childArray[i-1]->nameEmployee)>0)
            break;
        pP->childArray[i] = pP->childArray[i-1];
    }
    pP->childArray[i] =pE;
    pP->childCount++;
}

void removeEmployee(profession* ptrP,int idxE)
{
        employee* ptrE = ptrP->childArray[idxE];

        delete ptrE;
        ptrP->childCount--;
        for(int i = idxE;i < ptrP->childCount;i++)
            ptrP->childArray[i] = ptrP->childArray[i+1];
        ptrP->childArray[ptrP->childCount]=NULL;
}
