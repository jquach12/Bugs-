#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

//#include "StudentWorld.h"
#include <random>
#include <ctime>
class StudentWorld;
class Compiler;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject{
public:
    
    Actor(int iid, int xInit,int yInit, Direction dInit,double imageSize,int depth,StudentWorld* ptrToWorld,bool blocksSquare, bool couldStun, bool isToxic,bool canMove, bool isScent);
    virtual ~Actor();
    
    virtual void doSomething() = 0; //we want to make this an ABC
    StudentWorld* getWorld() const;
    bool isAlive() const; //need this so base pointer can do move
    void setDead();
    bool blocksSquare() const;
    bool canStun() const;
    bool isToxic() const;
    bool canMove() const;
    bool canBite() const;
    bool isScent() const;
    
    // can block, stun, poison, move, bite, smell
private:
    StudentWorld* m_wptr; //every actor has a pointer to the world it lives in
    bool m_isAlive = true;
    bool m_blocksSquare = false;
    bool m_couldStun = false;
    bool m_isToxic = false;
    bool m_canMove = false;
    bool m_canBite = false;
    bool m_isScent = false;
    
};

class Pebble : public Actor{
public:
    Pebble(int iid, int xInit,int yInit,Direction dInit,double imageSize,int depth, StudentWorld* ptrToWorld);
    virtual void doSomething();
};

class Waterpool : public Actor{
public:
    Waterpool(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld);
    virtual void doSomething();
};


class Poison : public Actor{
public:
    Poison(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld);
    virtual void doSomething();
};




//things that exhibit life like features, still an ABC
class EnergyHolder : public Actor{
public:
    
    EnergyHolder(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,bool canMove,bool isScent);
    //virtual void doSomething() = 0;
    void modifyHP(long deltaHP);
    long getHP() const;
    Actor* isSteppingOnFood(int x1,int y1) const;
    
private:
    long m_hp;
    
};



class Food : public EnergyHolder{
public:
    Food(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp);
    virtual void doSomething();
};



class Pheromone : public EnergyHolder{
public:
    Pheromone(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int someColonyNumber);
    int getColonyNumber() const;
    virtual void doSomething();
private:
    int m_pColonyNumber;
};


class Anthill : public EnergyHolder{
public:
    Anthill(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int colonyNumber,Compiler* c);
    virtual void doSomething();
    int getColonyNumber() const;
    Compiler* getCompiler() const;
    void seeIfICanMakeAnts();
    
private:
    int m_colonyNumber = 0;
    Compiler* m_compiler;
};














//still an abc
class Insect : public EnergyHolder{
public:
    Insect(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp);
    // Actor* isSteppingOnFood(int x1,int y1) const;
    //virtual void doSomething() = 0;
    bool isStunned() const;
    void stunnedByWater();
    void decrementStunTick();
    int getStunTicks() const;
    void setAlreadyStunned();
    
    void checkIfSteppedOnWaterOrPoison();
    
    
    void becomeFood();
    
    GraphObject::Direction getRandomDirection();
    //virtual bool attemptMove() = 0;
    
private:
    int m_stunTicks = 0;
    int m_walk;
    bool m_alreadyStunned = false;
};


class BabyGrasshopper : public Insect{
public:
    BabyGrasshopper(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int initJumps);
    virtual void doSomething();
    void decrementWalk();
    void setWalk(int n);
    int getWalk() const;
    void decrementDoesSomething();
    int getDoesSomething() const;
    void setDoesSomething(int n){
        m_doesSomething = n;
    }
    
private:
    int m_doesSomething = 2;
    int m_walk;
};

//lol a little backwards
class AdultGrasshopper : public BabyGrasshopper{
public:
    AdultGrasshopper(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int initJumps);
    virtual void doSomething();
    void attemptBite();
    void attemptJump();
    
private:
    int m_willBite = 0;

};




class Ant: public Insect{
public:
    Ant(int iid, int xInit,int yInit,Direction dInit, double imageSize, int depth, StudentWorld* ptrToWorld, long hp, int colonyNumber, Compiler* someCompiler);
    virtual void doSomething();
    void setLastRandomValue(int r);
    void interpreter();
    
    int getColonyNumber() const;
    void shouldIRememberIGotBlocked(bool value);
    void shouldIRememberSomeoneBitMe(bool value);
    
    int getAmountofFoodIAmHolding() const;
    void modifyMyCurrentFoodCount(int delta);
    
    void setInstructionCounter(int n);
    
    bool hasExecutedTenCommands() const;
    
    bool isStandingWithAnEnemy() const;
    bool isStandingOnMyAnthill() const;
    
    bool isPheromoneInFrontOfMe() const;
    bool isDangerInFrontOfMe() const;
    
    void justGotBit();
    
private:
    int m_lastRandomValue = 0;
    int m_instructionsCounter = 0;
    Compiler* m_antCompiler;
    bool m_rememberBlocked = false;
    bool m_rememberGotBit = false;
    int m_amtOfFoodHolding = 0;
    int m_colonyNumber;
    
    
};


#endif // ACTOR_H_
