#define NAME_SIZE 20
#define START_AR_SIZE 4
#include <iostream>
#include <string>
#include <QtGui>
#include <QErrorMessage>
#include <QFileDialog>
#include <QDir>
#pragma once



struct employee
{
    char nameEmployee[NAME_SIZE];
    int money;
};

struct profession
{
    char nameProfession[NAME_SIZE];
    int countWorkPlaces;
    int countVakansiy;
    int arLength;
    int childCount;
    employee** childArray;
};

struct zhek
{
    int numberZhek;
    char rayon[NAME_SIZE];
    int moneyZhek;
    int arLength;
    int childCount;
    profession** childArray;
};

struct city
{
    char nameCity[NAME_SIZE];
    char nameBoss[NAME_SIZE];
    int moneyCity;
    int arLength;
    int childCount;
    zhek** childArray;
};

city* getRoot();
void setRoot(city* r);
city* createCity();
void updateCity(QString nameCity,QString nameBoss,int moneyCity);
employee* createEmployee();
void updateEmployee(employee* pE, QString name, int salary);
void addEmployeeSort(profession* pP, employee* pE);
zhek* createZhek();
void updateZhek(zhek* pZ,int number, QString rayon, int money);
void addZhekSort(city* pC, zhek* pZ);
profession* createProfession();
void updateProfession(profession* pP,int workPlace, QString name, int vakansiy);
void addProfessionSort(zhek* pZ, profession* pP);
void removeCity();
void removeZhek(int idxZ);
void removeProfession(zhek* ptrZ,int idxP);
void removeEmployee(profession* ptrP,int idxE);
void storeToFile(city* pC, FILE* fp);
city* restoreFromFile(FILE* fp);
