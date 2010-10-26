#ifndef DICTIONARY_FILTER_H
#define DICTIONARY_FILTER_H

#include <QSortFilterProxyModel>

class Dictionary_Filter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    Dictionary_Filter();
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

public slots:
    void updateFilter(const QString& text);
    void onDictViewClick(QModelIndex index);


signals:
    void setUserInput(QString word);

private:
    QString m_filter_value;
};

#endif // DICTIONARY_FILTER_H
