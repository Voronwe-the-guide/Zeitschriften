#include "helper.h"

QString Helper::fixSpecialCharacters(QString input)
{
	input = input.replace("'","''");
	return input;
}

QString Helper::fixSpecialCharacters(int input)
{
	QString output = QString("%1").arg(input);
	return output;
}

QString Helper::fixSpecialCharacters(double input)
{
	QString output = QString("%1").arg(input);
	return output;
}

