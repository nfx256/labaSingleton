#include <QList>
#include <QString>
#include <QDebug>
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
    return type;
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
        return type;
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
        return type;
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

    Singleton(const QString value): name_(value)
    {
    }

    static Singleton* singleton_;
    QString name_;
    QList<Enterprise*> Enterprises;


public:

    Singleton(Singleton &other) = delete;

    void operator=(const Singleton& s) = delete;

    static Singleton *GetInstance(QString& valu);

    void deleteEnterprise(QString name)//по имени компании
    {
        QTextStream out(stdout);
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
            out << QString::fromUtf8("Из реестра была удалена компания ") << qPrintable(name)<<"\n";
            out << QString::fromUtf8("Размер реестра: ") << Enterprises.size() << "\n";
        }

    }
    void deleteEnterprise(int index)//по индексу в реестре
    {
        QTextStream out(stdout);
        if(index >= 0 && index < Enterprises.size())
        {
            QString name  = Enterprises[index]->getNameCompany();
            Enterprises.removeAt(index);
            out << QString::fromUtf8("Из реестра была удалена компания ") << qPrintable(name)<<"\n";
            out << QString::fromUtf8("Размер реестра: ") << Enterprises.size() << "\n";
        }

    }
    void addEnterprise(Enterprise& name)
    {
        QTextStream out(stdout);
        bool flag = true;

        for (int i = 0; i < Enterprises.size(); i++)
        {
            if (Enterprises[i]->getNameCompany()== name.getNameCompany())
                flag = false;
        }
        if(flag)
        {
            Enterprises.append(&name);
            out << QString::fromUtf8("В реестр была добавлена компания: ") << qPrintable(name.getNameCompany()) << "\n";
            out << QString::fromUtf8("Размер реестра: ") << Enterprises.size() << "\n";
        }
    }

    Enterprise& getEnterpriseAtIndex(int index)
    {
        QTextStream out(stdout);
        if(index >= 0 && index < Enterprises.size())
        {
           return *Enterprises[index];
        }
        else
        {
            out << QString::fromUtf8("ERROR\n") << QString::fromUtf8("Invalid index\n");
        }
    }
    int getCountEnterprise()
    {
        int i = Enterprises.size();
        return i;
    }
    QString value() const
    {
        return name_;
    }
};

Singleton* Singleton::singleton_ = nullptr;

Singleton* Singleton::GetInstance( QString& name)
{
    if(singleton_ == nullptr)
    {
        singleton_ = new Singleton(name);
    }
    return singleton_;
};


