#include "datafile.h"
#include <QFile>
#include <QDebug>
#include <QStringList>

DataFile::DataFile()
{
    lines = NULL;
}

DataFile::~DataFile()
{
    cleanMemory();
}

void DataFile::loadData(QString key, std::vector<std::vector<float> > &data_vector)
{
    QStringListIterator values_iterator(*lines);

    while(values_iterator.hasNext())
    {
        if(!values_iterator.peekNext().contains(key))
        {
            values_iterator.next();
            continue;
        }
        QStringList points = values_iterator.next().split(" ", QString::SkipEmptyParts);
        if(!points.isEmpty())
        {
            //Removes the key
            points.removeFirst();
        }
        QStringListIterator points_iterator(points);

        std::vector <float> pts;
        while(points_iterator.hasNext())
        {
            pts.push_back(points_iterator.next().toFloat());
        }
        data_vector.push_back(pts);
    }
}

void DataFile::loadData(QString key, std::vector<float> &data_vector)
{
    QStringListIterator values_iterator(*lines);

    while(values_iterator.hasNext())
    {
        if(!values_iterator.peekNext().contains(key))
        {
            values_iterator.next();
            continue;
        }
        QStringList points = values_iterator.next().split(" ", QString::SkipEmptyParts);
        if(!points.isEmpty())
        {
            //Removes the key
            points.removeFirst();
        }
        QStringListIterator points_iterator(points);

        while(points_iterator.hasNext())
        {
            data_vector.push_back(points_iterator.next().toFloat());
        }

    }
}

void DataFile::writeData(QString key, std::vector<float> &data_vector)
{
    QString line;
    line.append(key);
    for(unsigned int i = 0; i < data_vector.size(); i++)
    {
        line.append(" ");
        line.append(QString::number(data_vector.at(i)));
    }
    line.append("\n");
    file.open(QIODevice::Append);
    file.write(line.toLatin1());
    file.close();
}

void DataFile::setFile(QString file_name)
{
    cleanMemory();

    file.setFileName(file_name);
    file.open(QIODevice::ReadOnly);
    QString data;
    data = (QString)file.readAll();
    file.close();

    lines = new QStringList(data.split("\n",QString::SkipEmptyParts));
}

void DataFile::cleanMemory()
{
    if(lines != NULL)
    {
        delete lines;
    }
}

void DataFile::reloadFile()
{
    setFile(file.fileName());
}

bool DataFile::removeFile()
{
    return file.remove();
}
