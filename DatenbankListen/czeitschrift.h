#ifndef CZEITSCHRIFT_H
#define CZEITSCHRIFT_H

#include <QString>
#include <QMap>

#define ZEITSCHRIFT_TABELLE		"Zeitschrift"
#define ZEITSCHRIFT_ZEITSCHRIFT "Zeitschrift"	//!< TEXT
#define ZEITSCHRIFT_INDEX		"UniqueIndex"	//!< INTEGER
#define ZEITSCHRIFT_LOGO		"Logo"			//!< BLOB

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
	void setLogo(const QString &logo);

	int getUniqueIndex() const;
	void setUniqueIndex(int uniqueIndex);

	void AddElementToRubrikList(QString rubrik);
	QList <QString> getRubrikList();

private:
	void setText(QString key, QString text);
	bool m_isSelected;

	 QMap<QString,QByteArray> m_ZeitschriftMap;
	 QList <QString> m_rubrikList;
};

#endif // CZEITSCHRIFT_H
