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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
Enterprise::typeEnterprise getType() override //вернуть тип enum
{
    switch(type)
    {
        case typeEnterprise::SINGLE  : qDebug() << "Это предприятие имеет тип: SINGLE\n";  return type;  break;
        case typeEnterprise::SERIAL  : qDebug() << "Это предприятие имеет тип: SERIAL\n";  return type; break;
        case typeEnterprise::MASS: qDebug() << "Это предприятие имеет тип: MASS\n";  return type; break;
    }

}
float getTax() override
{
    tax = getIncome() * 0.4 / getNumberOfWorkers();
    return tax;
}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        switch(type)
        {
            case typeEnterprise::SINGLE  : qDebug() << "Это предприятие имеет тип: SINGLE\n";  return type;  break;
            case typeEnterprise::SERIAL  : qDebug() << "Это предприятие имеет тип: SERIAL\n";  return type; break;
            case typeEnterprise::MASS: qDebug() << "Это предприятие имеет тип: MASS\n";  return type; break;
        }
    }
    float getTax() override
    {
        tax = getIncome() * 0.1 / (getNumberOfWorkers() + getSquare());
        return tax;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        switch(type)
        {
            case typeEnterprise::SINGLE  : qDebug() << "Это предприятие имеет тип: SINGLE\n";  return type;  break;
            case typeEnterprise::SERIAL  : qDebug() << "Это предприятие имеет тип: SERIAL\n";  return type; break;
            case typeEnterprise::MASS: qDebug() << "Это предприятие имеет тип: MASS\n";  return type; break;
        }
    }

    float getTax() override
    {
        tax = getIncome() * 0.4 / (getNumberOfWorkers() + getSquare());
        return tax;
    }

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Singleton
{
protected:

    Singleton(const QString value): value_(value)
    {
    }

    static Singleton* singleton_;
    QString value_;
    QList<Enterprise*> Enterprises;


public:

    Singleton(Singleton &other) = delete;

    void operator=(const Singleton& s) = delete;

    static Singleton *GetInstance(QString& valu);

    void deleteEnterprise(QString name)//по имени компании
    {
        bool flag = false;
        int i = 0 ;
        for (; i < Enterprises.size(); i++)
        {
            if (Enterprises[i]->getNameCompany()== name)
            {
                flag = true;
                break;
            }

        }
        if(flag)
        {
            Enterprises.removeAt(i);
            qDebug() << "Из реестра была удалена компания" << qPrintable(name) ;
            qDebug() << "Размер реестра: " << Enterprises.size() << "\n";
        }

    }

    void deleteEnterprise(int index)//по индексу в реестре
    {
        if(index >= 0 && index < Enterprises.size())
        {
            QString name  = Enterprises[index]->getNameCompany();
            Enterprises.removeAt(index);
            qDebug() << "Из реестра была удалена компания" << qPrintable(name);
            qDebug() << "Размер реестра: " << Enterprises.size() << "\n";
        }

    }


    void addEnterprise(Enterprise& name)
    {
        bool flag = true;

        for (int i = 0; i < Enterprises.size(); i++)
        {
            if (Enterprises[i]->getNameCompany()== name.getNameCompany())
                flag = false;
        }
        if(flag)
        {
            Enterprises.append(&name);
            qDebug() << "В реестр была добавлена компания: " << qPrintable(name.getNameCompany());
            qDebug() << "Размер реестра: " << Enterprises.size() << "\n";
        }
    }



    Enterprise& getEnterpriseAtIndex(int index)
    {
        if(index >= 0 && index < Enterprises.size())
        {
           return *Enterprises[index];
        }
        else
        {
            qDebug() << "ERROR\n" << "Invalid index\n";
        }
    }

    int getCountEnterprise()
    {
        int i = Enterprises.size();
        return i;
    }


    QString value() const
    {
        return value_;
    }
};

Singleton* Singleton::singleton_ = nullptr;

Singleton* Singleton::GetInstance( QString& value)
{


    if(singleton_ == nullptr)
    {
        singleton_ = new Singleton(value);
    }
    return singleton_;
};


