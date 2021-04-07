#include <QCoreApplication>
QList<QString> averageValues(Singleton &mySingl, Enterprise::typeEnterprise type)
{
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
        qDebug() << qPrintable(Avr[j]);
    }
    return Avr;
}

QList<QString> listEnterprisesOfOwner(Singleton &mySingl, QString nameOwner)
{
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
        qDebug() << "List of enterprises owned by " << qPrintable(nameOwner) << ":";
    for(int k = 0; k < listEnterprise.size(); k++)
        qDebug() << qPrintable(listEnterprise[k]);
    }

    return listEnterprise;
}

void infoAboutType(Singleton &mySingl, Enterprise::typeEnterprise type)
{

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
                qDebug() << "Информация по предприятиям типа: " << qPrintable(message) << ".\n";
                flag = true;
            }
           count++;
           qDebug().nospace() << count << ")" << qPrintable(mySingl.getEnterpriseAtIndex(i).getNameCompany()) << "\n"
                                    << "\t Доход: " << mySingl.getEnterpriseAtIndex(i).getIncome() << '\n'
                                    << "\t Площадь: " << mySingl.getEnterpriseAtIndex(i).getSquare() << '\n'
                                    << "\t Кол-во рабочих: " << mySingl.getEnterpriseAtIndex(i).getNumberOfWorkers() << '\n'
                                    << "\t Заплатит налог: " << mySingl.getEnterpriseAtIndex(i).getTax() << '\n'
                                    << "\t Список владельцев: ";
           for(int j = 0; j < mySingl.getEnterpriseAtIndex(i).getListOwners().size(); j++)
           {
               qDebug() << "\t\t" << qPrintable(mySingl.getEnterpriseAtIndex(i).getListOwners()[j]);
           }
        }
    }
    if (!flag)
        qDebug() << "Предприятий типа " << message  << " в реестре нет.";
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
