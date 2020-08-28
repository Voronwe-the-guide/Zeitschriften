#ifndef CZEITSCHRIFT_H
#define CZEITSCHRIFT_H

#include <QString>

class CZeitschrift
{
public:
    CZeitschrift();
    CZeitschrift (const  CZeitschrift&) = default;
    CZeitschrift& operator=(const CZeitschrift&) = default;
    CZeitschrift ( CZeitschrift&&) = default;
    CZeitschrift& operator=( CZeitschrift&&) = default;

    virtual ~CZeitschrift() = default;

    bool setDBElement(QString columnName, QString columnEntry);

    QString Zeitschrift() const;
    void setZeitschrift(QString zeitschrift);

    bool isSelected() const;
    void setIsSelected(bool isSelected);

private:
    QString m_Zeitschrift;
    bool m_isSelected;
};

#endif // CZEITSCHRIFT_H
