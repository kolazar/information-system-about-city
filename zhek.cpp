#include "type.h"
#include "mainwindow.h"

zhek* createZhek()
{
    zhek* pZ = new zhek;
    pZ->childArray = NULL;
    pZ->childCount = 0;
    pZ->arLength = 0;
    return pZ;
}

void updateZhek(zhek* pZ,int number, QString rayon, int money)
{
    strncpy(pZ->rayon,qPrintable(rayon),NAME_SIZE - 1);
    pZ->moneyZhek = money;
    pZ->numberZhek = number;
}

void addZhekSort(city* pC, zhek* pZ)
{
    if(pC->childArray == NULL)
    {
        pC->childArray = new zhek * [START_AR_SIZE];
        pC->arLength = START_AR_SIZE;
        pC->childCount = 0;
    }
    if(pC->childCount == pC->arLength)
    {
     pC->arLength += START_AR_SIZE;
     int newSize = sizeof(zhek**)*pC->arLength;
     pC->childArray = reinterpret_cast<zhek**>(realloc(pC->childArray,newSize));
    }
    int i = pC->childCount;
    for(;i > 0; i --)
    {
        if(strcmp(pZ->rayon,pC->childArray[i-1]->rayon)>0)
            break;
        pC->childArray[i] = pC->childArray[i-1];
    }
    pC->childArray[i] =pZ;
    pC->childCount++;
}

void removeZhek(int idxZ)
{
    city * ptrC = getRoot();
    zhek *ptrZ = ptrC->childArray[idxZ];
    for(int i = 0; i < ptrZ->childCount; i++)
    {
        profession *ptrP = ptrZ->childArray[i];
        for(int j = 0; j < ptrP->childCount; j++)
            delete ptrP->childArray[j];
        delete[] (ptrP->childArray);
        delete ptrP;
    }
    ptrZ->childArray = NULL;
    delete ptrZ;
    delete[] (ptrZ->childArray);
    delete ptrZ;
    ptrC->childCount--;
    for(int i = idxZ; i < ptrC->childCount; i++)
    {
        ptrC->childArray[i] = ptrC->childArray[i+1];
    }
}

