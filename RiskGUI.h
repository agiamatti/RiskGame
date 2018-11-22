#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include <QMainWindow>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QDialog>
#include <QString>
#include <QPainter>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QButtonGroup>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QIntValidator>
#include <QEvent>
#include <QInputDialog>
#include <QDir>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QThread>
#include <QCloseEvent>
#include <QCoreApplication>

#include "Map.h"
#include "Info.h"
#include "Dice.h"
#include "Deck.h"
#include "Country.h"
#include "Continent.h"
#include "MapLoader.h"
#include "Observer.h"
#include "SettingsDialog.h"
#include "Subject.h"


using namespace std;

namespace Ui {
class RiskGUI;
}

class Player;
class RiskGUI : public QMainWindow, public Subject
{
    Q_OBJECT

public:
    explicit RiskGUI(QWidget *parent = nullptr);
    ~RiskGUI();

    //getters
    int getCurrentTurn();
    int getDiceMode();
    Player* getPlayerAtCurrentTurn();

    //other methods
    void obtainParameters();
    void printParameters();
    void consoleOut(std::string output);
    int getIndex(int start, int end, string item);
    string getResponse();

protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_enterButton_clicked();
    void on_lineInput_returnPressed();
    void on_startButton_clicked();
    void on_loadButton_clicked();
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();

private:
    Ui::RiskGUI* ui;
    //main Parameters
     string MAP_PATH;
     int NUM_OF_PLAYERS;
     int ARMY_DISTRIBUTION_MODE;
     int END_GAME_TURN;
     int DICE_MODE;

    //main attributes
    Map mp;
    Deck* deck;
    vector <Country> countries;
    vector <Continent> continents;
    vector <Info> map;
    vector <Player*> p;
    vector <int> orderOfTurns;

    int currentTurn;
    Player* playerAtCurrentTurn;
    SettingsDialog* settings;
    vector <string> playersSetup;
    bool gameBegun;
    string output;
    bool inputCorrect;
};
