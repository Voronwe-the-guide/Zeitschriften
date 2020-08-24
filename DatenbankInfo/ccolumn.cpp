#include "ccolumn.h"

CColumn::CColumn():
    m_searchable(true)
{

}
CColumn::CColumn(QString &name, bool searchable):
    CColumn()
{
    setName(name);
    setSearchable(searchable);
}

QString CColumn::name() const
{
    return m_name;
}

void CColumn::setName(const QString &name)
{
    m_name = name;
}

bool CColumn::searchable() const
{
    return m_searchable;
}

void CColumn::setSearchable(bool searchable)
{
    m_searchable = searchable;
}
