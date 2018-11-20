#include "SettingsDialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    initiated = false;
    NUM_OF_PLAYERS = 0;
    ui->lineEdit->setText("/Map/World.map");
    ui->lineEdit_3->setValidator(new QIntValidator(0,1));
    ui->lineEdit_3->setText("0");
    ui->lineEdit_4->setValidator(new QIntValidator(3,10000));
    ui->lineEdit_4->setText("1000");
    ui->lineEdit_5->setValidator(new QIntValidator(0,1));
    ui->lineEdit_5->setText("0");

    QStringList list=(QStringList()<<"Closed"<<"Human Player"<<"Aggressive AI"<<"Benevolent AI");
    ui->comboBox->addItems(QStringList()<<"Human Player"<<"Aggressive AI"<<"Benevolent AI");
    ui->comboBox_2->addItems(QStringList()<<"Aggressive AI"<<"Benevolent AI"<<"Human Player");
    ui->comboBox_3->addItems(QStringList()<<"Benevolent AI"<<"Aggressive AI"<<"Human Player"<<"Closed");
    ui->comboBox_4->addItems(list);
    ui->comboBox_5->addItems(list);
    ui->comboBox_6->addItems(list);

    ui->lineEdit_6->setText("Player 1");
    ui->lineEdit_7->setText("Aggressive AI 2");
    ui->lineEdit_7->setReadOnly(true);
    ui->lineEdit_8->setText("Benevolent AI 3");
    ui->lineEdit_8->setReadOnly(true);
    ui->lineEdit_9->setReadOnly(true);
    ui->lineEdit_10->setReadOnly(true);
    ui->lineEdit_11->setReadOnly(true);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    while(!players.empty()){
        players.pop_back();
    }

    if (ui->lineEdit_6->text().isEmpty())
        players.push_back("Player 1");
    else
        players.push_back(ui->lineEdit_6->text().toStdString()); //player 1

    if (ui->lineEdit_7->text().isEmpty())
        players.push_back("Aggressive AI 2");
    else
        players.push_back(ui->lineEdit_7->text().toStdString()); //player 2

    if(!ui->lineEdit_8->text().isEmpty())
         players.push_back(ui->lineEdit_8->text().toStdString()); //player 3
    if(!ui->lineEdit_9->text().isEmpty())
         players.push_back(ui->lineEdit_9->text().toStdString()); //player 4
    if(!ui->lineEdit_10->text().isEmpty())
         players.push_back(ui->lineEdit_10->text().toStdString()); //player 5
    if(!ui->lineEdit_11->text().isEmpty())
         players.push_back(ui->lineEdit_11->text().toStdString()); //player 6

    MAP_PATH = ui->lineEdit->text().toStdString();
    ARMY_DISTRIBUTION_MODE = ui->lineEdit_3->text().toInt();
    END_GAME_TURN = ui->lineEdit_4->text().toInt();
    DICE_MODE = ui->lineEdit_5->text().toInt();
    NUM_OF_PLAYERS = players.size();
    initiated = true;

}


void SettingsDialog::on_buttonBox_rejected()
{
    if(!initiated){ //if no values set
        players.push_back("Player 1");
        players.push_back("Aggressive AI 2");
        players.push_back("Benevolent AI 3");
        MAP_PATH = "/Map/World.map";
        NUM_OF_PLAYERS = players.size();
        ARMY_DISTRIBUTION_MODE = 0;
        END_GAME_TURN = 1000;
        DICE_MODE = 0;
        initiated = true;
    }
}

void SettingsDialog::on_toolButton_pressed(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a map file to open."));

    ui->lineEdit->setText(fileName);

}

void SettingsDialog::on_comboBox_activated(const QString &arg1){
    if(arg1 == "Human Player"){
        ui->lineEdit_6->setReadOnly(false);
        ui->lineEdit_6->setText("Player 1");
    }

    if(arg1 == "Aggressive AI"){
        ui->lineEdit_6->setText("Aggressive AI 1");
        ui->lineEdit_6->setReadOnly(true);
    }

    if(arg1 == "Benevolent AI"){
        ui->lineEdit_6->setText("Benevolent AI 1");
        ui->lineEdit_6->setReadOnly(true);
    }
}

void SettingsDialog::on_comboBox_2_activated(const QString &arg1){
    if(arg1 == "Human Player"){
        ui->lineEdit_7->setReadOnly(false);
        ui->lineEdit_7->setText("Player 2");
    }

    if(arg1 == "Aggressive AI"){
        ui->lineEdit_7->setText("Aggressive AI 2");
        ui->lineEdit_7->setReadOnly(true);
    }

    if(arg1 == "Benevolent AI"){
        ui->lineEdit_7->setText("Benevolent AI 2");
        ui->lineEdit_7->setReadOnly(true);
    }
}

void SettingsDialog::on_comboBox_3_activated(const QString &arg1){

    if(arg1 == "Closed"){
        ui->lineEdit_8->setText("");
        ui->lineEdit_8->setReadOnly(true);
    }

    if(arg1 == "Human Player"){
        ui->lineEdit_8->setReadOnly(false);
        ui->lineEdit_8->setText("Player 3");
    }

    if(arg1 == "Aggressive AI"){
        ui->lineEdit_8->setText("Aggressive AI 3");
        ui->lineEdit_8->setReadOnly(true);
    }

    if(arg1 == "Benevolent AI"){
        ui->lineEdit_8->setText("Benevolent AI 3");
        ui->lineEdit_8->setReadOnly(true);
    }
}

void SettingsDialog::on_comboBox_4_activated(const QString &arg1){
    if(arg1 == "Closed"){
        ui->lineEdit_9->setText("");
        ui->lineEdit_9->setReadOnly(true);
    }

    if(arg1 == "Human Player"){
        ui->lineEdit_9->setReadOnly(false);
        ui->lineEdit_9->setText("Player 4");
    }

    if(arg1 == "Aggressive AI"){
        ui->lineEdit_9->setText("Aggressive AI 4");
        ui->lineEdit_9->setReadOnly(true);
    }

    if(arg1 == "Benevolent AI"){
        ui->lineEdit_9->setText("Benevolent AI 4");
        ui->lineEdit_9->setReadOnly(true);
    }

}

void SettingsDialog::on_comboBox_5_activated(const QString &arg1){
    if(arg1 == "Closed"){
        ui->lineEdit_10->setText("");
        ui->lineEdit_10->setReadOnly(true);
    }

    if(arg1 == "Human Player"){
        ui->lineEdit_10->setReadOnly(false);
        ui->lineEdit_10->setText("Player 5");
    }

    if(arg1 == "Aggressive AI"){
        ui->lineEdit_10->setText("Aggressive AI 5");
        ui->lineEdit_10->setReadOnly(true);
    }

    if(arg1 == "Benevolent AI"){
        ui->lineEdit_10->setText("Benevolent AI 5");
        ui->lineEdit_10->setReadOnly(true);
    }

}

void SettingsDialog::on_comboBox_6_activated(const QString &arg1){
    if(arg1 == "Closed"){
        ui->lineEdit_11->setText("");
        ui->lineEdit_11->setReadOnly(true);
    }

    if(arg1 == "Human Player"){
        ui->lineEdit_11->setReadOnly(false);
        ui->lineEdit_11->setText("Player 6");
    }

    if(arg1 == "Aggressive AI"){
        ui->lineEdit_11->setText("Aggressive AI 6");
        ui->lineEdit_11->setReadOnly(true);
    }

    if(arg1 == "Benevolent AI"){
        ui->lineEdit_11->setText("Benevolent AI 6");
        ui->lineEdit_11->setReadOnly(true);
    }
}
