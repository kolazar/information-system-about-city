#include "type.h"

void storeToFile(city* pC, FILE* fp)
{
    if(pC == NULL)
        return;
    fwrite(pC,sizeof(city),1,fp);
    zhek** zhekArray = pC->childArray;
    int zhekCount = pC->childCount;
    if(zhekArray == NULL || zhekCount == 0)
        goto closeFile;

    for(int iZ = 0; iZ < zhekCount; iZ ++)
    {
        zhek* pZ = zhekArray[iZ];
        fwrite(pZ,sizeof(zhek),1,fp);
        profession** professionArray = pZ->childArray;
        int professionCount = pZ->childCount;
        if(professionArray == NULL || professionCount ==0)
            continue;
        for(int iP = 0; iP < professionCount; iP++)
        {
            profession* pP = professionArray[iP];
            fwrite(pP,sizeof(profession),1,fp);
            employee** employeeArray = pP->childArray;
            int employeeCount = pP->childCount;
            if(employeeArray == NULL || employeeCount == 0)
                continue;
            for(int iE = 0; iE < employeeCount;iE ++)
            {
                employee* pE = employeeArray[iE];
                fwrite(pE,sizeof(employee),1,fp);
            }
        }
    }
    closeFile:
    fclose(fp);
}

city* restoreFromFile(FILE* fp)
{
    city* root = new city;
    fread(root,sizeof(city),1,fp);
    root->childArray=NULL;
    int zhekCount = root->childCount;
    for(int iZ = 0;iZ < zhekCount; iZ++)
    {
        zhek* pZ = new zhek;
        fread(pZ,sizeof(zhek),1,fp);
        pZ->childArray = NULL;
        addZhekSort(root,pZ);
        int professionCount = pZ->childCount;
        if(professionCount == 0)
            continue;
        for(int iP = 0;iP<professionCount; iP++)
        {
            profession* pP = new profession;
            fread(pP,sizeof(profession),1,fp);
            pP->childArray=NULL;
            addProfessionSort(pZ,pP);
            int employeeCount = pP->childCount;
            if(employeeCount ==0)
                continue;
            for(int iE=0; iE<employeeCount;iE++)
            {
                employee* pE = new employee;
                fread(pE,sizeof(employee),1,fp);
                addEmployeeSort(pP,pE);
            }
        }
    }
    fclose(fp);
    return root;
}
