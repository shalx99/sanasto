#include "dictionary.h"
#include "mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QStringList>


const QString Dictionary::m_file_name("fin_ru.txt");

Dictionary::Dictionary()
{
    readFile();

    int num = 0;
    QStringList word_list = m_dict_items.uniqueKeys();
    foreach(QString word, word_list)
    {
        QStandardItem *item = new QStandardItem(word);
        setItem(num++, item);
    }
}

bool Dictionary::readFile()
{
    QFile file(m_file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "readFile() failed to open " << m_file_name << " file";
        return false;
    }

    QTextStream in(&file);
    QString line;

    while (!(line = in.readLine()).isNull())
    {
        processLine(line);
    }

    file.close();

    QString status("dictionary contains ");
    status.append(QString::number(m_dict_items.size())).append(" words");
    MainWindow::getInstance()->updateStatusBar(status);

    return true;
}

void Dictionary::processLine(QString line)
{
    QString separator("  ");

    int pos = line.indexOf(separator);

    if (pos < 0)
        return;

    QString word = line.left(pos);
    QString meaning = line.right(line.size() - pos - 1);

    m_dict_items.insertMulti(word, meaning);
}

QString Dictionary::getTranslation(QString word)
{
    QStringList all_translations = m_dict_items.values(word);
    QString res;
    foreach(QString translation, all_translations)
    {
        res.append(translation);
    }
    return res;
}
