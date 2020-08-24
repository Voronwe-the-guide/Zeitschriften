#ifndef CCOLUMN_H
#define CCOLUMN_H

#include <QString>

class CColumn
{
public:
    CColumn();
    CColumn(QString &name, bool searchable = true);
    CColumn (const  CColumn&) = default;
    CColumn& operator=(const CColumn&) = default;
    CColumn ( CColumn&&) = default;
    CColumn& operator=( CColumn&&) = default;

    virtual ~CColumn() = default;

    QString name() const;
    void setName(const QString &name);

    bool searchable() const;
    void setSearchable(bool searchable);

private:
    QString m_name;
    bool m_searchable;


};

#endif // CCOLUMN_H
