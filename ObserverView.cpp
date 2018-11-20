#include "ObserverView.h"

ObserverView::ObserverView(){
}

ObserverView::ObserverView(RiskGUI* x)
{
    _subject = x;
    _subject->Attach(this);

}

void ObserverView::Update() {
    //Called by Notify() when state of Subject changes
    display();

};

void ObserverView::display() {
    _subject->update();
    cout << "Better Work:" << endl;
    //system("CLS");
    //system("pause");
};

ObserverView::~ObserverView(){
    _subject->Detach(this);
}
