#include "type.h"
#include "mainwindow.h"

city* createCity()
{
    city * pC = new city;
    pC->childArray = NULL;
    pC->childCount = 0;
    pC->arLength = 0;
    return pC;
}

void updateCity(QString nameC,QString nameB,int money)
{
    strncpy(getRoot()->nameCity,qPrintable(nameC),NAME_SIZE-1);
    strncpy(getRoot()->nameBoss,qPrintable(nameB),NAME_SIZE-1);
    getRoot()->moneyCity = money;
}

void removeCity()
{
    for(int n = 0;n < getRoot()->childCount;n++)
    {
        zhek* ptrZ = getRoot()->childArray[n];
        for(int i = 0;i < ptrZ->childCount;i++)
        {
            profession* ptrP = ptrZ->childArray[i];

        for(int j = 0;j < ptrP->childCount;j++)
        {
            delete(ptrP->childArray[j]);
        }
        delete[](ptrP->childArray);
        delete ptrP;
    }
        ptrZ->childArray = NULL;
        delete ptrZ;
        delete[](ptrZ->childArray);
        delete ptrZ;
    }
    delete[](getRoot()->childArray);
    delete getRoot();
    setRoot(NULL);
}
