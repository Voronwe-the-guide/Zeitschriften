#include "cerrordisplay.h"

CErrorDisplay::CErrorDisplay(QObject *parent) : QObject(parent)
{

}

void CErrorDisplay::gotErrorMessage(QString sender, QString Message)
{
	QString error = QString("Error\nFrom %1:\n%2").arg(sender,Message);
	emit displayError(error);
}
