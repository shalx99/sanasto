#include "dictionary_filter.h"
#include "QDebug"

Dictionary_Filter::Dictionary_Filter()
{
}

void Dictionary_Filter::updateFilter(const QString& text)
{
    m_filter_value = text;
    invalidateFilter();
}

bool Dictionary_Filter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filter_value.size() == 0)
        return false;

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString string = sourceModel()->data(index).toString();

    if(string.startsWith(m_filter_value))
        return true;
    else
        return false;
}

void Dictionary_Filter::onDictViewClick(QModelIndex index)
{
    QString string = index.data().toString();
    emit setUserInput(string);
}
