#ifndef DATAFILE_H
#define DATAFILE_H
#include <QString>
#include <QVector3D>
#include <vector>

class DataFile
{
public:
    DataFile();
    void loadData(QString file_name, QString key, std::vector <std::vector <float> > &data_vector);
    void loadData(QString file_name, QString key, std::vector <float> &data_vector);


private:
};

#endif // DATAFILE_H
