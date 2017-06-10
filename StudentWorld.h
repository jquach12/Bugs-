#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>


#include <unordered_map>
#include <vector>
#include "Field.h"
#include <list>
#include <map>
#include <ctime>
#include <random>
#include <queue>

class Actor;         //"use the class to define a pointer variable"
class Compiler;
class Anthill;

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//maybe should have made a struct Coordinate, oh well

struct AntsTick{
    int m_nAnts = 0;
    int m_currentTick = 2000; //need to remember this
    
    bool operator>(const AntsTick& other){
        if (this->m_nAnts > other.m_nAnts)
            return true;
        else if (this->m_nAnts == other.m_nAnts && this->m_currentTick > other.m_currentTick)
            return true;
        else
            return false;
    }
};


class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
    }
    int getTicks() const;
    int someNumberFrom2To10() const;
    //can be const at the cost of recopying vectors
    Actor* getAnActorAtTheProposedLocation(int x1,int y1) const;
    vector<Actor*> getListOfActorsInThisCol(int x) const;
    
    void updateAmountOfAntsInThisColony(int colonyNumber, int delta, int tickMark);
    int getAntCountForThisAntColony(int colonyNumber) const;
    void transferToAnotherList(Actor*& element,int xPrev, int xNow);
    void addActorToAList(Actor* original, Actor* replacement);
    
    void createPheromone(int colonyNumber,int x, int y);
    void createFood(int x, int y, int energyUnits);
    
    void setDisplayText(int amountOfPlayers,Compiler* c0,Compiler* c1,Compiler* c2, Compiler* c3);
    void setDisplayForFourPlayers(Compiler* c0,Compiler* c1,Compiler* c2, Compiler* c3);
    void setDisplayForThreePlayers(Compiler* c0,Compiler* c1,Compiler* c2);
    void setDisplayForTwoPlayers(Compiler* c0, Compiler* c1);
    void setDisplayForOnePlayer(Compiler* c0);
    void setDisplayForZeroPlayers();
    
    int checkWinnerForFourPlayers();
    int checkWinnerForThreePlayers();
    int checkWinnerForTwoPlayers();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    
private:
    
    int m_ticks = 2000;
    //list<Actor*> m_allActors;
    
    // vector <  list<Actor* >  > m_allActors;
    
    //   map < int,list<Actor*> > m_allActors[64];
    
    // unordered_map<Coord, vector<Actor*>, Hashy,EqualsTo > m_AllActors;

    unordered_map<int, vector<Actor*> > m_AllActors;
    
    //these guys keep track of ants for each colony and the tick mark where they reached that ant quantity
    AntsTick m_antsPlayer0;
    AntsTick m_antsPlayer1;
    AntsTick m_antsPlayer2;
    AntsTick m_antsPlayer3;
    
    int m_numberOfPlayers = 0;
    //the following Anthill* pointers are 
    Compiler* m_cPlayer0 = nullptr;
    Compiler* m_cPlayer1 = nullptr;
    Compiler* m_cPlayer2 = nullptr;
    Compiler* m_cPlayer3 = nullptr;
};

#endif // STUDENTWORLD_H_



