#include "type.h"
#include "mainwindow.h"

profession* createProfession()
{
    profession* pP = new profession;
    pP->childArray = NULL;
    pP->childCount = 0;
    pP->arLength = 0;
    return pP;
}

void updateProfession(profession* pP,int workPlace, QString name, int vakansiy)
{
    strncpy(pP->nameProfession,qPrintable(name),NAME_SIZE - 1);
    pP->countWorkPlaces = workPlace;
    pP->countVakansiy = vakansiy;
}

void addProfessionSort(zhek* pZ, profession* pP)
{
    if(pZ->childArray == NULL)
    {
        pZ->childArray = new profession* [START_AR_SIZE];
        pZ->arLength = START_AR_SIZE;
        pZ->childCount = 0;
    }
    if(pZ->childCount == pZ->arLength)
    {
     pZ->arLength += START_AR_SIZE;
      int newSize = sizeof(profession**)*pZ->arLength;
     pZ->childArray = reinterpret_cast<profession**>(realloc(pZ->childArray,newSize));
    }
    int i = pZ->childCount;
    for(;i > 0; i --)
    {
        if(strcmp(pP->nameProfession,pZ->childArray[i-1]->nameProfession)>0)
            break;
        pZ->childArray[i] = pZ->childArray[i-1];
    }
    pZ->childArray[i] = pP;
    pZ->childCount++;
}

void removeProfession(zhek *ptrZ, int idxP)
{
    profession *ptrP = ptrZ->childArray[idxP];
    for(int j = 0; j < ptrP->childCount; j++)
        delete ptrP->childArray[j];
    delete[] (ptrP->childArray);
    delete ptrP;
    for(int i = idxP; i < ptrZ->childCount; i++)
        ptrZ->childArray[i] = ptrZ->childArray[i+1];
    ptrZ->childArray[ptrZ->childCount] = NULL;
    ptrZ->childCount--;
}
