#include <Helper/qmlfactory.h>
#include <Settings/cwindowinfo.h>

static const char* LIBRARY_NAME="ZeitschriftLib";
static const int VERSION_MAJOR = 1;
static const int VERSION_MINOR = 0;

void QMLFactory::registerTypes()
{
	WindowInfoQML::qmlRegister(LIBRARY_NAME,VERSION_MAJOR,VERSION_MINOR);

}
