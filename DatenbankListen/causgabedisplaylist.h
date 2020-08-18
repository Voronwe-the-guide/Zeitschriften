#ifndef CAUSGABEDISPLAYLIST_H
#define CAUSGABEDISPLAYLIST_H

#include <QAbstractListModel>
#include <QObject>
#include "causgabe.h"
#include <sqlite/sqlite3.h>

class CAusgabeDisplayList  : public QAbstractListModel
{
	Q_OBJECT
public:
	CAusgabeDisplayList(sqlite3 *db,QObject *parent = 0);

	virtual ~CAusgabeDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
	void listEmpty();

public slots:
	void getAusgabenForJahr(int jahr);
	void deleteAll();
	void AddAusgabe (CAusgabe &ausgabe);

protected:

	QHash<int, QByteArray> roleNames() const;

private:


	QList<CAusgabe> m_AusgabenList;
	sqlite3 *m_db;

	static const int Role_Jahr;
	static const int Role_Ausgabe;
	static const int Role_Zeitschrift;
};

#endif // CAUSGABEDISPLAYLIST_H
