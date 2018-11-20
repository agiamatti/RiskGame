#pragma once

#include "RiskGUI.h"
#include "Observer.h"
#include "Subject.h"
#include <QWidget>

class ObserverView : public Observer {
public:
    ObserverView();
    ObserverView(RiskGUI* x);
    void Update();
    void display();
    ~ObserverView();

private:
    RiskGUI *_subject;
};
