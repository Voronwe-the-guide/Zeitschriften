#ifndef CSQLITEDBLOADER_H
#define CSQLITEDBLOADER_H

#include <QObject>
#include <sqlite/sqlite3.h>

class CSQLiteDBLoader : public QObject
{
    Q_OBJECT
public:
    explicit CSQLiteDBLoader(QObject *parent = nullptr);

signals:

public slots:

private:
    sqlite3 *m_db;
};

#endif // CSQLITEDBLOADER_H
