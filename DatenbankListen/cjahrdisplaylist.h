#ifndef CJAHRDISPLAYLIST_H
#define CJAHRDISPLAYLIST_H


#include <QAbstractListModel>
#include <QObject>
#include "cjahr.h"
#include <sqlite/sqlite3.h>

class CJahrDisplayList  : public QAbstractListModel
{
		Q_OBJECT
public:
	CJahrDisplayList(sqlite3 *db,QObject *parent = 0);

	virtual ~CJahrDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
	void listEmpty();

public slots:
	void GetDBRequest();
	void deleteAll();
	void AddJahr(CJahr &jahr);

protected:

	QHash<int, QByteArray> roleNames() const;

private:


	QList<CJahr> m_JahrList;
	sqlite3 *m_db;

	static const int  Role_Jahr;
};

#endif // CJAHRDISPLAYLIST_H
