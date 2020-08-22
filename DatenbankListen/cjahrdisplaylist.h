#ifndef CJAHRDISPLAYLIST_H
#define CJAHRDISPLAYLIST_H


#include <QAbstractListModel>
#include "causgabedisplaylist.h"
#include <QObject>
#include "cjahr.h"

class CJahrDisplayList  : public QAbstractListModel
{
		Q_OBJECT
public:
    CJahrDisplayList(QObject *parent = 0);

	virtual ~CJahrDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
	void listEmpty();

public slots:
	void deleteAll();
	void AddJahr(CJahr &jahr);
	void deleteAusgaben();
	void AddAusgabe(CAusgabe ausgabe);


protected:

	QHash<int, QByteArray> roleNames() const;

private:


	QList<CJahr> m_JahrList;
	//QMap<int,CAusgabeDisplayList>  m_AusgabenListe;

	static const int  Role_Jahr;
};

#endif // CJAHRDISPLAYLIST_H