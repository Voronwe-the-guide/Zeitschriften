#ifndef CZEITSCHRIFT_H
#define CZEITSCHRIFT_H

#include <QString>
#include <QMap>

#define ZEITSCHRIFT_TABELLE         "Zeitschriften"
#define ZEITSCHRIFT_ZEITSCHRIFT     "Zeitschrift"	//!< TEXT
#define ZEITSCHRIFT_INDEX           "UniqueIndex"	//!< INTEGER
#define ZEITSCHRIFT_LOGO            "Logo"			//!< BLOB
#define ZEITSCHRIFT_BESCHREIBUNG    "Beschreibung"  //!< TEXT
#define ZEITSCHRIFT_NOTIZEN         "Notizen"       //!< TEXT
#define ZEITSCHRIFT_SPRACHE         "Sprache"       //!< TEXT

class CZeitschrift
{
public:
    CZeitschrift();
    CZeitschrift (const  CZeitschrift&) = default;
    CZeitschrift& operator=(const CZeitschrift&) = default;
    CZeitschrift ( CZeitschrift&&) = default;
    CZeitschrift& operator=( CZeitschrift&&) = default;

	virtual ~CZeitschrift();

	bool setDBElement(const QString& columnName, const QByteArray& columnEntry);

	QString getZeitschrift() const;
	void setZeitschrift(const QString& zeitschrift);

    bool isSelected() const;
    void setIsSelected(bool isSelected);

	QString getLogo() const;
    QString getPureLogo() const;
	void setLogo(const QString &logo);

    QString getBeschreibung() const;
    void setBeschreibung(const QString &beschreibung);

    QString getNotizen() const;
    void setNotizen(const QString &notizen);

    QString getSprache() const;
    void setSprache(const QString &sprache);

	int getUniqueIndex() const;
	void setUniqueIndex(int uniqueIndex);

	void AddElementToRubrikList(QString rubrik);
	QList <QString> getRubrikList();

	void AddElementToSloganList(QString element);
	QList <QString> getSloganList();

	void AddElementToRedaktionList(QString element);
	QList <QString> getRedaktionList();

    QString getAsSQLString(bool include_whereID) const;

private:
	void setText(QString key, QString text);
	bool m_isSelected;

	 QMap<QString,QByteArray> m_ZeitschriftMap;
	 QList <QString> m_rubrikList;
	 QList <QString> m_sloganList;
	 QList <QString> m_redaktionList;
};

#endif // CZEITSCHRIFT_H
