#include "StudentWorld.h"
#include <string>


#include "Actor.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "Compiler.h"
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


void StudentWorld::updateAmountOfAntsInThisColony(int colonyNumber, int delta, int tickMark){
    
    
    if(colonyNumber == 0){
        m_antsPlayer0.m_nAnts += delta;
        m_antsPlayer0.m_currentTick = tickMark;
        cerr<<"Player 0 now has "<<m_antsPlayer0.m_nAnts<<endl;
        cerr<<"Player 0 got this many ants at "<<m_antsPlayer0.m_currentTick<<endl;
    }
    
    else if(colonyNumber == 1){
        m_antsPlayer1.m_nAnts += delta;
        m_antsPlayer1.m_currentTick = tickMark;
    }
    
    else if(colonyNumber == 2){
        m_antsPlayer2.m_nAnts += delta;
        m_antsPlayer2.m_currentTick = tickMark;
    }
    
    else if(colonyNumber == 3){
        m_antsPlayer3.m_nAnts += delta;
        m_antsPlayer3.m_currentTick = tickMark;
    }
    
}

int StudentWorld::getAntCountForThisAntColony(int colonyNumber) const{
    
    if(colonyNumber == 0)
        return m_antsPlayer0.m_nAnts;
    
    else if(colonyNumber == 1)
        return m_antsPlayer1.m_nAnts;
    
    else if(colonyNumber == 2)
        return m_antsPlayer2.m_nAnts;
    
    else if(colonyNumber == 3)
        return m_antsPlayer3.m_nAnts;
    
    return -1; //ill make sure this never happens though
}


int StudentWorld::checkWinnerForFourPlayers(){
    //beginning conditions
    if(m_antsPlayer0.m_nAnts == m_antsPlayer1.m_nAnts && m_antsPlayer1.m_nAnts == m_antsPlayer2.m_nAnts && m_antsPlayer2.m_nAnts == m_antsPlayer3.m_nAnts && m_antsPlayer3.m_nAnts == 5){
        return GWSTATUS_NO_WINNER;
    }
    
    AntsTick arrOfScores []= {m_antsPlayer0,m_antsPlayer1,m_antsPlayer2,m_antsPlayer3};
    
    
    AntsTick winningAntNumber = arrOfScores[0];
    int winningColony = 0;
    
    //this gets the highest ant
    for (int i = 1; i < m_numberOfPlayers; i++){
        if (arrOfScores[i] > winningAntNumber){
            winningColony = i;
            winningAntNumber = arrOfScores[i];
        }
    }
    
    if(winningColony ==0)
        setWinner(m_cPlayer0->getColonyName());
    else if(winningColony == 1)
        setWinner(m_cPlayer1->getColonyName());
    else if (winningColony == 2)
        setWinner(m_cPlayer2->getColonyName());
    else if (winningColony == 3)
        setWinner(m_cPlayer3->getColonyName());
    return GWSTATUS_PLAYER_WON;
    
    
    
}


int StudentWorld::checkWinnerForThreePlayers(){
    //beginning conditions
    if(m_antsPlayer0.m_nAnts == m_antsPlayer1.m_nAnts && m_antsPlayer1.m_nAnts == m_antsPlayer2.m_nAnts && m_antsPlayer2.m_nAnts ==  5){
        return GWSTATUS_NO_WINNER;
    }
    
    AntsTick arrOfScores []= {m_antsPlayer0,m_antsPlayer1,m_antsPlayer2};
    
    
    AntsTick winningAntNumber = arrOfScores[0];
    int winningColony = 0;
    
    //this gets the highest ant
    for (int i = 1; i < m_numberOfPlayers; i++){
        if (arrOfScores[i] > winningAntNumber){
            winningColony = i;
            winningAntNumber = arrOfScores[i];
        }
    }
    
    if(winningColony ==0)
        setWinner(m_cPlayer0->getColonyName());
    else if(winningColony == 1)
        setWinner(m_cPlayer1->getColonyName());
    else if (winningColony == 2)
        setWinner(m_cPlayer2->getColonyName());
    
    return GWSTATUS_PLAYER_WON;
    
}

int StudentWorld::checkWinnerForTwoPlayers(){
    //beginning conditions
    if(m_antsPlayer0.m_nAnts == m_antsPlayer1.m_nAnts && m_antsPlayer1.m_nAnts == 5){
        return GWSTATUS_NO_WINNER;
    }
    
    AntsTick arrOfScores []= {m_antsPlayer0,m_antsPlayer1};
    
    
    AntsTick winningAntNumber = arrOfScores[0];
    int winningColony = 0;
    
    //this gets the highest ant
    for (int i = 1; i < m_numberOfPlayers; i++){
        if (arrOfScores[i] > winningAntNumber){
            winningColony = i;
            winningAntNumber = arrOfScores[i];
        }
    }
    
    if(winningColony ==0)
        setWinner(m_cPlayer0->getColonyName());
    else if(winningColony == 1)
        setWinner(m_cPlayer1->getColonyName());
    
    
    return GWSTATUS_PLAYER_WON;
    
}

void StudentWorld::setDisplayForFourPlayers(Compiler *c0, Compiler *c1, Compiler *c2, Compiler *c3){
    
    AntsTick arrOfScores []= {m_antsPlayer0,m_antsPlayer1,m_antsPlayer2,m_antsPlayer3};
    
    
    AntsTick winningAntNumber = arrOfScores[0];
    int winningColony = 0;
    
    //this gets the highest ant
    for (int i = 1; i < 4; i++){
        if (arrOfScores[i] > winningAntNumber){
            winningColony = i;
            winningAntNumber = arrOfScores[i];
        }
    }
    
    
    
    //s
    ostringstream statusOfGame;
    
    
    
    int player0Ants = m_antsPlayer0.m_nAnts;
    int player1Ants = m_antsPlayer1.m_nAnts;
    int player2Ants = m_antsPlayer2.m_nAnts;
    int player3Ants = m_antsPlayer3.m_nAnts;
    
    //consider the very beginning
    if(player0Ants == player1Ants && player1Ants == player2Ants && player2Ants == player3Ants && player3Ants == 5){
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<<setw(2)<<setfill('0')<< player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " <<c3->getColonyName()<<": "<<setw(2)<<setfill('0')<<player3Ants<< " ants  "<< endl;
        string s = statusOfGame.str();
        
        setGameStatText(s);
        
    }
    
    else if(winningColony == 0){
        
        statusOfGame<< "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<"*: "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " <<c3->getColonyName()<<": "<<setw(2)<<setfill('0')<<player3Ants<< " ants  "<< endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    
    else if (winningColony == 1){
        
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants << " ants  "<<c1->getColonyName()<<"*: "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " <<c3->getColonyName()<<": "<<setw(2)<<setfill('0')<<player3Ants<< " ants  "<< endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    else if (winningColony == 2){
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants << " ants  "<<c1->getColonyName()<<": "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<"*: "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " <<c3->getColonyName()<<": "<<setw(2)<<setfill('0')<<player3Ants<< " ants  "<< endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    else if (winningColony == 3){
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants << " ants  "<<c1->getColonyName()<<": "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " <<c3->getColonyName()<<"*: "<<setw(2)<<setfill('0')<<player3Ants<< " ants  "<< endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    else{
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<<setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " <<c3->getColonyName()<<": "<<setw(2)<<setfill('0')<<player3Ants<< " ants  "<< endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
}

void StudentWorld::setDisplayForThreePlayers(Compiler *c0, Compiler *c1, Compiler *c2){
    AntsTick arrOfScores []= {m_antsPlayer0,m_antsPlayer1,m_antsPlayer2};
    
    
    AntsTick winningAntNumber = arrOfScores[0];
    int winningColony = 0;
    
    //this gets the highest ant
    for (int i = 1; i < 3; i++){
        if (arrOfScores[i] > winningAntNumber){
            winningColony = i;
            winningAntNumber = arrOfScores[i];
        }
    }
    
    
    
    //s
    ostringstream statusOfGame;
    
    
    
    int player0Ants = m_antsPlayer0.m_nAnts;
    int player1Ants = m_antsPlayer1.m_nAnts;
    int player2Ants = m_antsPlayer2.m_nAnts;
    
    //consider the very beginning
    if(player0Ants == player1Ants && player1Ants == player2Ants && player2Ants == 5){
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<<setw(2)<<setfill('0')<< player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " << endl;
        string s = statusOfGame.str();
        
        setGameStatText(s);
        
    }
    
    else if(winningColony == 0){
        
        statusOfGame<< "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<"*: "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " << endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    
    else if (winningColony == 1){
        
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants << " ants  "<<c1->getColonyName()<<"*: "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " << endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    else if (winningColony == 2){
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants << " ants  "<<c1->getColonyName()<<": "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<"*: "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " << endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    
    
    else{
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<<setw(2)<<setfill('0')<<player1Ants<<" ants  " <<c2->getColonyName()<<": "<<setw(2)<<setfill('0')<<player2Ants<<" ants  " << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
}


void StudentWorld::setDisplayForTwoPlayers(Compiler *c0, Compiler* c1){
    AntsTick arrOfScores []= {m_antsPlayer0,m_antsPlayer1};
    
    
    AntsTick winningAntNumber = arrOfScores[0];
    int winningColony = 0;
    
    //this gets the highest ant
    for (int i = 1; i < 2; i++){
        if (arrOfScores[i] > winningAntNumber){
            winningColony = i;
            winningAntNumber = arrOfScores[i];
        }
    }
    
    
    
    //s
    ostringstream statusOfGame;
    
    
    
    int player0Ants = m_antsPlayer0.m_nAnts;
    int player1Ants = m_antsPlayer1.m_nAnts;
    
    
    //consider the very beginning
    if(player0Ants == player1Ants && player1Ants == 5){
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<<setw(2)<<setfill('0')<< player1Ants<<" ants  " << endl;
        string s = statusOfGame.str();
        
        setGameStatText(s);
        
    }
    
    else if(winningColony == 0){
        
        statusOfGame<< "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<"*: "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " <<endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    
    else if (winningColony == 1){
        
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants << " ants  "<<c1->getColonyName()<<"*: "<< setw(2)<<setfill('0')<<player1Ants<<" ants  " << endl;
        //statusOfGame << setw(4) << k << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    else{
        
        statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setfill('0')<<player0Ants <<" ants  "<<c1->getColonyName()<<": "<<setw(2)<<setfill('0')<<player1Ants<<" ants  " << endl;
        //statusOfGame.fill(' ');
        
        string s = statusOfGame.str();
        
        setGameStatText(s);
    }
    
    
    
}

void StudentWorld::setDisplayForOnePlayer(Compiler *c0){
    ostringstream statusOfGame;
    
    
    
    int player0Ants = m_antsPlayer0.m_nAnts;
    
    
    //consider the very beginning
    
    statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<" - "<<c0->getColonyName()<<": "<<setw(2)<<setfill('0')<<player0Ants <<" ants  "<<endl;
    
    setGameStatText(statusOfGame.str());
    
    
}


void StudentWorld::setDisplayForZeroPlayers(){
    ostringstream statusOfGame;
    
    
    //consider the very beginning
    
    statusOfGame << "Ticks:"<<setw(5)<<right<<getTicks()<<endl;
    
    setGameStatText(statusOfGame.str());
}

void StudentWorld::setDisplayText(int amountOfPlayers, Compiler* c0,Compiler* c1,Compiler* c2, Compiler* c3) {
    
    if(amountOfPlayers==0)
        setDisplayForZeroPlayers();
    
    if(amountOfPlayers == 1)
        setDisplayForOnePlayer(c0);
    
    if(amountOfPlayers == 2)
        setDisplayForTwoPlayers(c0, c1);
    if(amountOfPlayers == 3)
        setDisplayForThreePlayers(c0, c1, c2);
    if (amountOfPlayers == 4)
        setDisplayForFourPlayers(c0, c1, c2, c3);
    
}


GraphObject::Direction randomDirection(){
    
    int randomNumber = rand()%4;
    
    switch (randomNumber) {
        case 0:
            return GraphObject::left;
            break;
        case 1:
            return GraphObject::up;
            break;
        case 2:
            return GraphObject::down;
            break;
        case 3:
            return GraphObject::right;
            break;
        default:
            return GraphObject::right;
            break;
    }
}

int StudentWorld::someNumberFrom2To10() const{
    
    return rand() % 9 + 2;
}

int StudentWorld::getTicks() const{
    return m_ticks;
}

//Pheromone(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp);
void StudentWorld::createPheromone(int colonyNumber,int x, int y){
    
    //first ensure you're getting the correct pheromone id
    
    int id = -1; //arbitrary
    
    switch (colonyNumber) {
        case 0:
            id = IID_PHEROMONE_TYPE0;
            cerr<<"ID is currently: "<<id<<endl;
            break;
        case 1:
            id = IID_PHEROMONE_TYPE1;
            cerr<<"ID is currently: "<<id<<endl;
            break;
        case 2:
            id = IID_PHEROMONE_TYPE2;
            break;
        case 3:
            id = IID_PHEROMONE_TYPE3;
            break;
        default:
            break;
    }
    
    //then see if a pheromone of that ID is already there
    vector<Actor*> actorsInThisColumn = getListOfActorsInThisCol(x);
    for (int i = 0; i < actorsInThisColumn.size(); i++){
        if(actorsInThisColumn[i]->getY() == y && actorsInThisColumn[i]->isScent()){
            
            //found a pheromone object
            Pheromone* somePheromone = dynamic_cast<Pheromone*>(actorsInThisColumn[i]);
            
            //if there is a matching colony number
            if(somePheromone->getColonyNumber() == colonyNumber){
                somePheromone->modifyHP(256);
                if(somePheromone->getHP() > 768){
                    cerr<<"MY pheromone hp was "<<somePheromone->getHP()<<endl;
                    somePheromone->modifyHP(-(somePheromone->getHP()-768)); //this sets it to 768 if overboard
                    cerr<<"Now my hp after subtracting is "<<somePheromone->getHP();
                }
                cerr<<"Returning"<<endl;
                return;
            }
        }
    }
    
    //at this point this was a new pheromone
    Pheromone* php = new Pheromone(id,x,y,GraphObject::right,.25,2,this,256,colonyNumber);
    m_AllActors[php->getX()].push_back(php);
    cerr<<"Added a pheromone!"<<endl;
}


void StudentWorld::createFood(int x, int y,int energyUnits){
    Food* fp = new Food(IID_FOOD,x,y,GraphObject::right,0.25,2,this,energyUnits);
    m_AllActors[fp->getX()].push_back(fp);
    cerr<<"Added a food!"<<endl;
}

//this works at the cost of making a copy of the vector. and cannot be const if using [] operator (is pass by reference)
Actor* StudentWorld::getAnActorAtTheProposedLocation(int x1,int y1) const {
    //  cerr<<"Searching through the column where x = "<<x1<<endl;
    
    const vector<Actor*> copyOfList = getListOfActorsInThisCol(x1);
    for (int i = 0; i < copyOfList.size();i++){
        if (copyOfList[i]->getY() == y1)
            return copyOfList[i];
    }
    
    
    // cerr<<"Found nothing!"<<endl;
    return nullptr;
}


vector<Actor*> StudentWorld::getListOfActorsInThisCol(int x) const{
    auto search = m_AllActors.find(x);
    
    //if (search != m_AllActors.end()) i will just make sure this never happens
    return search->second;
    
}


//do this before letting the Actor do its thing (NOTICE HOW THIS WORKS EVEN IF THE ELEMENT NEVER MOVED AT ALL)
//transfers should only occur if an actor moved to a different column (i.e. moving left or right)
void StudentWorld::transferToAnotherList(Actor*& element,int xPrev, int xNow){
    
    //recall that [] is a REFERENCE -> can be modified
    
    Actor* tobeAdded = element;
    m_AllActors[tobeAdded->getX()].push_back(tobeAdded);
    
    
    //this really does work omg (erasing)
    m_AllActors[xPrev].erase(remove(m_AllActors[xPrev].begin(),m_AllActors[xPrev].end(),element),m_AllActors[xPrev].end());
    
}


void StudentWorld::addActorToAList(Actor *original, Actor *replacement){
    
    m_AllActors[original->getX()].push_back(replacement);
    // cerr<<"Added an actor with ID "<<replacement->getID()<<" with the original actor's vector of ID "<<original->getID()<<endl;
    
}


int StudentWorld::init(){
    srand ((int)time(0));
    cerr<<"initializing game world..."<<endl;
    string fieldFileName;
    Field f;
    std::string fieldFile = getFieldFilename();
    
    if (f.loadField(fieldFile) != Field::LoadResult::load_success){
        cerr<<"File not found!"<<endl;
        return false; // something bad happened!
    }
    
    //  cerr<<"Field file name is: "<<fieldFile<<endl;
    
    // otherwise the load was successful and you can access the
    // contents of the field – here’s an example
    
    
    Anthill* m_ahPlayer0;
    Anthill* m_ahPlayer1;
    Anthill* m_ahPlayer2;
    Anthill* m_ahPlayer3;
    
    
    
    // get the names of all of the ant program source files
    // we provide the getFilenamesOfAntPrograms() function for
    // you in our GameWorld class.
    vector<string> fileNames = getFilenamesOfAntPrograms();
    
    cerr<<"File names are:"<<endl;
    for (int i =0; i <fileNames.size();i++){
        cerr<<fileNames[i]<<endl;
        m_numberOfPlayers++;
    }
    cerr<<"Total files/players is: "<<fileNames.size()<<"/"<<m_numberOfPlayers<<endl;
    
    if(fileNames.size() >=1){
        m_cPlayer0 = new Compiler;
        string error;
        // compile the source file... If the compile function returns // false, there was a syntax error during compilation!
        if ( ! m_cPlayer0->compile(fileNames[0], error) ) {
            // entrant 0’s source code had a syntax error!
            setError(fileNames[0] + " " + error);
            
            delete m_cPlayer0;
            // return an error to tell our simulation framework
            // that something went wrong, and it’ll inform the user
            return GWSTATUS_LEVEL_ERROR;
        }
        cerr<<"Player 0 has arrived!"<<endl;
    }
    
    if(fileNames.size()>=2){
        m_cPlayer1 = new Compiler;
        string serror;
        // compile the source file... If the compile function returns // false, there was a syntax error during compilation!
        if ( ! m_cPlayer1->compile(fileNames[1], serror) ) {
            // entrant 0’s source code had a syntax error!
            setError(fileNames[1] + " " + serror);
            
            delete m_cPlayer1;
            // return an error to tell our simulation framework
            // that something went wrong, and it’ll inform the user
            return GWSTATUS_LEVEL_ERROR;
        }
        cerr<<"Player 1 has arrived!"<<endl;
    }
    
    if(fileNames.size()>=3){
        m_cPlayer2 = new Compiler;
        string sserror;
        // compile the source file... If the compile function returns // false, there was a syntax error during compilation!
        if ( ! m_cPlayer2->compile(fileNames[2], sserror) ) {
            // entrant 0’s source code had a syntax error!
            setError(fileNames[2] + " " + sserror);
            
            delete m_cPlayer2;
            // return an error to tell our simulation framework
            // that something went wrong, and it’ll inform the user
            return GWSTATUS_LEVEL_ERROR;
        }
        cerr<<"Player 2 has arrived!"<<endl;
    }
    
    if(fileNames.size()>=4){
        m_cPlayer3 = new Compiler;
        string ssserror;
        // compile the source file... If the compile function returns // false, there was a syntax error during compilation!
        if ( ! m_cPlayer3->compile(fileNames[3], ssserror) ) {
            // entrant 0’s source code had a syntax error!
            setError(fileNames[3] + " " + ssserror);
            
            delete m_cPlayer3;
            // return an error to tell our simulation framework
            // that something went wrong, and it’ll inform the user
            return GWSTATUS_LEVEL_ERROR;
        }
        cerr<<"Player 3 has arrived!"<<endl;
    }
    
    //if not mentioned, set depth to 1
    for (int x = 0 ; x < VIEW_WIDTH; x++){
        //indeed a vector column, not a row of actors
        vector<Actor*> listOfActorsInThisCol;
        
        for (int y=0; y < VIEW_HEIGHT;y++){
            Field::FieldItem item = f.getContentsOf(x,y); // note it’s x,y and not y,x!!!
            
            
            
            //A Pebble object must start out with a depth of 1.
            if (item == Field::FieldItem::rock){
                Actor* pp = new Pebble(IID_ROCK,x,y,GraphObject::right,0.25, 1,this);
                listOfActorsInThisCol.push_back(pp);
                // cerr<<"Add a pebble at ("<<x<<","<<y<<")"<<endl;
            }
            
            //A Pool of Water always has a depth of 2.
            if (item == Field::FieldItem::water){
                Actor* wp = new Waterpool(IID_WATER_POOL,x,y,GraphObject::right,0.25, 2, this);
                listOfActorsInThisCol.push_back(wp);
                //  cerr<<"Add a waterpool at ("<<x<<","<<y<<")"<<endl;
                
            }
            
            
            //recall all food is made with 100 points in game
            if (item == Field::FieldItem::food){
                Actor* fp = new Food(IID_FOOD,x,y,GraphObject::right,0.25, 2, this,6000);
                listOfActorsInThisCol.push_back(fp);
                // cerr<<"Add a babygrasshopper at ("<<x<<","<<y<<")"<<endl;
                
            }
            
            
            
            // The BabyGrasshopper must start out with 500 hit points.
            if (item == Field::FieldItem::grasshopper){
                GraphObject::Direction randomdir = randomDirection();
                Actor* bgp = new BabyGrasshopper(IID_BABY_GRASSHOPPER,x,y,randomdir,0.25, 1, this,500,rand() % 9 + 2);
                listOfActorsInThisCol.push_back(bgp);
                // cerr<<"Add a babygrasshopper at ("<<x<<","<<y<<")"<<endl;
                // cerr<<"This baby grasshopper starts by moving in this direction: "<<randomdir<<endl;
            }
            
            
            if (item == Field::FieldItem::poison){
                Poison* pp = new Poison(IID_POISON,x,y,GraphObject::right,0.25, 2, this);
                listOfActorsInThisCol.push_back(pp);
            }
            
            
            
            if (item == Field::FieldItem::anthill0 && m_numberOfPlayers >=1){
                m_ahPlayer0 = new Anthill(IID_ANT_HILL,x,y,GraphObject::right,0.25,2,this,8999,0,m_cPlayer0);
                listOfActorsInThisCol.push_back(m_ahPlayer0);
                cerr<<"Anthill,PLEASE HAVE POINTER POINT TO SAME ADDRESS AS ABOVE:"<<&*m_ahPlayer0->getCompiler()<<endl;
            }
            
            
            if (item == Field::FieldItem::anthill1 && m_numberOfPlayers >= 2){
                m_ahPlayer1 = new Anthill(IID_ANT_HILL,x,y,GraphObject::right,0.25,2,this,8999,1,m_cPlayer1);
                listOfActorsInThisCol.push_back(m_ahPlayer1);
            }
            
            if (item == Field::FieldItem::anthill2 && m_numberOfPlayers >= 3){
                m_ahPlayer2 = new Anthill(IID_ANT_HILL,x,y,GraphObject::right,0.25,2,this,8999,2,m_cPlayer2);
                listOfActorsInThisCol.push_back(m_ahPlayer2);
            }
            
            if (item == Field::FieldItem::anthill3 && m_numberOfPlayers >= 4){
                m_ahPlayer3 = new Anthill(IID_ANT_HILL,x,y,GraphObject::right,0.25,2,this,8999,3,m_cPlayer3);
                listOfActorsInThisCol.push_back(m_ahPlayer3);
            }
            
        }
        
        //add vectors to map
        pair<int, vector<Actor*> > somePair (x, listOfActorsInThisCol);
        m_AllActors.insert(somePair);
        
        
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    
    
    m_ticks--;
    
    //keep track of previous locations so a helper function knows where to remove actors from
    queue<int> prevX;
    vector<Actor*>elementsThatChangedX;
    
    
    
    //i think you should let everyone move first before transferring, but somehow keep note of where things will transfer to
    for (int i = 0; i < VIEW_WIDTH;i++){
        vector<Actor*> someVec = m_AllActors[i];
        for (int j = 0; j < someVec.size();j++){
            if (someVec[j]->isAlive()){
                
                //x initial
                
                int xInit = someVec[j]->getX();
                
                /*if(someVec[j]->getID()==IID_BABY_GRASSHOPPER)
                 someVec[j]->setDirection(randomDirection());*/
                someVec[j]->doSomething();
                
                
                
                //if it is still alive after it does its action?
                
                if(someVec[j]->getX()!=xInit){
                    // cerr<<"Vec["<<xInit<<"] is size: "<<someVec.size()<<endl;
                    prevX.push(xInit);
                    // cerr<<"Vec["<<xInit<<"] lost a member!"<<endl;
                    
                    elementsThatChangedX.push_back(someVec[j]);
                }
                
                
                
            }
            
        }
    }
    
    
    
    for (int i = 0; i <elementsThatChangedX.size();i++){
        int someX = prevX.front();
        transferToAnotherList(elementsThatChangedX[i], someX, elementsThatChangedX[i]->getX());
        prevX.pop();
    }
    
    //now let's try to clean up stuff
    for (int i = 0; i < VIEW_WIDTH;i++){
        for (int j = 0; j <m_AllActors[i].size();j++){
            
            if(m_AllActors[i][j]->isAlive()==false){
                
                
                Actor* someDeadActor = m_AllActors[i][j]; //remember where to point to so to delete
                delete someDeadActor;
                m_AllActors[i].erase(remove(m_AllActors[i].begin(),m_AllActors[i].end(),m_AllActors[i][j]),m_AllActors[i].end());
                
            }
            
            
        }
    }
    setDisplayText(m_numberOfPlayers,m_cPlayer0,m_cPlayer1,m_cPlayer2,m_cPlayer3);
    
    cerr<<"So far, player0 has produced "<<m_antsPlayer0.m_nAnts<<" at "<<m_antsPlayer0.m_currentTick<<endl;
    cerr<<"So far, player1 has produced "<<m_antsPlayer1.m_nAnts<<" at "<<m_antsPlayer1.m_currentTick<<endl;
    cerr<<"So far, player2 has produced "<<m_antsPlayer2.m_nAnts<<" at "<<m_antsPlayer2.m_currentTick<<endl;
    cerr<<"So far, player3 has produced "<<m_antsPlayer3.m_nAnts<<" at "<<m_antsPlayer3.m_currentTick<<endl;
    
    if(m_ticks <=0){
        
        //check no players
        if(m_numberOfPlayers == 0)
            return GWSTATUS_NO_WINNER;
        else if(m_numberOfPlayers == 1){
            setWinner(m_cPlayer0->getColonyName());
            return GWSTATUS_PLAYER_WON;
        }
        else if(m_numberOfPlayers == 2)
            return checkWinnerForTwoPlayers();
        else if (m_numberOfPlayers == 3)
            return checkWinnerForThreePlayers();
        else if (m_numberOfPlayers == 4)
            return checkWinnerForFourPlayers();
        
        
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    
    for(int i = 0; i < VIEW_WIDTH;i++){
        cerr<<"Vec["<<i<<"] is of size "<<m_AllActors[i].size()<<endl;
    }
    
    int countOfTotalItems = 0; //make sure things are deleted
    int totalVectors = 0;
    for(int i = 0; i < VIEW_WIDTH;i++){
        
        totalVectors++;
        for(int j = 0; j < m_AllActors[i].size();j++)
            countOfTotalItems++;
        
    }
    cerr<<"All vectors before deleting "<<totalVectors<<endl;
    cerr<<"All items before delete: "<<countOfTotalItems<<endl;
   
    
    
    //the above code simply records the previous state of the world before deleting everything
     cerr<<"DIE! DIE! DIE!"<<endl;
    
    
    
    //traverse through the unordered_map, visiting every vector from its back element and popping it O(1) time to remove !
    
    for(unordered_map<int, vector<Actor*> > :: iterator deleter = m_AllActors.begin(); deleter != m_AllActors.end();){
    
        for (int y = deleter->second.size()-1; y >=0; --y){
            
            delete deleter->second[y];
            deleter->second.pop_back();
            countOfTotalItems--;
            
        }
        deleter = m_AllActors.erase(deleter); //remember that erase returns back an iterator of first thing not removed
        totalVectors--;
        
    }
    cerr<<"All vectors after deleting "<<totalVectors<<endl;
         cerr<<"All items after delete: "<<countOfTotalItems<<endl;
    for(int i = 0; i < VIEW_WIDTH;i++){
        cerr<<"Vec["<<i<<"] is of size "<<m_AllActors[i].size()<<endl;
    }
    
    cerr<<"Size of map before clearing everything "<<m_AllActors.size()<<endl;
    
    
    
    //only after all the memory is freed that it is safe to call clear()
    m_AllActors.clear();
    
    cerr<<"Size of map after clearing everything "<<m_AllActors.size()<<endl;
    
    
    
    //also delete any Compilers that were new'd
    
    if (m_cPlayer0){
        cerr<<"Since i am player 0, i will delete myself "<<endl;
        delete m_cPlayer0;
    }
    
    if (m_cPlayer1){
        cerr<<"Since i am player 1, i will delete myself "<<endl;
        delete m_cPlayer1;
    }
    
    if (m_cPlayer2){
        cerr<<"Since i am player 2, i will delete myself "<<endl;
        delete m_cPlayer2;
    }
    
    if (m_cPlayer3){
        cerr<<"Since i am player 3, i will delete myself "<<endl;
        delete m_cPlayer3;
    }
    
    
}





