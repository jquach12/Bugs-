#include "Actor.h"
#include "StudentWorld.h"
#include <ctime>
#include <random>
#include <cmath>
#include "Compiler.h"
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor :: Actor(int iid, int xInit,int yInit, Direction dInit,double imageSize, int depth,StudentWorld* ptrToWorld,bool blocksSquare,bool couldStun,bool isToxic, bool canMove,bool isScent)
:GraphObject(iid,xInit,yInit,dInit,imageSize,depth),m_wptr(ptrToWorld),m_blocksSquare(blocksSquare),m_couldStun(couldStun),m_isToxic(isToxic),m_canMove(canMove),m_isScent(isScent)
{}

Actor::~Actor()
{}

void Actor :: setDead(){
    m_isAlive = false;
}

bool Actor :: isAlive() const{
    return m_isAlive;
}


StudentWorld* Actor :: getWorld() const{
    return m_wptr;
}

bool Actor ::blocksSquare() const{
    return m_blocksSquare;
}

bool Actor :: canStun() const{
    return m_couldStun;
}

bool Actor :: isToxic() const{
    return m_isToxic;
}

bool Actor :: canMove() const{
    return m_canMove;
}

bool Actor :: canBite() const{
    return m_canBite;
}

bool Actor :: isScent() const{
    return m_isScent;
}

//PEBBLE
Pebble :: Pebble(int iid, int xInit,int yInit, Direction dInit,double imageSize,int depth, StudentWorld* ptrToWorld)
:Actor(iid,xInit,yInit, dInit,imageSize,depth, ptrToWorld,true,false,false,false,false)
{}

void Pebble:: doSomething(){
    
    return;
}


//POOL OF WATER

Waterpool::Waterpool(int iid, int xInit,int yInit, Direction dInit,double imageSize,int depth, StudentWorld* ptrToWorld)
:Actor(iid,xInit,yInit,dInit,imageSize,depth, ptrToWorld,false,true,false,false,false)
{}


void Waterpool:: doSomething(){
    // cerr<<"Im water. Cash me at: "<<getX()<<","<<getY()<<endl;
    
    /* easier implementation if the insects check if they stepped on waterpool, rather than have waterpool check if they were stepped on */
    
}


Poison::Poison(int iid, int xInit,int yInit, Direction dInit,double imageSize,int depth, StudentWorld* ptrToWorld)
:Actor(iid,xInit,yInit,dInit,imageSize,depth, ptrToWorld,false,false,true,false,false)
{}

void Poison:: doSomething(){
    //cerr<<"Greetings, im a poison at location "<<getX()<<","<<getY()<<endl;
}


/*****************************************************************************************************************************************************
 *****************************************************************************************************************************************************
 */




EnergyHolder::EnergyHolder(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp, bool canMove,bool isScent)
:Actor(iid,xInit,yInit,dInit,imageSize,depth, ptrToWorld,false,false,false,canMove,isScent),m_hp(hp)
{}

void EnergyHolder::modifyHP(long deltaHP){
    m_hp += deltaHP;
}



long EnergyHolder::getHP() const{
    return m_hp;
}


Actor* EnergyHolder::isSteppingOnFood(int x1, int y1) const{
    vector<Actor*> copy = getWorld()->getListOfActorsInThisCol(x1);
    for (int i = 0; i < copy.size();i++){
        
        if(copy[i]->getY()==getY()){
            Food* fp = dynamic_cast<Food*>(copy[i]);
            if(fp && fp->isAlive()){
                // cerr<<"Stepped on a food at "<<x1<<","<<y1<<endl;
                return copy[i];
            }
        }
        /*
         if (copy[i]->getY() == y1 && copy[i]->getID()==IID_FOOD){
         // cerr<<"Stepped on a food at "<<x1<<","<<y1<<endl;
         return copy[i];
         
         }*/
    }
    
    return nullptr;
}



Food::Food(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp)
:EnergyHolder(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp,false,false)
{}

void Food::doSomething()
{/*do nothing*/}


Pheromone::Pheromone(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int someColonyNumber)
:EnergyHolder(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp,false,true),m_pColonyNumber(someColonyNumber)
{}

void Pheromone::doSomething()
{
    modifyHP(-1);
    if(getHP()<=0){
        cerr<<"Pheromone died"<<endl;
        this->setDead();
    }
}

int Pheromone::getColonyNumber() const{
    return m_pColonyNumber;
}

Anthill::Anthill(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int colonyNumber,Compiler* c)
:EnergyHolder(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp,false,false),m_colonyNumber(colonyNumber),m_compiler(c)
{}

int Anthill:: getColonyNumber() const{
    return m_colonyNumber;
}

Compiler* Anthill:: getCompiler() const{
    return m_compiler;
}


void Anthill::seeIfICanMakeAnts(){
    if(this->getHP()>=2000){
        
        
        
        // cerr<<"Adding an ant!"<<endl;
        modifyHP(-1500);
        int randomNumber = rand()%4;
        GraphObject::Direction someRandomDirection;
        switch (randomNumber) {
            case 0:
                someRandomDirection = GraphObject::left;
                break;
            case 1:
                someRandomDirection = GraphObject::up;
                break;
            case 2:
                someRandomDirection = GraphObject::down;
                break;
            case 3:
                someRandomDirection = GraphObject::right;
                break;
            default:
                cerr<<"Default direction case! let's say left"<<endl; //this never occurs
                someRandomDirection = GraphObject::left;
                break;
        }
        
        int someID;
        
        if(getColonyNumber() ==0)
            someID = IID_ANT_TYPE0;
        else if(getColonyNumber() == 1)
            someID  = IID_ANT_TYPE1;
        else if(getColonyNumber() == 2)
            someID = IID_ANT_TYPE2;
        else if(getColonyNumber() == 3)
            someID = IID_ANT_TYPE3;
        
        
        
        Ant* someAnt = new Ant(someID,this->getX(),this->getY(),someRandomDirection,1.25,1,getWorld(),1500,this->getColonyNumber(),this->getCompiler());
        getWorld()->updateAmountOfAntsInThisColony(this->getColonyNumber(), +1,getWorld()->getTicks());
        cerr<<"Created an ant at "<<getX()<<","<<getY()<<endl;
        getWorld()->addActorToAList(this, someAnt);
        
        
    }
}

void Anthill::doSomething(){
    modifyHP(-1);
    // cerr<<"Current hp of this ant hill is "<<this->getHP()<<endl;
    
    if(getHP()<=0){
        cerr<<"Ant hill died at "<<getX()<<","<<getY()<<endl;
        
        setDead();
        return;
    }
    
    //maybe easier if the ant takes care of this stuff
    Actor* someFood = isSteppingOnFood(getX(), getY());
    if(someFood){
        Food* fp = dynamic_cast<Food*>(someFood);
        if(fp){
            
            //check if the food has 10000 hp
            if(fp->getHP()>=10000){
                this->modifyHP(10000);
                fp->modifyHP(-10000);
                cerr<<fp->getHP()<<endl;
                cerr<<"Yum a whole 10000 hp from food"<<endl;
            }
            else{
                this->modifyHP(fp->getHP());
                fp->setDead();
                cerr<<"yum, partial food"<<endl;
            }
            
            return;
        }
        
        
        
        
    }
    
    
    
    
    if(this->getHP()>=2000){
        // cerr<<"Adding an ant!"<<endl;
        modifyHP(-1500);
        int randomNumber = rand()%4;
        GraphObject::Direction someRandomDirection;
        switch (randomNumber) {
            case 0:
                someRandomDirection = GraphObject::left;
                break;
            case 1:
                someRandomDirection = GraphObject::up;
                break;
            case 2:
                someRandomDirection = GraphObject::down;
                break;
            case 3:
                someRandomDirection = GraphObject::right;
                break;
            default:
                cerr<<"Default direction case! let's say left"<<endl; //this never occurs
                someRandomDirection = GraphObject::left;
                break;
        }
        
        int someID = 0;
        
        if(getColonyNumber() ==0)
            someID = IID_ANT_TYPE0;
        else if(getColonyNumber() == 1)
            someID  = IID_ANT_TYPE1;
        else if(getColonyNumber() == 2)
            someID = IID_ANT_TYPE2;
        else if(getColonyNumber() == 3)
            someID = IID_ANT_TYPE3;
        
        
        
        Ant* someAnt = new Ant(someID,this->getX(),this->getY(),someRandomDirection,1.25,1,getWorld(),1500,this->getColonyNumber(),this->getCompiler());
        
        getWorld()->updateAmountOfAntsInThisColony(this->getColonyNumber(), +1,getWorld()->getTicks());
        cerr<<"Created an ant at "<<getX()<<","<<getY()<<endl;
        getWorld()->addActorToAList(this, someAnt);
        /* //ask studentworld to increase ant count that this colony has produced*/
    }
    
    
}


///INSECT

//still ABC
Insect::Insect(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp)
:EnergyHolder(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp,true,false)
{}

void Insect::stunnedByWater(){
    m_stunTicks += 2;
}

bool Insect:: isStunned() const{
    return m_stunTicks > 0;
}

void Insect:: decrementStunTick(){
    m_stunTicks -= 1;
}

int Insect :: getStunTicks() const{
    return m_stunTicks;
}




void Insect::setAlreadyStunned(){
    m_alreadyStunned = true;
}

void Insect::checkIfSteppedOnWaterOrPoison(){
    //check if stepped on a water pool
    vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(getX());
    for (int i = 0; i < someList.size();i++){
        if (someList[i]->getY()==getY() && someList[i]->canStun()){
            stunnedByWater();
            // cerr<<"stunned water!"<<endl;
            return;
        }
        else if(someList[i]->getY()==getY() && someList[i]->isToxic()){
            modifyHP(-150);
            cerr<<"Ouch! Stepped on poison at "<<getX()<<","<<getY()<<endl;
            
        }
    }
    
}

void Insect::becomeFood(){
    
    //first check if there is food already on this square
    
    Actor* maybeFood = getWorld()->getAnActorAtTheProposedLocation(getX(), getY());
    if (maybeFood){
        //
        //cerr<<"Found something with an id "<<maybeFood->getID()<<endl;
        
        //   cerr<<"Examining the square "<<getX()<<","<<getY()<<endl;
        
        // cerr<<"In column "<<getX()<<", there are: "<<endl;
        vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(getX());
        for (int i = 0; i < someList.size();i++){
            //cerr<<"There is something with ID "<<someList[i]->getID()<<endl;
            if(someList[i] != nullptr){
                
                //only care about actors in the same square
                if(someList[i]->getY() == this->getY()){
                    
                    
                    //    cerr<<"Hey there is food at "<<someList[i]->getX()<<","<<someList[i]->getY()<<endl;
                    Food* fp = dynamic_cast<Food*>(someList[i]);
                    if (fp){
                        //   cerr<<"Before leaving a carcass: "<<fp->getHP()<<endl;
                        fp->modifyHP(+100);
                        //  cerr<<"Healed a food at "<<getX()<<","<<fp->getY()<<endl;
                        //  cerr<<"After: "<<fp->getHP()<<endl;
                        return; //need this before it tries to allocate a new food
                    }
                    
                }
                
            }
            
            
        }
        
    }
    
    // at this point, it was a new food
    Food* newFood = new Food(IID_FOOD,getX(),getY(),GraphObject::right,0.25,2,getWorld(),100);
    getWorld()->addActorToAList(this, newFood);
    cerr<<"Allocated a new food during game"<<endl;
    return;
    
    
}

GraphObject::Direction Insect:: getRandomDirection(){
    
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
            cerr<<"Default direction case! let's say left"<<endl; //this never occurs
            return GraphObject::left;
            break;
    }
    
}



BabyGrasshopper::BabyGrasshopper(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp, int initWalk)
:Insect(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp),m_walk(initWalk)
{}



void BabyGrasshopper::decrementWalk(){
    m_walk--;
}

void BabyGrasshopper::setWalk(int n){
    m_walk=n;
}
int BabyGrasshopper::getWalk() const{
    return m_walk;
}

void BabyGrasshopper::decrementDoesSomething(){
    m_doesSomething--;
}

int BabyGrasshopper::getDoesSomething() const{
    return m_doesSomething;
}

void BabyGrasshopper::doSomething(){
    
    
    
    //The baby grasshopper loses one hit point (as it gets hungrier).
    modifyHP(-1);
    
    
    if(m_doesSomething == 1){
        m_doesSomething = 0;
        return;
    }
    
    if (m_doesSomething == 0){
        m_doesSomething = 2;
        return;
    }
    
    m_doesSomething--;
    
    /*
     //sleep every 2 ticks
     if (getWorld()->getTicks() % 3 != 0){
     // cerr<<"I will sleep this turn"<<endl;
     
     return;
     
     }*/
    
    
    
    if (getHP()<=0){
        this->setDead();
        cerr<<"i died :("<<endl;
        
        becomeFood();
        return;
    }
    
    
    
    if (isStunned()){
        //  cerr<<"I am stunned!"<<endl;
        decrementStunTick();
        // cerr<<"My stun tick count is.."<<getStunTicks()<<endl;
        return;
    }
    
    
    //Otherwise, the baby grasshopper is going to do something this round.
    
    
    // cerr<<"hi im a grasshopper"<<endl;
    
    
    //check if stepping on food
    Actor* hopefullyFood = isSteppingOnFood(getX(), getY());
    if(hopefullyFood){
        
        
        Food* fp = dynamic_cast<Food*>(hopefullyFood);
        
        if (fp != nullptr){
            
            //    cerr<<"Found a food!"<<endl;
            
            //baby grasshopper consumed all of the food
            if(fp->getHP() <= 200){
                this->modifyHP(fp->getHP());
                fp->modifyHP(-(fp->getHP()));
                fp->setDead();
                cerr<<"killed all the food"<<endl;
            }
            else{
                this->modifyHP(+200);
                //cerr<<"Food hp is "<<fp->getHP()<<endl;
                fp->modifyHP(-200);
                //  cerr<<"Ow. you ate part of me!"<<endl;
                //  cerr<<"Food hp is "<<fp->getHP()<<endl;
            }
            
            if (getHP() >= 1600){
                setDead();
                
                becomeFood();
                
                //  cerr<<"Molting!!!!"<<endl;
                AdultGrasshopper* agp = new AdultGrasshopper(IID_ADULT_GRASSHOPPER,getX(),getY(),getRandomDirection(),1.25,1,getWorld(),1600,rand()%9 + 2);
                agp->setDoesSomething(2);
                getWorld()->addActorToAList(this, agp);
                
                
                return;
                
            }
            //this is a number between 0 and 1. 50% chance of resting
            int randNum = rand() % 2;
            if (randNum==0)
                return;
            
            
            
        }
        
        
        
    }
    
    
    int xInit = this->getX();
    int yInit = this->getY();
    
    int xFinal = xInit;
    int yFinal = yInit;
    
    GraphObject::Direction moveInThisDirection = this->getDirection();
    
    if (moveInThisDirection==GraphObject::left)
        xFinal -=1;
    else if (moveInThisDirection==GraphObject::right)
        xFinal +=1;
    else if (moveInThisDirection==GraphObject::up)
        yFinal +=1;
    else if (moveInThisDirection==GraphObject::down)
        yFinal -=1;
    
    
    Actor* ap = getWorld()->getAnActorAtTheProposedLocation(xFinal, yFinal);
    if(ap && ap->blocksSquare()){
        m_walk = 0;
        // cerr<<"Blocked you at location "<<xFinal<<","<<yFinal<<endl;
    }
    
    
    if (m_walk>0){
        if (getDirection()==left)
            moveTo(getX()-1, getY());
        else if (getDirection()==right)
            moveTo(getX()+1,getY());
        else if (getDirection()==up)
            moveTo(getX(),getY()+1);
        else if (getDirection()==down)
            moveTo(getX(), getY()-1);
        
        m_walk--;
        
        
        checkIfSteppedOnWaterOrPoison();
        
        
    }
    else{
        m_walk = rand() % 9 + 2;
        switch (getRandomDirection()) {
            case GraphObject::left:
                this->setDirection(left);
                break;
            case GraphObject::right:
                this->setDirection(right);
                break;
            case GraphObject::up:
                this->setDirection(up);
                break;
            case GraphObject::down:
                this->setDirection(down);
                break;
            default:
                break;
        }
    }
    
}


AdultGrasshopper::AdultGrasshopper(int iid, int xInit,int yInit,Direction dInit, double imageSize,int depth, StudentWorld* ptrToWorld, long hp,int initJumps)
:BabyGrasshopper(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp,initJumps)
{}

void AdultGrasshopper::attemptBite(){
    
    if(m_willBite == 1){
        //first get list of all the potential stuff to be bitten
        vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(getX());
        
        
        vector<Actor*> potentialVictims;
        
        for (int i = 0; i < someList.size();i++){
            if (someList[i]->canMove()){
                
                //check if pointing to yourself
                if(&*someList[i] == &*this){
                    //    cerr<<"Pointing at myself! dont bite myself!"<<endl;
                    continue;
                }
                
                potentialVictims.push_back(someList[i]);
                //cerr<<"Added this guy into my victim list "<<someList[i]->getID()<<endl;;
                
                
                
            }
        }
        //cerr<<"Victim size: "<<potentialVictims.size()<<endl;
        if(potentialVictims.size()==0)
            return;
        
        //so say it stores 4 insects, then [0],[1],[2],[3] are filled
        int victim_index = rand() % potentialVictims.size();
        Actor* victim = potentialVictims[victim_index];
        if(victim){
            //get the pointer
            Insect* ip = dynamic_cast<Insect*>(victim);
            if(ip){
                cerr<<"My hp was "<<ip->getHP()<<endl;
                ip->modifyHP(-50);
                cerr<<"Ow. i got bit! at location "<<getX()<<","<<getY()<<endl;
                cerr<<"Current hp: "<<ip->getHP()<<endl;
                
                
                
                
                //check if wat you bit was an Ant
                Ant* maybeAnEnemyAnt = dynamic_cast<Ant*>(ip);
                if(maybeAnEnemyAnt)
                    maybeAnEnemyAnt->justGotBit();
                
                //if the victim is still alive and was an adult grasshopper, 1/2 chance of biting some other guy
                AdultGrasshopper* maybeAdultGrasshopper = dynamic_cast<AdultGrasshopper*>(ip);
                if(maybeAdultGrasshopper && maybeAdultGrasshopper->getHP() > 0 ){
                    
                    //  cerr<<"hm"<<endl;
                    int perhapsBiteBack = rand() % 2;
                    if(perhapsBiteBack){
                        
                        cerr<<"Last night i took an l but tonight i bite back"<<endl;
                        maybeAdultGrasshopper->attemptBite();
                        cerr<<"The assailant hp is "<<maybeAdultGrasshopper->getHP()<<endl;
                    }
                    
                }
            }
        }
        
        
    }
}


void AdultGrasshopper::attemptJump(){
    
    int random = rand() % 10;
    if (random==0){
        
        cerr<<"Cos time thingy:"<<endl;
        //cerr<<cos(time(0))<<endl;
        
        float pi = 3.14159;
        
        //add .5 to round up
        double someCosValue = cos(randInt(0,2*pi));
        double someSinValue = sin(randInt(0,2*pi));
        
        
        cerr<<"My origin is "<<getX()<<","<<getY()<<endl;
        float xOrigin = getX();
        float yOrigin = getY();
        
        cerr<<"i want to move this distance horizontally: "<< someCosValue*10 <<endl;
        cerr<<"i want to move this distance vertically: "<< someSinValue*10 <<endl;
        
        
        xOrigin+=  someCosValue * 10;
        yOrigin+=  someSinValue * 10;
        
        int xFinal = (xOrigin+.5);
        int yFinal = (yOrigin+.5);
        
        
        cerr<<"i propose to move to "<<xFinal<<","<<yFinal<<endl;
        
        if(xFinal < 0 || xFinal > VIEW_WIDTH -1 || yFinal < 0 || yFinal > VIEW_HEIGHT-1)
            return;
        
        
        
        //at this point the coordinate is also not block, so move
        this->moveTo(xFinal, yFinal);
        cerr<<"I jumped!"<<endl;
        cerr<<"My current position after jumping is "<<getX()<<","<<getY()<<endl;
    }
    
    // return;
    
    
}

void AdultGrasshopper:: doSomething()
{
    
    modifyHP(-1);
    // cerr<<"I am agp and my hp is "<<getHP()<<endl;
    //do i feel like biting
    
    
    if(getDoesSomething()==1){
        decrementDoesSomething();
        return;
    }
    else if (getDoesSomething() == 0){
        setDoesSomething(2);
        return;
    }
    
    decrementDoesSomething();
    
    m_willBite = rand() % 3;
    
    
    /*
     //sleep every 2 ticks
     if (getWorld()->getTicks() % 3 != 0){
     // cerr<<"I will sleep this turn"<<endl;
     
     return;
     
     }*/
    
    
    
    if (getHP()<=0){
        this->setDead();
        cerr<<"i am adult and i died :("<<endl;
        
        becomeFood();
        
        return;
    }
    
    
    
    attemptBite();
    
    int random = rand() % 10;
    if (random==0){
        
        //   cerr<<"Cos time thingy:"<<endl;
        //   cerr<<cos(time(0))<<endl;
        
        //add .5 to round up
        float pi = 3.14159;
        double someCosValue = cos(randInt(0,2*pi));
        double someSinValue = sin(randInt(0,2*pi));
        
        
        cerr<<"My origin is "<<getX()<<","<<getY()<<endl;
        int xOrigin = getX();
        int yOrigin = getY();
        
        //   cerr<<"i want to move this distance horizontally: "<< someCosValue*10 <<endl;
        //   cerr<<"i want to move this distance vertically: "<< someSinValue*10 <<endl;
        
        
        xOrigin+=  someCosValue * 10;
        yOrigin+=  someSinValue * 10;
        
        int xFinal = (xOrigin+.5);
        int yFinal = (yOrigin+.5);
        
        
        //   cerr<<"i propose to move to "<<xFinal<<","<<yFinal<<endl;
        
        if(xFinal < 0 || xFinal >= VIEW_WIDTH  || yFinal < 0 || yFinal >= VIEW_HEIGHT)
            return;
        
        
        //at this point the coordinate is within bounds
        vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(xFinal);
        for (int i = 0; i < someList.size();i++){
            
            
            if (someList[i]->getY()==yFinal && someList[i]->blocksSquare())
                return;
        }
        
        //at this point the coordinate is also not block, so move
        this->moveTo(xFinal, yFinal);
        // cerr<<"We bouncin cuhhh"<<endl;
        // cerr<<"My current position after jumping is "<<getX()<<","<<getY()<<endl;
        return;
    }
    
    //attempt a jump (naive way)
    
    
    
    //check if stepping on food
    Actor* hopefullyFood = isSteppingOnFood(getX(), getY());
    if(hopefullyFood){
        
        
        Food* fp = dynamic_cast<Food*>(hopefullyFood);
        
        if (fp != nullptr){
            
            //    cerr<<"Found a food!"<<endl;
            
            //baby grasshopper consumed all of the food
            if(fp->getHP() <= 200){
                this->modifyHP(fp->getHP());
                fp->setDead();
                cerr<<"killed all the food"<<endl;
            }
            else{
                this->modifyHP(+200);
                //    cerr<<"Food hp is "<<fp->getHP()<<endl;
                fp->modifyHP(-200);
                //cerr<<"Ow. you ate part of me!"<<endl;
                // cerr<<"Food hp is "<<fp->getHP()<<endl;
                
                //this is a number between 0 and 1
                int randNum = rand() % 2 + 1;
                if (randNum == 1){
                    // cerr<<"I choose to rest: "<<endl;
                    return;
                    
                }
                
                
            }
            
        }
        
        
    }
    
    
    int xInit = this->getX();
    int yInit = this->getY();
    
    int xFinal = xInit;
    int yFinal = yInit;
    
    GraphObject::Direction moveInThisDirection = this->getDirection();
    
    if (moveInThisDirection==GraphObject::left)
        xFinal -=1;
    else if (moveInThisDirection==GraphObject::right)
        xFinal +=1;
    else if (moveInThisDirection==GraphObject::up)
        yFinal +=1;
    else if (moveInThisDirection==GraphObject::down)
        yFinal -=1;
    
    
    Actor* ap = getWorld()->getAnActorAtTheProposedLocation(xFinal, yFinal);
    if(ap && ap->blocksSquare()){
        setWalk(0);
    }
    
    
    if (getWalk()>0){
        if (moveInThisDirection==left)
            moveTo(getX()-1, getY());
        else if (moveInThisDirection==right)
            moveTo(getX()+1,getY());
        else if (moveInThisDirection==up)
            moveTo(getX(),getY()+1);
        else if (moveInThisDirection==down)
            moveTo(getX(), getY()-1);
        
        decrementWalk();
        
        
        
    }
    else{
        setWalk(rand() % 9 + 2);
        switch (getRandomDirection()) {
            case GraphObject::left:
                this->setDirection(left);
                break;
            case GraphObject::right:
                this->setDirection(right);
                break;
            case GraphObject::up:
                this->setDirection(up);
                break;
            case GraphObject::down:
                this->setDirection(down);
                break;
            default:
                break;
        }
    }
    
    
    // cerr<<"I am...an adult!"<<endl;
}


Ant::Ant(int iid, int xInit,int yInit,Direction dInit, double imageSize, int depth, StudentWorld* ptrToWorld, long hp, int colonyNumber, Compiler* someCompiler)
:Insect(iid,xInit,yInit,dInit,imageSize,depth,ptrToWorld,hp),m_lastRandomValue(0),m_instructionsCounter(0),m_antCompiler(someCompiler),m_colonyNumber(colonyNumber)
{}

void Ant::shouldIRememberIGotBlocked(bool value)
{
    m_rememberBlocked = value;
}

void Ant::shouldIRememberSomeoneBitMe(bool value)
{
    m_rememberGotBit = value;
}

int Ant::getAmountofFoodIAmHolding() const{
    return m_amtOfFoodHolding;
}

void Ant::modifyMyCurrentFoodCount(int delta){
    m_amtOfFoodHolding += delta;
}

void Ant::setInstructionCounter(int n){
    m_instructionsCounter = n;
}

int Ant::getColonyNumber() const{
    return m_colonyNumber;
}

bool Ant::isStandingWithAnEnemy() const{
    
    //get the list of actors for given column
    vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(this->getX());
    
    for(int i = 0; i < someList.size();i++){
        
        //only consider same square actors that can move (insects)
        if(someList[i]->getY() == this->getY() && someList[i]->canMove()==true){
            
            Ant* maybeAnt = dynamic_cast<Ant*>(someList[i]);
            //see if it is an ally ant
            if(maybeAnt && maybeAnt->getColonyNumber() == this->getColonyNumber())
                continue;
            
            //otherwise  it is some insect that isnt an ally
            return true;
            
        }
    }
    return false;
    
}

bool Ant::isStandingOnMyAnthill() const{
    
    //get the list of actors for given column
    vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(this->getX());
    
    for(int i = 0; i < someList.size();i++){
        
        //only consider same square actors that cannot move, stun, bite, is poison, and has no scent
        if(someList[i]->getY() == this->getY() && !someList[i]->canMove() && !someList[i]->canStun() &&!someList[i]->canBite() && !someList[i]->isToxic() && !someList[i]->isScent() ){
            
            Anthill* maybeAnthill = dynamic_cast<Anthill*>(someList[i]);
            //see if it your anthill
            if(maybeAnthill && maybeAnthill->getColonyNumber() == this->getColonyNumber()){
                cerr<<"STEPH"<<endl;
                return true;
                
            }
        }
    }
    //at this point, nothing found
    cerr<<"not standing on my anthill since i am "<<this->getX()<<","<<this->getY()<<endl;
    return false;
    
}

bool Ant::isPheromoneInFrontOfMe() const{
    
    //first consider the direction the ant is facing
    
    GraphObject::Direction dirIAmFacing = this->getDirection();
    
    //need this later
    vector<Actor*> aCopyOfSomeCol;
    
    //left
    if(dirIAmFacing==GraphObject::left){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX()-1);
        cerr<<"Looking at stuff to my left"<<endl;
        
        
        //consider only the stuff at same Y coordinate
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY()==this->getY() && aCopyOfSomeCol[i]->isScent()){
                //check for colony number
                
                Pheromone* maybeMyPheromone = dynamic_cast<Pheromone*>(aCopyOfSomeCol[i]);
                if(maybeMyPheromone && maybeMyPheromone->getColonyNumber() == this->getColonyNumber())
                    return true;
                
            }
            
        }
        
        return false;
    }
    
    //right
    else if(dirIAmFacing==GraphObject::right){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX()+1);
        //consider only the stuff at same Y coordinate
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY()==this->getY() && aCopyOfSomeCol[i]->isScent()){
                
                //check for colony number
                Pheromone* maybeMyPheromone = dynamic_cast<Pheromone*>(aCopyOfSomeCol[i]);
                if(maybeMyPheromone && maybeMyPheromone->getColonyNumber() == this->getColonyNumber())
                    return true;
                
            }
            
        }
        
        
        return false;
    }
    
    
    //up
    else if(dirIAmFacing == GraphObject::up){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX());
        
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY() == this->getY()+1 && aCopyOfSomeCol[i]->isScent()){
                
                //check for colony number
                Pheromone* maybeMyPheromone = dynamic_cast<Pheromone*>(aCopyOfSomeCol[i]);
                if(maybeMyPheromone && maybeMyPheromone->getColonyNumber() == this->getColonyNumber())
                    return true;
                
            }
        }
    }
    
    //down
    else if(dirIAmFacing == GraphObject::down){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX());
        
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY() == this->getY()-1 && aCopyOfSomeCol[i]->isScent()){
                
                //check for colony number
                Pheromone* maybeMyPheromone = dynamic_cast<Pheromone*>(aCopyOfSomeCol[i]);
                if(maybeMyPheromone && maybeMyPheromone->getColonyNumber() == this->getColonyNumber())
                    return true;
                
            }
        }
    }
    
    //at this point didnt found your pheromone
    
    return false;
}


bool Ant::isDangerInFrontOfMe() const{
    //first consider the direction the ant is facing
    
    GraphObject::Direction dirIAmFacing = this->getDirection();
    
    //need this later
    vector<Actor*> aCopyOfSomeCol;
    
    //left
    if(dirIAmFacing==GraphObject::left){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX()-1);
        cerr<<"Looking at stuff to my left"<<endl;
        
        
        //consider only the stuff at same Y coordinate
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            
            if(aCopyOfSomeCol[i]->getY()==this->getY() && ( aCopyOfSomeCol[i]->isToxic() || aCopyOfSomeCol[i]->canMove() ) ){
                
                //check if you detected a friendly ant
                Ant* maybeFriendly = dynamic_cast<Ant*>(aCopyOfSomeCol[i]);
                if(maybeFriendly && maybeFriendly->getColonyNumber() == this->getColonyNumber())
                    continue;
                else
                    return true;
                
            }
            
        }
        
        return false;
    }
    
    //right
    else if(dirIAmFacing==GraphObject::right){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX()+1);
        //consider only the stuff at same Y coordinate
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY()==this->getY() && ( aCopyOfSomeCol[i]->isToxic() || aCopyOfSomeCol[i]->canMove() ) ){
                
                //check if you detected a friendly ant
                Ant* maybeFriendly = dynamic_cast<Ant*>(aCopyOfSomeCol[i]);
                if(maybeFriendly && maybeFriendly->getColonyNumber() == this->getColonyNumber())
                    continue;
                else
                    return true;
                
            }
            
        }
        
        
        return false;
    }
    
    
    //up
    else if(dirIAmFacing == GraphObject::up){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX());
        
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY() == this->getY()+1 && ( aCopyOfSomeCol[i]->isToxic() || aCopyOfSomeCol[i]->canMove() ) ){
                
                //check if you detected a friendly ant
                Ant* maybeFriendly = dynamic_cast<Ant*>(aCopyOfSomeCol[i]);
                if(maybeFriendly && maybeFriendly->getColonyNumber() == this->getColonyNumber())
                    continue;
                else
                    return true;
                
                
            }
        }
    }
    
    //down
    else if(dirIAmFacing == GraphObject::down){
        aCopyOfSomeCol = getWorld()->getListOfActorsInThisCol(this->getX());
        
        for (int i = 0; i < aCopyOfSomeCol.size();i++){
            if(aCopyOfSomeCol[i]->getY() == this->getY()-1 && ( aCopyOfSomeCol[i]->isToxic() || aCopyOfSomeCol[i]->canMove() ) ){
                
                //check if you detected a friendly ant
                Ant* maybeFriendly = dynamic_cast<Ant*>(aCopyOfSomeCol[i]);
                if(maybeFriendly && maybeFriendly->getColonyNumber() == this->getColonyNumber())
                    continue;
                else
                    return true;
                
                
            }
        }
    }
    
    //at this point didnt found anything dangerous
    
    return false;
}

//an ant or a grasshopper would call this
void Ant::justGotBit(){
    m_rememberGotBit = true;
}

bool Ant::hasExecutedTenCommands() const{
    
    return m_instructionsCounter >= 10;
}

void Ant::interpreter(){
    
    
    Compiler::Command cmd;
    
    int realCounter = 0;
    
    
    for (;;){
        
        if ( ! m_antCompiler->getCommand(m_instructionsCounter, cmd)){
            this->setDead();
            cerr<<"Not listening!"<<endl;
            return;
        }
        
        
        
        if (cmd.opcode == Compiler::moveForward){
            cerr<<"Moving forward"<<endl;
            
            
            //check  if got blocked
            int xInit = this->getX();
            int yInit = this->getY();
            
            int xFinal = xInit;
            int yFinal = yInit;
            
            GraphObject::Direction moveInThisDirection = this->getDirection();
            
            if (moveInThisDirection==GraphObject::left)
                xFinal -=1;
            else if (moveInThisDirection==GraphObject::right)
                xFinal +=1;
            else if (moveInThisDirection==GraphObject::up)
                yFinal +=1;
            else if (moveInThisDirection==GraphObject::down)
                yFinal -=1;
            
            
            Actor* ap = getWorld()->getAnActorAtTheProposedLocation(xFinal, yFinal);
            if(ap && ap->blocksSquare()){
                shouldIRememberIGotBlocked(true);
                // cerr<<"Got blocked man at "<<xFinal<<","<<yFinal<<endl;
            }
            else{
                //tell ant to remember it didnt get blocked
                shouldIRememberIGotBlocked(false);
                
                if (moveInThisDirection==left)
                    moveTo(getX()-1, getY());
                else if (moveInThisDirection==right)
                    moveTo(getX()+1,getY());
                else if (moveInThisDirection==up)
                    moveTo(getX(),getY()+1);
                else if (moveInThisDirection==down)
                    moveTo(getX(), getY()-1);
                
                //Remember that it was not bit while on its current square(since it’s now on a new square, it hasn’t been bitten there yet, by definition).
                shouldIRememberSomeoneBitMe(false);
                // cerr<<"Remembering i did not get bit"<<endl;
                
                
                
                //then check if step in water or poison
                checkIfSteppedOnWaterOrPoison();
            }
            ++m_instructionsCounter;
            cerr<<"After moving forward, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            // if(hasExecutedTenCommands())
            //    return;
            
            
            
            realCounter++;
            if(realCounter>10)
                return;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
        }
        
        else if (cmd.opcode == Compiler::eatFood){
            //first check if you got 100 or more food to eat
            if(getAmountofFoodIAmHolding()>=100){
                modifyHP(100);
                modifyMyCurrentFoodCount(-100);
                cerr<<"Eating my own stash of food for 100!"<<endl;
            }
            
            //then check if eating food would run out your resources
            else if(getAmountofFoodIAmHolding()>0){
                cerr<<"Going to eat "<<getAmountofFoodIAmHolding()<<endl;
                modifyHP(getAmountofFoodIAmHolding());
                modifyMyCurrentFoodCount(-getAmountofFoodIAmHolding()); //careful for (-)
                cerr<<"Eating my last bite..."<<endl;
            }
            
            //at this point it never had food
            ++m_instructionsCounter;
            cerr<<"After eating food, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            // if(hasExecutedTenCommands())
            //   return;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        else if (cmd.opcode == Compiler::dropFood){
            
            cerr<<"current food count before drop: "<<getAmountofFoodIAmHolding()<<endl;
            //if it has no food, use up an instruction and counter
            
            if(getAmountofFoodIAmHolding()<=0){
                m_instructionsCounter++;
                realCounter++;
                
                if(realCounter>=10)
                    return;
                else
                    continue;
            }
            
            //maybe dropped on anthill
            //get the list of actors for given column
            vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(this->getX());
            
            for(int i = 0; i < someList.size();i++){
                
                //only consider same square actors that cannot move, stun, bite, is poison, and has no scent
                if(someList[i]->getY() == this->getY() && !someList[i]->canMove() && !someList[i]->canStun() &&!someList[i]->canBite() && !someList[i]->isToxic() && !someList[i]->isScent() ){
                    
                    Anthill* maybeAnthill = dynamic_cast<Anthill*>(someList[i]);
                    //see if it is an enemy ant
                    if(maybeAnthill && maybeAnthill->getColonyNumber() == this->getColonyNumber()){
                        getWorld()->createFood(getX(), getY(), this->getAmountofFoodIAmHolding());
                        this->modifyMyCurrentFoodCount(-getAmountofFoodIAmHolding());
                        //cerr<<"Dropped food and seeing if i can make ants"<<endl;
                        maybeAnthill->seeIfICanMakeAnts();
                        //  return;
                    }
                    
                }
            }
            
            //now see if dropped food on food
            Actor* maybeFoodPtr = this->isSteppingOnFood(getX(), getY());
            if (maybeFoodPtr){
                Food* iAmFood = dynamic_cast<Food*>(maybeFoodPtr);
                
                //food heals as much as ant holds
                iAmFood->modifyHP(this->getAmountofFoodIAmHolding());
                
                //this zeroes out all that it holds
                this->modifyMyCurrentFoodCount(-getAmountofFoodIAmHolding());
            }
            
            //then the ant was not stepping on food, so make food!
            else{
                getWorld()->createFood(getX(), getY(), getAmountofFoodIAmHolding());
                this->modifyMyCurrentFoodCount(-getAmountofFoodIAmHolding());
            }
            
            cerr<<"Dropped food"<<endl;
            cerr<<"now i have: "<<getAmountofFoodIAmHolding()<<endl;
            ++m_instructionsCounter;
            cerr<<"After dropping food, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        else if (cmd.opcode == Compiler::faceRandomDirection){
            cerr<<"Currently facing this direction: "<<this->getDirection();
            this->setDirection(getRandomDirection());
            cerr<<"now facing this direction: "<<this->getDirection();
            ++m_instructionsCounter;
            cerr<<"m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        
        
        else if(cmd.opcode == Compiler::goto_command){
            m_instructionsCounter = stoi(cmd.operand1);
        }
        
        else if(cmd.opcode == Compiler::bite){
            
            
            vector<Actor*> someList = getWorld()->getListOfActorsInThisCol(getX());
            
            //then try to push back only the insects(those that can move
            vector<Actor*> potentialVictims;
            
            
            for (int i = 0; i < someList.size();i++){
                if (someList[i]->canMove()){
                    
                    
                    //then check if it is ant of the same colony
                    Ant* maybeTheSameColony = dynamic_cast<Ant*>(someList[i]);
                    if(maybeTheSameColony && maybeTheSameColony->getColonyNumber() == this->getColonyNumber()){
                        cerr<<"Yo chill. we the same color"<<endl;
                        continue;
                        
                    }
                    //otherwise add on
                    potentialVictims.push_back(someList[i]);
                    //cerr<<"Added this guy into my victim list "<<someList[i]->getID()<<endl;;
                }
            }//end of adding all the list
            
            
            if(potentialVictims.empty()){
                ++m_instructionsCounter;
                cerr<<"After biting, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
                
                //  if(hasExecutedTenCommands())
                //  return;
                realCounter++;
                if(realCounter>10)
                    return;
            }
            
            
            int randomIndex = rand() % potentialVictims.size();
            Insect* someBitInsect = dynamic_cast<Insect*>(potentialVictims[randomIndex]);
            if(someBitInsect){
                cerr<<"My hp before i got bit by an ant: "<<someBitInsect->getHP()<<endl;
                someBitInsect->modifyHP(-15);
                cerr<<"My hp after being bit: "<<someBitInsect->getHP()<<endl;
                
                //check if wat you bit was an Ant
                Ant* maybeAnEnemyAnt = dynamic_cast<Ant*>(someBitInsect);
                if(maybeAnEnemyAnt)
                    maybeAnEnemyAnt->justGotBit();
            }
            
            ++m_instructionsCounter;
            cerr<<"After biting, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        
        else if (cmd.opcode == Compiler::pickupFood){
            
            cerr<<"Picking up food was called"<<endl;
            
            //first see if ant is already holding max 1800 units of food
            if(getAmountofFoodIAmHolding() == 1800){
                m_instructionsCounter++;
                
                cerr<<"Holding my max already!"<<endl;
                //return;
                realCounter++;
                if(realCounter>10)
                    return;
            }
            
            //then see if it is even stepping on food
            Actor* maybeOnFood = isSteppingOnFood(getX(), getY());
            if (maybeOnFood){
                Food* itIsFood = dynamic_cast<Food*>(maybeOnFood);
                
                //see if the food can survive a bite
                if(itIsFood->getHP()>400){
                    modifyMyCurrentFoodCount(+400);
                    itIsFood->modifyHP(-400);
                    
                    //just in case eating overboard
                    if(getAmountofFoodIAmHolding()>1800){
                        itIsFood->modifyHP(-(getAmountofFoodIAmHolding()-1800));
                        m_amtOfFoodHolding = 1800;
                    }
                    
                    
                    
                }
                else{
                    //all the food was eaten
                    modifyMyCurrentFoodCount(itIsFood->getHP()); //eh, integer precision loss is fine
                    itIsFood->modifyHP(-(itIsFood->getHP()));
                    //just in case eating overboard
                    if(getAmountofFoodIAmHolding()>1800){
                        m_amtOfFoodHolding = 1800;
                    }
                    
                    if(itIsFood->getHP()<=0)
                        itIsFood->setDead();
                }
                
                
                
                
            }
            ++m_instructionsCounter;
            cerr<<"After picking up food, m_instructionCounter is now "<<m_instructionsCounter<<endl;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        //THE CURIOUS CASE WHEN OPERAND1 = 0
        else if (cmd.opcode == Compiler::generateRandomNumber){
            
            //check if operand1 is 0
            if(stoi(cmd.operand1) == 0){
                m_lastRandomValue = 0;
                cerr<<"since operand1 is 0...m_lastval is..."<<m_lastRandomValue<<endl;
            }
            
            else{
                m_lastRandomValue = randInt(0, stoi(cmd.operand1));
                cerr<<"Random value is "<<m_lastRandomValue<<endl;
            }
            
            ++m_instructionsCounter;
            cerr<<"After generating random number, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            //if(hasExecutedTenCommands()){
            //    setInstructionCounter(0);
            //    return;
            //}
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        
        
        else if (cmd.opcode == Compiler::emitPheromone){
            getWorld()->createPheromone(this->getColonyNumber(), this->getX(), this->getY());
            cerr<<"Emitting a pheromone!"<<endl;
            
            //see if already stepping on a pheromone
            
            
            ++m_instructionsCounter;
            cerr<<"After dropping a pheromone, m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            //if(hasExecutedTenCommands())
            //    return;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
        }
        
        
        else if (cmd.opcode == Compiler ::rotateClockwise){
            GraphObject::Direction curDirection = getDirection();
            
            if(curDirection == GraphObject::left)
                setDirection(GraphObject::up);
            else if (curDirection == GraphObject::up)
                setDirection(GraphObject::right);
            else if (curDirection == GraphObject::right)
                setDirection(GraphObject::down);
            else if (curDirection == GraphObject::down)
                setDirection(GraphObject::left);
            
            ++m_instructionsCounter;
            cerr<<"After rotating clockwise m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            //if(hasExecutedTenCommands())
            //    return;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
            
            
        }
        
        
        
        else if (cmd.opcode == Compiler ::rotateCounterClockwise){
            GraphObject::Direction curDirection = getDirection();
            
            if(curDirection == GraphObject::left)
                setDirection(GraphObject::down);
            else if (curDirection == GraphObject::down)
                setDirection(GraphObject::right);
            else if (curDirection == GraphObject::right)
                setDirection(GraphObject::up);
            else if (curDirection == GraphObject::up)
                setDirection(GraphObject::left);
            
            ++m_instructionsCounter;
            cerr<<"After rotating counter clockwise m_instructionsCounter is now "<<m_instructionsCounter<<endl;
            
            //if(hasExecutedTenCommands())
            //    return;
            
            return; //if the command is anything other than goto, if, or generateRandomNumber, then the ant's doSomething must immediately return
            
            realCounter++;
            if(realCounter>10)
                return;
            
            
        }
        
        
        //THE IF COMMAND
        else if (cmd.opcode == Compiler::if_command){
            switch (stoi(cmd.operand1)) {
                case Compiler::last_random_number_was_zero:
                    if(m_lastRandomValue == 0){
                        cerr<<"Yeah my last random value was 0"<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"LIKE counter is now: "<<m_instructionsCounter<<endl;
                        
                        
                        // return; //so as to let instruction counter go to that line
                    }
                    else{
                        ++m_instructionsCounter;
                        cerr<<"if last_random_number_was_zero failed"<<endl;
                        //if(hasExecutedTenCommands())
                        //return;
                        
                    }
                    
                    break;
                    
                    
                case Compiler::i_am_carrying_food:
                    if(this->getAmountofFoodIAmHolding() > 0){
                        cerr<<"Yeah i got food"<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"after carrying food, instruction counter is now: "<<m_instructionsCounter<<endl;
                        
                        
                        // return; //so as to let instruction counter go to that line
                    }
                    else{
                        ++m_instructionsCounter;
                        //cerr<<"if i_am_carrying_food failed"<<endl;
                        //if(hasExecutedTenCommands())
                        //    return;
                        
                    }
                    break;
                    
                    
                case Compiler::i_am_hungry:
                    if(this->getHP()<=25 ){
                        cerr<<"Yeah im hungry food"<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"after carrying food, instruction counter is now: "<<m_instructionsCounter<<endl;
                        
                        
                        // return; //so as to let instruction counter go to that line
                    }
                    else{
                        ++m_instructionsCounter;
                        cerr<<"i_am_hungry failed"<<endl;
                        //if(hasExecutedTenCommands())
                        //  return;
                        
                    }
                    break;
                    
                    
                case Compiler::i_am_standing_with_an_enemy:
                    if (isStandingWithAnEnemy()){
                        cerr<<"Yeah im standing with an enemy"<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After standing with an enemy, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        // return;
                    }
                    else{
                        ++m_instructionsCounter;
                        cerr<<"standing_with_an_enemy failed"<<endl;
                        // if(hasExecutedTenCommands())
                        //    return;
                        
                    }
                    break;
                    
                    
                case Compiler::i_am_standing_on_food:
                    
                    //NOTE: THIS RETURNS AN Actor*, BUT THIS RETURNS FALSE IF Actor* = nullptr
                    if(isSteppingOnFood(this->getX(), this->getY())){
                        cerr<<"Yeah standing on food"<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After standing with an enemy, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        // return;
                        
                    }
                    else{
                        ++m_instructionsCounter;
                        cerr<<"if i_am_standing_on_food failed"<<endl;
                        //if(hasExecutedTenCommands())
                        // return;
                        
                    }
                    
                    break;
                    
                    
                case Compiler::i_am_standing_on_my_anthill:
                    if(isStandingOnMyAnthill()){
                        cerr<<"Yeah standing on my anthill"<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After standing on my anthill, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        // return;
                    }
                    else{
                        ++m_instructionsCounter;
                        cerr<<"if standing_on_my_anthill failed"<<endl;
                        //if(hasExecutedTenCommands())
                        //return;
                        
                    }
                    
                    break;
                    
                    
                case Compiler::i_smell_pheromone_in_front_of_me:
                    if(isPheromoneInFrontOfMe()){
                        cerr<<"Yeah my pheromone in front of me "<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After smelling my pheromone, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        // return;
                    }
                    else{
                        ++m_instructionsCounter;
                        cerr<<"if smell_pheromone_in_front_of_me failed"<<endl;
                        //if(hasExecutedTenCommands())
                        //  return;
                        
                    }
                    
                    break;
                    
                    
                case Compiler::i_smell_danger_in_front_of_me:
                    if(isDangerInFrontOfMe()){
                        cerr<<"something dangerous lies ahead of me "<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After detecting danger, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        // return;
                    }
                    else
                        ++m_instructionsCounter;
                    cerr<<"if smell_danger_in_front_of_me failed"<<endl;
                    //if(hasExecutedTenCommands())
                    //return;
                    
                    break;
                    
                case Compiler::i_was_bit:
                    if(m_rememberGotBit){
                        cerr<<"i remember being bitten here "<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After remembering i got bit, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        //  return;
                    }
                    ++m_instructionsCounter;
                    cerr<<"if i_was_bit failed"<<endl;
                    // if(hasExecutedTenCommands())
                    //  return;
                    
                    
                    break;
                    
                    
                case Compiler::i_was_blocked_from_moving:
                    if(m_rememberBlocked){
                        cerr<<"i remember being blocked here at "<<getX()<<","<<getY()<<endl;
                        m_instructionsCounter = stoi(cmd.operand2);
                        cerr<<"After remembering i got blocked, instruction counter is now "<<m_instructionsCounter<<endl;
                        
                        //  return;
                    }
                    ++m_instructionsCounter;
                    cerr<<"if i_was_blocked_from_moving failed"<<endl;
                    //if(hasExecutedTenCommands())
                    //return;
                    
                    
                    break;
                    
                default:
                    break;
                    
                    
            }
            
            // m_instructionsCounter++; DID THIS COST EVERYTHING?
        }
        
        
        else{
            cerr<<"Hey im listening but not a valid command bro"<<endl;
            return;
        }
        
        
        
    }//end of for loop
    
    
}



void Ant::doSomething(){
    
    //cerr<<"Ant, PLEASE TELL ME YOUR POINTER POINTS TO THE SAME THING: "<<&*m_antCompiler<<endl;
    //cerr<<"I am an ant!"<<endl;
    
    modifyHP(-1);
    
    if (getHP()<=0){
        this->setDead();
        cerr<<"im an ant and i died :("<<endl;
        //we dont care about updating the count of ants since winner is determined by new ants produced only
        becomeFood();
        return;
    }
    
    
    if (isStunned()){
        //  cerr<<"I am stunned!"<<endl;
        decrementStunTick();
        cerr<<"My stun tick count is.."<<getStunTicks()<<endl;
        return;
    }
    //oh man this line looks so innocent...
    interpreter();
    
    
}
