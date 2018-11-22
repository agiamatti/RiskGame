// standard C++ header:
#include <iostream>
#include <string>

// Qt header:
#include <QApplication>

#include "RiskGUI.h"
#include "Map.h"
#include "ObserverView.h"

using namespace std;

int main(int argc, char *argv[])
{


        QApplication a(argc, argv);

        //create riskgui class on stack otherwise it will not properly close
        RiskGUI* riskgui = new RiskGUI();
        ObserverView obsView(riskgui);
        riskgui->show();

        return a.exec();

}
