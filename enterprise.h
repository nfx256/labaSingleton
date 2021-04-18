#ifndef ENTERPRISE_H
#define ENTERPRISE_H
#include <QList>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QTextStream>
class Enterprise {
private:

    QString companyName_;//название
    double income_;//доход
    double square_;// площадь
    int numberOfWorkers_;//кол-во сотрудников
    QList<QString> owners;

public:

    enum class typeEnterprise {
                                  SINGLE,//Единичное
                                  SERIAL,//Серийное
                                  MASS,//Массовое
                                };
    Enterprise()
    {
        companyName_ = "0";
        income_ = 0;
        numberOfWorkers_ = 0;
        square_ = 0;
    }
Enterprise(QString companyName, double income, double square, int numberOfWorkers,QList<QString> lList)	//конструктор, по умолчанию не имеет смысла(наверно)
{

    companyName_ = companyName;
    income_ = income;
    numberOfWorkers_ = numberOfWorkers;
    square_ = square;
    owners = lList;
}
virtual ~Enterprise()
{

}

int getNumberOfWorkers()
{
    return numberOfWorkers_;
}
void setNumberOfWorkers(int number)
{
    if(number >0)
        numberOfWorkers_ = number;
}
double getSquare()
{
    return square_;
}
void setSquare(double number)
{
    if(number >0)
        square_ = number;
}
double getIncome()
{
    return income_;
}
void setIncome(double number)
{
    if(number >0)
        income_ = number;
}
QString getNameCompany()
{
   return companyName_;
}
void setNameCompany(QString name)
{
    if(!name.isEmpty())
        companyName_ = name;
}
QList<QString> getListOwners()
{
    return owners;
}
void setListOwners(QList<QString> name)
{
    if(!name.isEmpty())
        owners = name;
}
virtual float getTax() = 0;//получение налога, реализация под каждый тип будет своя
virtual typeEnterprise getType()  = 0;//получение типа предприятия
};
#endif // ENTERPRISE_H
