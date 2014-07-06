#ifndef DATAFILE_H
#define DATAFILE_H
#include <QString>
#include <vector>
#include <QFile>
#include <QDir>

class DataFile
{
public:
    DataFile();
    ~DataFile();
    //Read Operations
    void setUpFile(QString file_name="");
    void loadData(QString key, std::vector <std::vector <float> > &data_vector);
    void loadData(QString key, std::vector <float> &data_vector);

    //Write Operations
    void generateFileName();
    void writeData(QString key, std::vector <float> &data_vector);

    //Common Operations
    bool removeFile();
    void reloadFile();
    void setDirectoryPath(QString directory_path="./Logs");

private:
    QFile file;
    QStringList *lines;
    QString directory_path;
    QString original_path;

    void cleanMemory();
    QString getNewFileName();

};
#endif // DATAFILE_H
