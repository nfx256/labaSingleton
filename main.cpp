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
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
