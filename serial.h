#ifndef SERIAL_H
#define SERIAL_H
#include "enterprise.h"
class Serial :public Enterprise
{
private:
    typeEnterprise type =typeEnterprise::SERIAL;
    float tax;

public:
    Serial()
        :Enterprise()
    {

    }
    Serial(QString companyName, double income, double square, int numberOfWorkers,QList<QString> lList)
        :Enterprise(companyName, income, square, numberOfWorkers, lList)
    {

    }
    Enterprise::typeEnterprise getType()  override
    {
        return type;
    }
    float getTax() override
    {
        tax = getIncome() * 0.1 / (getNumberOfWorkers() + getSquare());
        return tax;
    }
};

#endif // SERIAL_H
