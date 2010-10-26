#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QMap>

class Dictionary : public QStandardItemModel
{
public:
    Dictionary();
    QString getTranslation(QString word);

private:
    bool readFile();
    void processLine(QString line);

    static const QString m_file_name;
    QMap<QString, QString> m_dict_items;
};

#endif // DICTIONARY_H
