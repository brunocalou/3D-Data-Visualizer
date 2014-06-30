#include "datafile.h"
#include <QFile>
#include <QDebug>
#include <QStringList>

DataFile::DataFile()
{
}

void DataFile::loadData(QString file_name, QString key, std::vector<std::vector<float> > &data_vector)
{
    QFile file;
    file.setFileName(file_name);
    file.open(QIODevice::ReadOnly);
    QString data;
    data = (QString)file.readAll();
    file.close();

    QStringList values = data.split(key,QString::SkipEmptyParts);
    QStringListIterator values_iterator(values);

    while(values_iterator.hasNext())
    {
        QStringList points = values_iterator.next().split(" ", QString::SkipEmptyParts);
        QStringListIterator points_iterator(points);

        std::vector <float> pts;
        while(points_iterator.hasNext())
        {
            pts.push_back(points_iterator.next().toFloat());
        }
        data_vector.push_back(pts);
    }
//    for(std::vector<std::vector<float> >::iterator it = data_vector.begin(); it != data_vector.end(); it++)
//    {
//        for(std::vector<float>::iterator val = (*it).begin(); val != (*it).end(); val++)
//        {
//            qDebug() << (*val);
//        }
//    }
}

void DataFile::loadData(QString file_name, QString key, std::vector<float> &data_vector)
{
    QFile file;
    file.setFileName(file_name);
    file.open(QIODevice::ReadOnly);
    QString data;
    data = (QString)file.readAll();
    file.close();

    QStringList values = data.split(key,QString::SkipEmptyParts);
    QStringListIterator values_iterator(values);

    while(values_iterator.hasNext())
    {
        QStringList points = values_iterator.next().split(" ", QString::SkipEmptyParts);
        QStringListIterator points_iterator(points);

        while(points_iterator.hasNext())
        {
            data_vector.push_back(points_iterator.next().toFloat());
        }

    }
}
