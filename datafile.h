#ifndef DATAFILE_H
#define DATAFILE_H
#include <QString>
#include <vector>
#include <QFile>
class DataFile
{
public:
    DataFile();
    ~DataFile();
    void loadData(QString key, std::vector <std::vector <float> > &data_vector);
    void loadData(QString key, std::vector <float> &data_vector);
    void writeData(QString key, std::vector <float> &data_vector);
    void setFile(QString file_name);
    void reloadFile();
    bool removeFile();

private:
    QFile file;
    QStringList *lines;
    void cleanMemory();
};

#endif // DATAFILE_H
