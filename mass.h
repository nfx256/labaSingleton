#ifndef MASS_H
#define MASS_H
#include "enterprise.h"
class Mass :public Enterprise
{
private:
    typeEnterprise type =typeEnterprise::MASS;
    float tax;

public:
    Mass()
        :Enterprise()
    {

    }
    Mass(QString companyName, double income, double square, int numberOfWorkers,QList<QString> lList)
        :Enterprise(companyName, income, square, numberOfWorkers, lList)
    {

    }

    Enterprise::typeEnterprise getType()  override
    {
        return type;
    }

    float getTax() override
    {
        tax = getIncome() * 0.4 / (getNumberOfWorkers() + getSquare());
        return tax;
    }
};
#endif // MASS_H
