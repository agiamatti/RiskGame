#include "RiskGUI.h"
#include "ui_riskgui.h"
#include "Player.h"

RiskGUI::RiskGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RiskGUI)
{
    ui->setupUi(this);
    setWindowIcon(QIcon());
    playerAtCurrentTurn = NULL;
    gameBegun = false;

    ui->startButton->hide();
    settings = new SettingsDialog();
    settings->setModal(true);
    settings->setWindowTitle("Welcome to RISK");
    settings->exec();
    obtainParameters(); //obtains the chosen parameters from the initial settings menu
    consoleOut("Welcome to RISK!");
    printParameters();
    consoleOut("You may change settings in the menu before loading the game.");
}

RiskGUI::~RiskGUI()
{
    for (unsigned int i = 0; i < p.size(); i++) {
        delete p.at(i); //deleting players
    }

    delete settings;
    delete ui;
}

//obtains parameters from the settings menu
void RiskGUI::obtainParameters(){

    MAP_PATH = settings->MAP_PATH;
    NUM_OF_PLAYERS = settings->NUM_OF_PLAYERS;
    ARMY_DISTRIBUTION_MODE = settings->ARMY_DISTRIBUTION_MODE;
    END_GAME_TURN = settings->END_GAME_TURN;
    DICE_MODE = settings->DICE_MODE;
    playersSetup = settings->players;
}

//prints parameters from the settings menu
void RiskGUI::printParameters(){
    consoleOut("Map Chosen Path: " + MAP_PATH + " Number of Players: " + to_string(NUM_OF_PLAYERS) + ", Army Distrubution Mode: " + to_string(ARMY_DISTRIBUTION_MODE) + " , Dice Mode: " + to_string(DICE_MODE));
}


//returns dice mode; used in player
int RiskGUI::getDiceMode(){
    return DICE_MODE;
}

//prints to the game console; note that since the console uses html formatting, you can add colors and other formatting in that way
void RiskGUI::consoleOut(std::string output){
    QApplication::processEvents(); //processes UI
    Notify(); //update the view
    ui->consoleOutput->append(QString::fromStdString(output));
}

//the enter button next to the line input can be used to send the input
void RiskGUI::on_enterButton_clicked(){
    QString pureinput;

    if(!ui->lineInput->text().isEmpty()){
        pureinput = ui->lineInput->text();
        output = pureinput.toStdString();
        QString input = "<font color=\"green\">You have entered: \"" + pureinput + "\"</font>";
        ui->consoleOutput->append(input);
        ui->lineInput->clear();
    }

}

//return (or enter) can be pressed to have the same effect as the 'enter' button
void RiskGUI::on_lineInput_returnPressed(){
    on_enterButton_clicked();
}

void RiskGUI::on_actionAbout_triggered(){
    QMessageBox msgBox;
    msgBox.setText("COMP345 Team 8 Presents: Risk 2018\nGUI: Alan Giamatti. 2018© All rights reserved.");
    msgBox.exec();

}

//launches setting menu; can only change the menu before 'load game' is pressed
void RiskGUI::on_actionSettings_triggered(){
   if(!gameBegun){
       settings->setModal(true);
       settings->setWindowTitle("Settings");
       settings->exec();
       consoleOut("New Settings: ");
       obtainParameters();
       printParameters();
    }

   else{
       QMessageBox msgBox;
       msgBox.setText("You may not change the settings as the game has already begun.");
       msgBox.exec();

   }

}

//closes the game when x is pressed
void RiskGUI::closeEvent(QCloseEvent *event){
        delete this;
        exit(0);
}


Player* RiskGUI::getPlayerAtCurrentTurn(){
    return playerAtCurrentTurn;
}

//used to obtain strings from UI
string RiskGUI::getResponse(){


    inputCorrect = false;
    string response;

    while(!inputCorrect){
        QApplication::processEvents(); // to keep application UI running

        if (output.length()>0){
            response = output;
            inputCorrect = true;
        }
    }

    output= ""; //clear; so the string doesn't persist

    //Notify(); //update the view
    return response;
}

//used to obtain indices from GUI
int RiskGUI::getIndex(int start, int end, string item) {

    int index = -1;
    string input;
    inputCorrect = false;

    consoleOut("<font color=\"blue\">Please enter a value between " + to_string(start) + " and " + to_string(end) + ".</font>");

        while (!inputCorrect) {

            QApplication::processEvents(); // to keep application UI running
            input = output; //output is the string last input in the UI

            input = input.substr(0, input.find(" "));

            if(input.length()>0){
                try {
                    index = stoi(input);
                }
                catch (invalid_argument& e) {
                    index = -100;
                }
                catch (out_of_range& e) {
                    index = -100;
                }
                catch (exception e) {
                    index = -100;
                }


                if (index >= start && index <= end) {
                    inputCorrect = true;
                }

                else{
                    consoleOut("<font color=\"red\">Invalid " + item + ". Please try again.</font>");
                    consoleOut("<font color=\"blue\">Please enter a value between " + to_string(start) + " and " + to_string(end) + ".</font>");
                }

                 QApplication::processEvents(); // to keep application running


                 output= ""; //clear; so the string doesn't persist

            }

        }

        //Notify(); //update the view
        return index;
}

//paintEvent paints the world map with countries; using a particular color for each player
void RiskGUI::paintEvent(QPaintEvent *event){
    // unuse
    Q_UNUSED(event);

    // pass "this" pointer to painter
    QPainter painter(this);
    //QBrush brush (const QColor (white), Qt::BrushStyle solid = Qt::SolidPattern);

    //Draw Window parameters
    int drawWindowX = 1450;
    int drawWindowY = 630;
    int windowBorderX = 20;
    int windowBorderY = 50;

    painter.fillRect(20,30,drawWindowX,drawWindowY, QColor (Qt::white)); //white box where the world map resides

    //color array for players
    vector <QColor> colorArray;
    colorArray.push_back(QColor (30,144,255)); //blue
    colorArray.push_back(QColor (Qt::red));
    colorArray.push_back(QColor (0, 180, 0)); //green
    colorArray.push_back(QColor (Qt::yellow));
    colorArray.push_back(QColor (255, 165, 0)); //orange
    colorArray.push_back(QColor (Qt::cyan));
    colorArray.push_back(QColor (Qt::gray)); //extra, never chosen
    QBrush brush;

    //draw countries
    unsigned int size = countries.size();

    //calculates how much to multiply country indices; so they take the full screen and no more
    double multiplierGUIx = 1;
    double multiplierGUIy = 1;
    int minXOffset = 0;
    int minYOffset = 0;

    int maxX = 400;
    int maxY = 400;
    int minX = 400;
    int minY = 400;

    for(unsigned int i = 0; i <size; i++){
        if(maxX < countries.at(i).getGUIx()){
            maxX = countries.at(i).getGUIx();
        }
        if(maxY < countries.at(i).getGUIy()){
            maxY = countries.at(i).getGUIy();
        }

        if(minX > countries.at(i).getGUIx()){
            minX = countries.at(i).getGUIx();
        }

        if(minY > countries.at(i).getGUIy()){
            minY = countries.at(i).getGUIy();
        }

    }

    //adjusting values if some coordinates are too small
    if(minX<windowBorderX){
        minXOffset = windowBorderX - minX;
    }

    if(minY<windowBorderY){
        minYOffset = windowBorderY - minY;
    }

    if(minX>windowBorderX){
        minXOffset = windowBorderX - minX;
    }

    if(minY>windowBorderY){
        minYOffset = windowBorderY - minY;
    }

    //Country display settings
    //country rectangle size in pixels
    int countryRectx = 60;
    int countryRecty = 36;

    multiplierGUIx = (drawWindowX-windowBorderX-60)/(double)(maxX+minXOffset); //-70 because of box length
    multiplierGUIy = (drawWindowY-windowBorderY)/(double)(maxY+minYOffset);

    //cout << "GUI Mult X: " << multiplierGUIx << ", GUI Mult Y: " << multiplierGUIy << "; X offset: " << minXOffset << ", Y offset: " << minYOffset << "; maxX: " << maxX <<", maxY: " << maxY << "; minX: " << minX <<", minY: " << minY << endl;


    // loop to draw connection lines
    for (unsigned int i = 0; i < size; i++){
        int x = ((countries.at(i).getGUIx())+minXOffset)*multiplierGUIx; //GUI cordinates are multiplied so country distances are larger
        int y = ((countries.at(i).getGUIy())+minYOffset)*multiplierGUIy;

        vector <Country*> adjCountries = countries.at(i).getAdjCountries();

        for(unsigned int j = 0; j< adjCountries.size() ; j++ ){
            int x2 = ((adjCountries.at(j)->getGUIx())+minXOffset)*multiplierGUIx;
            int y2 = ((adjCountries.at(j)->getGUIy())+minYOffset)*multiplierGUIy;
            QLineF line (x+countryRectx/2,y+countryRecty/2,x2+countryRectx/2, y2+countryRecty/2);
            if (line.length()>drawWindowX/2 || line.length()>drawWindowY){} //prevent drawing huge lines across map
            else{painter.drawLine(line);}

        }
    }


    //loop to draw countries and their name+army values
    for (unsigned int i = 0; i < size; i++){
        int x = ((countries.at(i).getGUIx())+minXOffset)*multiplierGUIx; //GUI cordinates are multiplied so country distances are larger
        int y = ((countries.at(i).getGUIy())+minYOffset)*multiplierGUIy;

        // loop to find to which player does the country belong to, and gives the index j of the player
        unsigned int j=0;
        for(j=0; j<p.size();j++){
            if(countries.at(i).getPlayer() == p.at(j)){
                break;
            }
        }
             painter.fillRect(x,y,countryRectx,countryRecty, colorArray.at(j)); //draws the country!

             string countryName = countries.at(i).getCountryName();
             // spliting the name in two if it has more than 1 part
             if(countryName.find(" ")>0 && countryName.find(" ") < countryName.length()){
                painter.fillRect(x,y-30,60,28,QColor(Qt::white)); //white box behind name
                painter.drawText(x,y-18,QString::fromStdString((countryName.substr(0,countryName.find(" ")))));
                painter.drawText(x,y-5,QString::fromStdString((countryName.substr(countryName.find(" ")+1))));
             }
             else{
                painter.fillRect(x,y-16,countryName.length()*8,14,QColor(Qt::white)); //white box behind name
                painter.drawText(x,y-5,QString::fromStdString((countryName)));
             }



       painter.drawText(x+2,y+20,QString::fromStdString("A.V.: "+ to_string(countries.at(i).getArmyValue())));

    }

   int xbox = 780;
   int ybox = 684;

    painter.fillRect(xbox,ybox,690,238, QColor (Qt::white)); //white box where the stats window resides
    int totalArmyCountOnMap = 0;
    vector <int> soldierArr;
    vector <int> countryArr;
    int maxSoldierCount =0;
    int maxCountryCount =0;

    //calculating soldier count in total and per player
    for(unsigned int i = 0; i<p.size(); i++){
        soldierArr.push_back(0);

        for(unsigned int j = 0; j<p.at(i)->getCountriesOwned().size(); j++){

            totalArmyCountOnMap = totalArmyCountOnMap + p.at(i)->getCountriesOwned().at(j)->getArmyValue(); //total Army Count
            soldierArr.at(i) = soldierArr.at(i) + p.at(i)->getCountriesOwned().at(j)->getArmyValue();   //Army Count per player
        }
    }

    for(unsigned int i = 0; i<soldierArr.size(); i++){
        if(soldierArr.at(i)>maxSoldierCount){
            maxSoldierCount = soldierArr.at(i);
        }
    }

    //calculating country count in total and per player
    for(unsigned int i = 0; i<p.size(); i++){
        int numAtP = p.at(i)->getNumberOfCountriesOwned();
        countryArr.push_back(numAtP);
        if (numAtP>maxCountryCount){
            maxCountryCount = numAtP;
        }
    }



    int legendOffset = (6-p.size())*20;
    //draw player legend at the left side of the graph
   for(unsigned int i = 0; i<p.size(); i++){
        painter.fillRect(xbox+15,ybox+legendOffset+15+40*i,20,10,colorArray.at(i));
        painter.drawText(xbox+45,ybox+legendOffset+24+40*i,QString::fromStdString(p.at(i)->getPlayerName().substr(0,13)));
    }


  int columnDist = 33;
  int columnWidth= 25;
  int rowDist = 40;
  int barOffset = (columnDist-rowDist)/2;
  int GraphOffset = (6-p.size())*30; //offset is to center the graph for lower player counts
  int xgraph = 950+GraphOffset;
  int ygraph = 700;


   //for army graph
   int maxGraph = 0;

   if(maxSoldierCount/(double)totalArmyCountOnMap > 0.5 || maxCountryCount/(double)mp.getTotalNumberOfCountries()>0.5 ){
        maxGraph = 100;
   }
   else{
        maxGraph = 50;
   }

    //drawing graph scale and data bars
   if(p.size()>0){
       for(unsigned int i=0; i<6; i++){
           painter.drawText(xgraph-36,ygraph+6+rowDist*i,QString::fromStdString(to_string(maxGraph-maxGraph*i/5)+"%"));
           painter.drawLine(xgraph,ygraph+rowDist*i,xgraph+columnDist*2*p.size()+70,ygraph+rowDist*i);

       }

       int armyLegend = 0;
       int countryLegend = 0;
       //draw data colums
       for(unsigned int i=0; i<p.size(); i++){
           //draw soldier stats
            double armyHeight = ((soldierArr.at(i)/(double)totalArmyCountOnMap) *(100/maxGraph)*5*rowDist);
            //cout << "total: "<< totalArmyCountOnMap << " , s: " <<soldierArr.at(i) << " , h:" << armyHeight << endl;
            painter.fillRect(xgraph+barOffset+columnDist*i+10,(ygraph+rowDist*5)-armyHeight,columnWidth,armyHeight+1,colorArray.at(i)); // the graph column of player count
            armyLegend = armyLegend + (xgraph+barOffset+columnDist*i+10);

            painter.fillRect(xgraph+barOffset+columnDist*i+6,(ygraph+rowDist*5)-armyHeight-14,34,12, QColor (Qt::white)); //white box behind value on top of bar
            painter.drawText(xgraph+barOffset+columnDist*i+10,(ygraph+rowDist*5)-armyHeight-4, QString::fromStdString(to_string((soldierArr.at(i)*100/totalArmyCountOnMap)) + "%")); //value on top of bar

            //draw country stats
            double countryHeight = ((countryArr.at(i)/(double)mp.getTotalNumberOfCountries()) *(100/maxGraph)*5*rowDist);
            //cout << "total: "<< mp.getTotalNumberOfCountries() << " , s: " <<countryArr.at(i) << " , h:" << countryHeight << endl;
            painter.fillRect(xgraph+barOffset+columnDist*i+70+(columnDist*p.size()),(ygraph+rowDist*5)-countryHeight,columnWidth,countryHeight+1,colorArray.at(i)); // the graph column of country count
            countryLegend = countryLegend + (xgraph+barOffset+columnDist*i+70+(columnDist*p.size()));

            painter.fillRect(xgraph+barOffset+columnDist*i+66+(columnDist*p.size()),(ygraph+rowDist*5)-countryHeight-14,34,12, QColor (Qt::white)); //white box behind value on top of bar
            painter.drawText(xgraph+barOffset+columnDist*i+70+(columnDist*p.size()),(ygraph+rowDist*5)-countryHeight-4, QString::fromStdString(to_string((countryArr.at(i)*100/mp.getTotalNumberOfCountries())) + "%")); //value on top of bar

       }
       painter.drawText((armyLegend/p.size())-32,ygraph+5*rowDist+15, "Armies Owned"); //graph legend for Army
       painter.drawText((countryLegend/p.size())-38,ygraph+5*rowDist+15, "Countries Owned"); //graph legend for Country
   }



}


//Loads the game but does not start it
void RiskGUI::on_loadButton_clicked(){
    gameBegun = true;
    obtainParameters();
    cout << MAP_PATH << endl;
    ui->loadButton->hide();
     consoleOut("Loading Game!");

     // =================================== Part 1 =================================== //

     map = MapLoader(MAP_PATH, continents);

     // =================================== Part 2 =================================== //


     // Step 1: Creating Country Objects
     for (unsigned int i = 0; i < (int)map.size(); i++) {
         countries.push_back(Country(map[i].getCountry(), 0, 0, map[i].getContinent(), map[i].getGUIx(),map[i].getGUIy()));
     }

     // Step 2: Adding countries to the map ie creating a graph
     for (unsigned int i = 0; i < (int)map.size(); i++) {
         mp.addCountry(&countries[i]);
     }

     // Step 3: Connecting the adj countries.
     for (unsigned int i = 0; i < (int)map.size(); i++) {
         for (int k = 0; k < map[i].SizeOfListOfCountries(); k++) {
             for (unsigned int j = 0; j < (int)map.size(); j++) {
                 if (map[i].getCountriesFromList(k) == countries[j].getCountryName()) {
                     mp.addAdjacentCountry(&countries[i], &countries[j]);
                 }
             }
         }
     }


     // Check if map is vaild
     if (!mp.isValid()) {
         cout << "GoodBye" << endl;
         return;
     }
     else {
         cout << "Map is Created" << endl;
     }

     // =================================== Part 3 =================================== //

      int theAmountOfPlayers = NUM_OF_PLAYERS;

     // =================================== Part 4 =================================== //

     cout << "\nCreating Deck" << endl;
     Deck deck(map);

     // Code to demonstrate that deck works properly

     cout << "The number of cards in the deck: " << deck.size() << endl;
     cout << "The number of countries: " << map.size() << endl;


     // =================================== Part 5 =================================== //

     cout << "\nCreating the players" << endl;

     for (int i = 0; i < theAmountOfPlayers; i++) {
         string playerName = playersSetup.at(i);
         p.push_back(new Player(this, deck, playerName));

         if (playerName.find("Aggressive AI")!=string::npos){
             p.at(i)->setStrategy(new StrategyAggressive(p.at(i)));
         }
         else if (playerName.find("Benevolent AI")!=string::npos){
             p.at(i)->setStrategy(new StrategyBenevolent(p.at(i)));
         }
     }

     // =================================== Part 6 =================================== //

     cout << "\nRandomly chosing the turns of players" << endl;

     int temporary;
     bool dupCheck = false;

     while(orderOfTurns.size()<theAmountOfPlayers) {
         temporary = rand() % theAmountOfPlayers;
         for(int j = 0; j<orderOfTurns.size();j++){
             if (temporary == orderOfTurns.at(j)){
                 dupCheck = true;
             }
         }
         if(!dupCheck){
             orderOfTurns.push_back(temporary);
         }
         dupCheck = false;
     }

     // =================================== Part 7 =================================== //

     int j = 0;
     for (unsigned int i = 0; i < (int)map.size(); i++) {
         int random = rand() % (int)map.size();
         if (countries.at(random).getFlag() == 0) {
             p.at(orderOfTurns.at(j))->addCountriesOwned(&countries.at(random));
             //countries.at(random).setPlayer(p.at(orderOfTurns.at(j)));
             countries.at(random).setArmyValue(1);
             countries.at(random).setFlag(1);
             if (j < theAmountOfPlayers - 1)
                 j++;
             else
                 j = 0;
         }
         else
             i--;
     }

     // =================================== Part 8 =================================== //

     int A = 0;
     switch (theAmountOfPlayers) {
     case 2:
         A = 40;
         break;
     case 3:
         A = 35;
         break;
     case 4:
         A = 30;
         break;
     case 5:
         A = 25;
         break;
     case 6:
         A = 20;
         break;
     }

     int search;
     int turn = 0;

     //Desired Manual Army Distribution; must account for non-human strategies
     while (A > 0 && ARMY_DISTRIBUTION_MODE == 1) {
         while (turn != theAmountOfPlayers) {
             if(p.at(orderOfTurns.at(turn))->hasHumanStrategy()){
                 p.at(orderOfTurns.at(turn))->printCountriesOwned();
                 cout << "\nPlayer: " << p.at(orderOfTurns.at(turn))->getPlayerName();
                 cout << " Please pick a country to reinforce" << endl;
                 search = getIndex(1, p.at(orderOfTurns.at(turn))->getNumberOfCountriesOwned(), "selection");
                 p.at(orderOfTurns.at(turn))->reinforce((p.at(orderOfTurns.at(turn))->getCountriesOwned().at(search - 1)), 1);
             }
             else{
                 p.at(orderOfTurns.at(turn))->reinforce(p.at(orderOfTurns.at(turn))->getCountriesOwned().at(rand() % p.at(orderOfTurns.at(turn))->getNumberOfCountriesOwned()), 1);
             }
             turn++;
         }
         turn = 0;
         A--;
     }


     //Automatic Army Distribution; randomly distributes armies for the players at the start
     while (A > 0 && ARMY_DISTRIBUTION_MODE == 0) {
         while (turn != theAmountOfPlayers) {
             p.at(orderOfTurns.at(turn))->reinforce(p.at(orderOfTurns.at(turn))->getCountriesOwned().at(rand() % p.at(orderOfTurns.at(turn))->getNumberOfCountriesOwned()), 1);
             turn++;
         }

         turn = 0;
         A--;
     }

//     for (Country *c : mp.getCountriesMap()) {
//         c->printCountryDetails();
//         cout << endl;
//     }

     ui->startButton->show();
     consoleOut("Game is loaded. Ready to Start.");
     Notify(); //update the view
}


//starts the game and the main game loop
void RiskGUI::on_startButton_clicked(){

         // MAIN GAME LOOP//
         ui->startButton->hide();
         bool gameOver = false;
         int roundCounter = 0;
         consoleOut("The game has begun!");

         while (!gameOver) {
             consoleOut("Round " + to_string(++roundCounter));
             // for each player
             for (unsigned int i = 0; i < p.size(); i++) {
                 playerAtCurrentTurn = p.at(orderOfTurns.at(i));
                 if(playerAtCurrentTurn->getNumberOfCountriesOwned()!=0){
                 playerAtCurrentTurn->calculateReinforcementsPerTurn(continents); // must call this method at the beginning of every turn to account for changes in reinforcements

                 // Reinforcement phase

                 consoleOut(playerAtCurrentTurn->getPlayerName() + "'s reinforcement phase");
                 playerAtCurrentTurn->reinforce();

                 // Attack Phase - Here is where gameOver can change value
                 consoleOut(playerAtCurrentTurn->getPlayerName() + "'s attack phase");
                 playerAtCurrentTurn->attack();

                 //Here is a method for finishing the game early to show the win condition
                 if (roundCounter == END_GAME_TURN) {
                     consoleOut("Ending game");
                     for (unsigned int j = i + 1; j < p.size(); j++) {
                         vector <Country*> countries =  playerAtCurrentTurn->getCountriesOwned();
                         for (unsigned int k = 0; k < countries.size(); k++) {
                             playerAtCurrentTurn->addCountriesOwned(countries.at(k));
                             playerAtCurrentTurn->removeCountriesOwned(countries.at(k));
                         }

                         playerAtCurrentTurn->printCountriesOwned();
                         playerAtCurrentTurn->printCountriesOwned();
                     }

                 }

                 // Indicate game over and leave main loop
                 if (p.at(orderOfTurns.at(i))->getNumberOfCountriesOwned() >= map.size()) {
                     consoleOut("Game Over. " + playerAtCurrentTurn->getPlayerName() + " Wins!" );
                     gameOver = true;
                     QMessageBox msgBox;
                     msgBox.setText(QString::fromStdString(playerAtCurrentTurn->getPlayerName() + " Wins!"));
                     msgBox.exec();
                     break;
                 }


                 // Fortification Phase
                 consoleOut(playerAtCurrentTurn->getPlayerName() + "'s fortification phase");
                 playerAtCurrentTurn->fortify();
                }

             }

         }
 }
