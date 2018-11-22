#pragma once

#include <iostream>
#include <vector>
#include <QDialog>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>


using namespace std;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    vector <string> players;
    string MAP_PATH;
    int NUM_OF_PLAYERS;
    int ARMY_DISTRIBUTION_MODE;
    int END_GAME_TURN;
    int DICE_MODE;


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_toolButton_pressed();
    void on_SettingsDialog_rejected();

    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_2_activated(const QString &arg1);
    void on_comboBox_3_activated(const QString &arg1);
    void on_comboBox_4_activated(const QString &arg1);
    void on_comboBox_5_activated(const QString &arg1);
    void on_comboBox_6_activated(const QString &arg1);


private:
    Ui::SettingsDialog *ui;
    bool initiated;
};

