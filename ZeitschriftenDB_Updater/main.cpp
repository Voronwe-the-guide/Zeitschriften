#include <QCoreApplication>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>
#include <DatenbankListen/czeitschriftdisplaylist.h>
#include <sqlite/sqlite3.h>
#include <QDebug>
#include <QFileInfo>


int makeSQLiteSearch(const QString& request,sqlite3 *db, sqlite3_stmt **stmt,QString callingFunction)
{
    if (db == nullptr)
    {
        qDebug()<<"No open DB!";
        return -1;
    }
    QTime startTime = QTime::currentTime();
    int rc = sqlite3_prepare_v2(db,request.toStdString().c_str() , -1, stmt, nullptr);
    QTime endTime = QTime::currentTime();
    int doneIn = startTime.msecsTo(endTime);
    if (rc !=0 )
    {
        QString error = QString("sqlite3_prepare_v2 request from ")+callingFunction+QString(" returned %1 (%2) for %3").arg(sqlite3_errstr(rc)).arg(rc).arg(request);
        qDebug()<< error; //"SqLite request from "<<callingFunction"<< returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
    }

    qDebug()<<"Finished in "<<doneIn;
    return rc;
}

int addEmptyRowToTable(sqlite3 *db,const QString& Table )
{
    if (db == nullptr)
    {
        qDebug()<<"No open DB!";
        return -1;
    }
//    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("INSERT INTO %1 DEFAULT VALUES").arg(Table);
    int rc = sqlite3_exec(db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
    if (rc !=0 )
    {
        qDebug()<<"addNewEmptyRowToAusgabenTable: SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
        return -1;
    }

    int index = static_cast<int>(sqlite3_last_insert_rowid(db));

    return index;
}

void updateElementInTable(sqlite3 *db,QString& request)
{
    char *zErrMsg;
    int rc = sqlite3_exec (db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
    //    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);
    if (rc !=0 )
    {
        qDebug()<<"SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
    }

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CArtikelDisplayList artikelListeAlt;
    CArtikelDisplayList artikelListeNeu;
    CAusgabeDisplayList ausgabenListeAlt;
    CAusgabeDisplayList ausgabenListeNeu;
    CZeitschriftDisplayList zeitschriftenListeAlt;
    CZeitschriftDisplayList zeitschriftenListeNeu;

    QString DBinput;
    QString DBoutput;


    sqlite3 *db_in;
    sqlite3 *db_out;

    for (int i=0; i<argc; i++)
    {
        QString arg(argv[i]);
        if (arg.startsWith("-in="))
        {
            DBinput = arg.section('=',1);
        }
        if (arg.startsWith("-out="))
        {
            DBoutput = arg.section('=',1);
        }
    }
    if (DBinput.isEmpty())
    {
        qDebug("[ERROR] No Input DB");
        return -1;
    }
    if (DBoutput.isEmpty())
    {
        qDebug("[ERROR] No outputDB");
        return -1;
    }

    QFileInfo inputInfo(DBinput);
    if (!inputInfo.exists())
    {
        qDebug()<<"[ERROR] Input file does not exits: "<<DBinput;
        return -1;
    }


    int  rc = sqlite3_open_v2(DBinput.toUtf8(),&db_in,(SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI),nullptr);
    if (rc != SQLITE_OK)
    {
         qDebug()<<"Could not open SQLite DB "<<DBinput;
         return -1;
    }

    for (int i=0; i<artikelListeAlt.rowCount(); i++)
    {

    }
    rc = sqlite3_open_v2(DBoutput.toUtf8(),&db_out,(SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI),nullptr);
    if (rc != SQLITE_OK)
    {
         qDebug()<<"Could not open SQLite DB "<<DBoutput;
         return -1;
    }


  qDebug()<<"Get ZeitschriftenListe";
    sqlite3_stmt *stmt;
    QString request = QString("SELECT * FROM ")+ZEITSCHRIFT_TABELLE +" ORDER BY "+ZEITSCHRIFT_ZEITSCHRIFT+" ASC";
     rc = makeSQLiteSearch(request.toStdString().c_str(),db_in,&stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int number = sqlite3_column_count(stmt);
            CZeitschrift zeitschrift;
            for (int i=0; i<number; ++i)
            {

                QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
                QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
                zeitschrift.setDBElement(columnName,columnText);

            }
            int index = -1;
            bool isNew = zeitschriftenListeAlt.AddElement(zeitschrift,index);
            if (isNew)
            {
                int index = addEmptyRowToTable(db_out,ZEITSCHRIFT_TABELLE);
                zeitschrift.setUniqueIndex(index);
                QString sqlElements = zeitschrift.getAsSQLString(true);
                QString request = QString("UPDATE ")+ZEITSCHRIFT_TABELLE+" "+sqlElements;
                updateElementInTable(db_out,request);

            }

        }
    }


    qDebug()<<"Get AusgabenListe";
     request = QString("SELECT * FROM ")+AUSGABE_TABELLE +" ORDER BY "+AUSGABE_ZEITSCHRIFT+" ASC, "+AUSGABE_JAHR+" ASC, "+AUSGABE_AUSGABE+" ASC";
     rc = makeSQLiteSearch(request.toStdString().c_str(),db_in,&stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            qDebug() << "." << 1;
            int number = sqlite3_column_count(stmt);
            CAusgabe ausgabe;
            CZeitschrift zeitschrift;
            for (int i=0; i<number; ++i)
            {

                QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
                QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
                ausgabe.setDBElement(columnName,columnText);
                zeitschrift.setDBElement(columnName, columnText);

            }
            int index = -1;
            bool isNewAusgabe = ausgabenListeAlt.AddElement(ausgabe,index);
            if (isNewAusgabe)
            {
                int index = addEmptyRowToTable(db_out,AUSGABE_TABELLE);
                ausgabe.setUniqueIndex(index);
                QString sqlElements = ausgabe.getAsSQLString(true);
                QString request = QString("UPDATE ")+AUSGABE_TABELLE+" "+sqlElements;
                updateElementInTable(db_out,request);
            }
            index = -1;
            bool isNewZeitschrift = zeitschriftenListeAlt.AddElement(zeitschrift,index);
            if (isNewZeitschrift)
            {
                qDebug()<<"\n Neue Zeitschrift "<<zeitschrift.getZeitschrift();
                int index = addEmptyRowToTable(db_out,ZEITSCHRIFT_TABELLE);
                zeitschrift.setUniqueIndex(index);
                QString sqlElements = ausgabe.getAsSQLString(true);
                QString request = QString("UPDATE ")+ZEITSCHRIFT_TABELLE+" "+sqlElements;
                updateElementInTable(db_out,request);
            }

        }
    }

    qDebug()<<"Get ArtikelListe";
     request = QString("SELECT * FROM ")+ARTIKEL_TABELLE +" ORDER BY "+ARTIKEL_ZEITSCHRIFT+" ASC, "+ARTIKEL_JAHR+" ASC, "+ARTIKEL_AUSGABE+" ASC, "+ARTIKEL_SEITE+" ASC";
     rc = makeSQLiteSearch(request.toStdString().c_str(),db_in,&stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            qDebug() << "." << 1;
            int number = sqlite3_column_count(stmt);
            CArtikel artikel;
            CAusgabe ausgabe;
            CZeitschrift zeitschrift;


            for (int i=0; i<number; ++i)
            {

                QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
                QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
                artikel.setDBElement(columnName,columnText);
                ausgabe.setDBElement(columnName,columnText);
                zeitschrift.setDBElement(columnName,columnText);

            }

            artikelListeAlt.AddElement(artikel);
            int index = addEmptyRowToTable(db_out,ARTIKEL_TABELLE);
            artikel.setUniqueIndex(index);
            QString sqlElements = artikel.getAsSQLString(true);
            QString request = QString("UPDATE ")+ARTIKEL_TABELLE+" "+sqlElements;
            updateElementInTable(db_out,request);

            index = -1;
            bool isNewZeitschrift = zeitschriftenListeAlt.AddElement(zeitschrift,index);
            if (isNewZeitschrift)
            {
                qDebug()<<"\n Neue Zeitschrift "<<zeitschrift.getZeitschrift();
                int index = addEmptyRowToTable(db_out,ZEITSCHRIFT_TABELLE);
                zeitschrift.setUniqueIndex(index);
                QString sqlElements = ausgabe.getAsSQLString(true);
                QString request = QString("UPDATE ")+ZEITSCHRIFT_TABELLE+" "+sqlElements;
                updateElementInTable(db_out,request);
            }

            index = -1;
            bool isNewAusgabe = ausgabenListeAlt.AddElement(ausgabe,index);
            if (isNewAusgabe)
            {
                qDebug()<<"\n Neue Zeitschrift "<<ausgabe.getZeitschrift()<<" / "<<ausgabe.getJahr()<<" / "<<ausgabe.getAusgabe();
                int index = addEmptyRowToTable(db_out,AUSGABE_TABELLE);
                ausgabe.setUniqueIndex(index);
                QString sqlElements = ausgabe.getAsSQLString(true);
                QString request = QString("UPDATE ")+AUSGABE_TABELLE+" "+sqlElements;
                updateElementInTable(db_out,request);
            }

        }
    }
    else
    {
        qDebug()<<"ERROR - No Inhalte Table found";
        return -1;
    }

   // qDebug("Suche nach neuen Ausgaben in der ArtikelListe - wenn gefunden, erweitere Ausgabenliste");


    sqlite3_finalize(stmt);
    sqlite3_close_v2(db_in);
    sqlite3_close_v2(db_out);



    return 0;
}
