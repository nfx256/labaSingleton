#ifndef SINGLE_H
#define SINGLE_H
#include "enterprise.h"
class Single :public Enterprise
{
private:
typeEnterprise type =typeEnterprise::SINGLE;
float tax;


public:
Single():Enterprise()
{

}
Single(QString companyName, double income, double square, int numberOfWorkers,QList<QString> lList)
    :Enterprise(companyName, income, square, numberOfWorkers,lList)
{

}
~Single(){std::cout << "~single\n";}
Enterprise::typeEnterprise getType() override //вернуть тип enum
{
    return type;
}
float getTax() override
{
    tax = getIncome() * 0.4 / getNumberOfWorkers();
    return tax;
}
};
#endif // SINGLE_H
