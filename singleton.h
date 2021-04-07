#include <QList>
#include <QString>
#include <QDebug>

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
~Enterprise()
{

}

int getNumberOfWorkers()
{
    return numberOfWorkers_;
}
double getSquare()
{
    return square_;
}
double getIncome()
{
    return income_;
}
QString getNameCompany()
{
   return companyName_;
}

QList<QString> getListOwners()
{
    return owners;
}
virtual float getTax() = 0;//получение налога, реализация под каждый тип будет своя
virtual typeEnterprise getType()  = 0;//получение типа предприятия
};

#endif // SINGLETON_H
