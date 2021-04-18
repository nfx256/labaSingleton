#include <QCoreApplication>
#include "singleton.h"


QList<QString> averageValues(Singleton &mySingl, Enterprise::typeEnterprise type)
{
    QTextStream out(stdout);
    double avrIncome = 0;
    double avrNumberOfWorkers = 0;
    double avrSquare= 0;
    bool flag = false;
    int count = 0;
    for(int i = 0; i < mySingl.getCountEnterprise(); i++)
    {
        if(mySingl.getEnterpriseAtIndex(i).getType() == type)
        {
            avrSquare+=mySingl.getEnterpriseAtIndex(i).getSquare();
            avrIncome+=mySingl.getEnterpriseAtIndex(i).getIncome();
            avrNumberOfWorkers+=mySingl.getEnterpriseAtIndex(i).getNumberOfWorkers();
            flag = true;
            count++;
        }
    }
    if(flag)
    {
        avrSquare/=count;
        avrIncome/=count;
        avrNumberOfWorkers/=count;
    }
    QList<QString> Avr;
    Avr.append("Average square: " + QString::number(avrSquare,'f',3));
    Avr.append("Average income: " + QString::number(avrIncome,'f',3));
    Avr.append("Average number of workers: " + QString::number(avrNumberOfWorkers,'f',3));
    for(int j = 0; j < Avr.size(); j++){
        out << qPrintable(Avr[j]) << "\n";
    }
    return Avr;
}

QList<QString> listEnterprisesOfOwner(Singleton &mySingl, QString nameOwner)
{
    QTextStream out(stdout);
    QList<QString> listEnterprise;
    bool flag;
    for(int i = 0; i < mySingl.getCountEnterprise(); i++)
    {
        flag = false;
        QList<QString>listOwners = mySingl.getEnterpriseAtIndex(i).getListOwners();
        for(int j = 0; j < listOwners.size(); j++)
        {
            if(listOwners[j] == nameOwner)
            {
                flag = true;
                break;
            }
        }
        if(flag)
            listEnterprise.append(mySingl.getEnterpriseAtIndex(i).getNameCompany());
    }
    if(!listEnterprise.empty())
    {
        out << "List of enterprises owned by " << qPrintable(nameOwner) << ":" << "\n";
    for(int k = 0; k < listEnterprise.size(); k++)
        out << qPrintable(listEnterprise[k]) << "\n";
    }

    return listEnterprise;
}

void infoAboutType(Singleton &mySingl, Enterprise::typeEnterprise type)
{
    QTextStream out(stdout);
    QString message ;
    switch(type)
    {
        case Enterprise::typeEnterprise::SINGLE  : message  = "Single" ;break;
        case Enterprise::typeEnterprise::SERIAL  :  message  = "Serial" ;break;
        case Enterprise::typeEnterprise::MASS:  message  = "Mass" ;break;
    }
    int count = 0;
    //bool key1 = true;
    bool flag = false;
    for(int i = 0; i < mySingl.getCountEnterprise(); i++)
    {
        if(mySingl.getEnterpriseAtIndex(i).getType() == type)
        {
            if(!flag)
            {
                out << QString::fromUtf8("Информация по предприятиям типа: ") << qPrintable(message) << ".\n";
                flag = true;
            }
           count++;
           out << count << ")" << qPrintable(mySingl.getEnterpriseAtIndex(i).getNameCompany()) << "\n"
                                    << QString::fromUtf8("\t Доход: ") << mySingl.getEnterpriseAtIndex(i).getIncome() << '\n'
                                    << QString::fromUtf8("\t Площадь: ") << mySingl.getEnterpriseAtIndex(i).getSquare() << '\n'
                                    << QString::fromUtf8("\t Кол-во рабочих: ") << mySingl.getEnterpriseAtIndex(i).getNumberOfWorkers() << '\n'
                                    << QString::fromUtf8("\t Заплатит налог: ") << mySingl.getEnterpriseAtIndex(i).getTax() << '\n'
                                    << QString::fromUtf8("\t Список владельцев: ") << "\n";
           for(int j = 0; j < mySingl.getEnterpriseAtIndex(i).getListOwners().size(); j++)
           {
               out << "\t\t" << qPrintable(mySingl.getEnterpriseAtIndex(i).getListOwners()[j]) << "\n";
           }
        }
    }
    if (!flag)
        out << QString::fromUtf8("Предприятий типа ") << message  << QString::fromUtf8(" в реестре нет.");
}

int main(int argc, char *argv[])
{
    QTextStream out(stdout);
    QCoreApplication a(argc, argv);
    QList<QString> owners;
    QList<QString> owners1;




    owners << "Mikhail" << "Egor" << "Dima";
    owners1 << "Mikhail" << "Dima";

    Single company1("OOO.Home", 200, 10, 3,owners);
    auto tax1 = company1.getTax();
    Enterprise::typeEnterprise tip1 = company1.getType();

    Serial company2("OOO.Car", 200, 10, 3,owners1);
    auto tax2 = company2.getTax();
    Enterprise::typeEnterprise tip2 = company2.getType();

    Mass company3("OOO.Check", 200, 10, 3,owners);
    auto tax3 = company3.getTax();
    Enterprise::typeEnterprise tip3 = company3.getType();

    QString name = "Reestr";
    Singleton *mySingl = Singleton::GetInstance(name);
    mySingl->addEnterprise(company1);
    mySingl->addEnterprise(company2);
    mySingl->addEnterprise(company3);

    int count = mySingl->getCountEnterprise();
    out << QString::fromUtf8("Кол-во предприятий в регистре1: ") << count <<"\n";

    mySingl->deleteEnterprise(company1.getNameCompany());
    mySingl->addEnterprise(company1);
    out << "/////////////////////////////////////////\n";
    //mySingl->deleteEnterprise(0);
    count = mySingl->getCountEnterprise();
    out << QString::fromUtf8("Кол-во предприятий в регистре: ") << count <<"\n";
    Enterprise::typeEnterprise kindOf;
    kindOf = mySingl->getEnterpriseAtIndex(0).getType();//в консоль выводит сообщение
    out << "kindOf :" << static_cast<int>(kindOf);
    QList<QString> listEnterpriseOfEgor= listEnterprisesOfOwner(*mySingl,"Egor");
    QList<QString> listEnterpriseTypeOfSingle = averageValues(*mySingl, tip2);
    infoAboutType(*mySingl, tip1);

//    Mass company3("OOO.Close", 200, 10, 3,4);
//    auto tax3 = company3.getTax();
//    Enterprise::typeEnterprise tip3 = company3.getType();
    Enterprise* comp = new Single("OOO.Car", 200, 10, 3,owners1);
    delete comp;
    return 0;

}
