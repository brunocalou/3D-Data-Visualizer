#include "datafile.h"
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QDateTime>
#include <QFile>
#include <QDir>

DataFile::DataFile()
{
    lines = NULL;
    file.setFileName(getNewFileName());
    original_path = QDir::currentPath();
    setDirectoryPath();
}

DataFile::~DataFile()
{
    cleanMemory();
}

void DataFile::loadData(QString key, std::vector<std::vector<float> > &data_vector)
{
    QDir::setCurrent(directory_path);

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
    QDir::setCurrent(original_path);
}

void DataFile::loadData(QString key, std::vector<float> &data_vector)
{
    QDir::setCurrent(directory_path);

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
    QDir::setCurrent(original_path);
}

void DataFile::writeData(QString key, std::vector<float> &data_vector)
{
    QDir::setCurrent(directory_path);

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
    QDir::setCurrent(original_path);
    qDebug() << "saved";
}

void DataFile::setUpFile(QString file_name)
{
    cleanMemory();

    QDir::setCurrent(directory_path);

    if(file_name == ""){file_name = getNewFileName();}
    file.setFileName(file_name);

    if(file.exists())//Prevents the error "QIODevice::seek: Cannot call seek on a sequential device"
    {
        file.open(QIODevice::ReadOnly);
        QString data;
        data = (QString)file.readAll();
        file.close();

        lines = new QStringList(data.split("\n",QString::SkipEmptyParts));
    }
    QDir::setCurrent(original_path);
}

void DataFile::generateFileName()
{
    setUpFile(getNewFileName());
}

void DataFile::setDirectoryPath(QString directory_path)
{
    QDir::setCurrent(original_path);
    if(directory_path == "./Logs")
    {
        QDir dir;
        dir.mkdir(directory_path);
    }
    this->directory_path = directory_path;
}

QString DataFile::getNewFileName()
{
    QDateTime date = QDateTime::currentDateTime();
    return QString("Log_").append(date.toString("ddd_dd_MM_yyyy_hh:mm:ss")).append(".txt");
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
    QDir::setCurrent(directory_path);
    setUpFile(file.fileName());
    QDir::setCurrent(original_path);
}

bool DataFile::removeFile()
{
    QDir::setCurrent(directory_path);
    bool removed =  file.remove();
    QDir::setCurrent(original_path);
    return removed;
}
