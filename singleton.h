#include "enterprise.h"
#include "mass.h"
#include "single.h"
#include "serial.h"
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
        }

    }
    void deleteEnterprise(int index)//по индексу в реестре
    {
        QTextStream out(stdout);
        if(index >= 0 && index < Enterprises.size())
        {
            QString name  = Enterprises[index]->getNameCompany();
            Enterprises.removeAt(index);
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
            qDebug() << QString::fromUtf8("ERROR\n") << QString::fromUtf8("Invalid index\n");
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


