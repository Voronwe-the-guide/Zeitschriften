#ifndef CARTIKELDISPLAYLIST_H
#define CARTIKELDISPLAYLIST_H

#include <QAbstractListModel>
#include <QObject>
#include "cartikel.h"


class CArtikelDisplayList : public QAbstractListModel
{
	Q_OBJECT
public:
    CArtikelDisplayList(QObject *parent = 0);

	virtual ~CArtikelDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

    QString searchElement() const;
    void setSearchElement(const QString &searchElement);

signals:
	void listEmpty();

public slots:
	void deleteAll();
	void AddElement(CArtikel &artikel);


protected:

	QHash<int, QByteArray> roleNames() const;

private:

    QString HighlightSearchElement(QString parsedString) const;
	QList<CArtikel> m_ArtikelList;
    QString m_searchElement;

    QString m_fontColor_normal;
    QString m_fontColor_highlight;

	static const int  Role_Zeitschrift;
	static const int  Role_Jahr;					//!< Jahrgang der Zeitschrift
	static const int  Role_Ausgabe;				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
	static const int  Role_Seite;				//!< Seitennummer
	static const int  Role_Rubrik;
	static const int  Role_Ueberschrift;
	static const int  Role_Zusammenfassung;
	static const int  Role_Kurztext;
	static const int  Role_Autor;
	static const int  Role_Fotos;
	static const int  Role_Schlagworte;
	static const int  Role_Land;
	static const int  Role_Koordinate;
};




#endif // CARTIKELDISPLAYLIST_H
