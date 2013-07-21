#include "mainwindow.h"
#include <QApplication>

#include "exception.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch(ErgException& e)
    {
        auto leakedmsg(new QErrorMessage);
        leakedmsg->showMessage(QString("Emergency Response Editor Exception Raised: ") + e.whatq());
    }
    catch(QException& e)
    {
        auto leakedmsg(new QErrorMessage);
        leakedmsg->showMessage(QString("Qt Exception Raised: ") + e.what());
    }
    catch(std::exception& e)
    {
        auto leakedmsg(new QErrorMessage);
        leakedmsg->showMessage(QString("std::exception Raised:") + e.what());
    }
}
