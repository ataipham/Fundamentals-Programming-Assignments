/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
 class MovingObject;
 class Position;
 class Configuration;
 class Map;

 class Criminal;
 class RobotS;
 class RobotW;
 class RobotSW;
 class RobotC;

 class ArrayMovingObject;
 class StudyPinkProgram;

 class BaseItem;
 class BaseBag;
 class SherlockBag;
 class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C = 0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type) {
        type = in_type;
    }
    virtual ~MapElement(){}
    virtual ElementType getType() const {
        return type;
    }
};

class Path : public MapElement {
    public:
    Path() :MapElement(PATH){}
};

class Wall : public MapElement {
    public:
    Wall() :MapElement(WALL){}
};

class FakeWall : public MapElement {
private:
    int req_exp;
public:
    FakeWall(int in_req_exp) :MapElement(FAKE_WALL) {
        this->req_exp = in_req_exp;      
    }
    int getReqExp() const;
};

class Map {
private:
    int num_rows, num_cols;
    MapElement*** map;
public:
    Map (int num_rows , int num_cols , int num_walls , Position * array_walls , int num_fake_walls , Position * array_fake_walls );
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const;
    int getNumRows() const;
    int getNumCols() const;
};

class Position {
private:
    int r, c;
public:
    static const Position npos;
    Position(int r = 0, int c = 0);
    Position(const string& str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
    bool isEqual(int in_r, int in_c) const;
    bool isEqual(const Position& pos) const;
};

// const Position Position::npos(-1, -1);

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map* map, const string& name ="");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual string getName() =0 ;
};

class Character : public MovingObject {
    protected:
    int hp, exp;
    string name;
    string moving_rule;
public:
    Character(int index, const Position &init_pos, Map *map, const string &name);
    ~Character(){}
   virtual string getName();
   virtual int getHP() const;
   virtual int getEXP() const;
   virtual void setHP(int HP);
   virtual void setEXP(int EXP);
   virtual int getRow() const;
   virtual int getCol() const;
};

 class Sherlock : public Character {
private:
    int i;
public:
    Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp);
    Position getNextPosition();
    Position getCurrentPosition();

    void move();
    string str() const;

//    int getR_Sherlock();
//    int getC_Sherlock();
//    int getHP();
//    int getEXP();
//    string getName();
//    void setHP(int HP);
//   void setEXP(int EXP);
};

class Watson : public Character {
private:
    int i=0;
public:
    Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp);
    Position getNextPosition();
    Position getCurrentPosition();
    void move();
    string str() const;
//  int getR_Wats();
//    int getC_Wats();
//    int getHP();
//    int getEXP();
//    string getName();
//    void setHP(int HP);
//    void setEXP(int EXP);
};

class Criminal : public Character {
private:
    Sherlock* sherlock;
    Watson* watson;
    ArrayMovingObject* moving_obj;
    Position previousposition;
    int steps;
    int robotsCreated;

public:
    Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson);
    long long distance_to_sher(int crim_row, int crim_col);
    long long distance_to_wats(int crim_row, int crim_col);
    bool moved = false;
    // U=0 , L=1, D=2, R=3
    Position calculateNextPos(Position current, int direction);
    long long ManhattanDistance(Position current);
    Position getCurrentPosition();
    Position getPreviousPosition();
    Position getNextPosition();
    void createRobot();
    void move();
    string str() const;
    int getSteps() const;

};

class ArrayMovingObject {
private:
    int count, capacity;
    MovingObject** arr_mv_objs;

public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject* mv_obj);
    MovingObject* get(int index) const;
    string str() const;
    int getCount() const;
    int getCapacity() const;
    int size() const;
};

 class Configuration {
    friend class StudyPinkProgram;

 private:
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int  num_walls, num_fake_walls;
    Position* arr_walls;
    Position* arr_fake_walls;
    int sherlock_init_hp, sherlock_init_exp;
    string sherlock_moving_rule, watson_moving_rule;
    Position watson_init_pos;
    Position criminal_init_pos;
    Position sherlock_init_pos;
    int watson_init_hp, watson_init_exp, num_steps;

 public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;

 }; 

class Robot : public MovingObject {
    protected:
    Criminal* criminal;
    RobotType robot_type;
    BaseItem * item;
    public:
    Robot(int index, const Position& init_pos, Map* map, Criminal* criminal, RobotType robot_type);
    virtual ~Robot();
    void initializeItem(int i, int j);
    virtual Position getNextPosition() = 0;
    virtual void move() =0;
 //   virtual Position getCurrentPosition();
    string str() const;
    virtual RobotType getRobotType() const;
    virtual BaseItem *getItem() const;
};
class RobotC : public Robot {
    public:
    RobotC ( int index , const Position& init_pos , Map * map , Criminal * criminal );
    ~RobotC(){}
    Position getNextPosition();
    long long distancetoSher(Sherlock* sher) const;
    long long distancetoWats(Watson* wats) const;
    long long getDistance(Sherlock* sher) const;
    long long getDistance(Watson* wats) const;
    void move();
    string str();
    string getName();
};

class RobotS : public Robot{
    private:
    Sherlock * sherlock;
    public:
    RobotS ( int index , const Position & init_pos , Map * map , Criminal *criminal , Sherlock * sherlock ) ;
    ~RobotS(){}
    Position getNextPosition();
    long long distancetoSherlock(int Robotrow, int Robotcol);
    Position getCurrentPosition();
    long long getDistance();
    void move();
    string str();
    string getName();
};

class RobotW : public Robot {
    private:
    Watson* watson;
    public:
    RobotW ( int index , const Position & init_pos , Map * map , Criminal *criminal , Watson * watson ) ;
    ~RobotW(){}
    Position getNextPosition();
    long long distancetoWatson(int Robotrow, int Robotcol);
    void move();
    long long getDistance();
    string str();
    string getName();
};

class RobotSW : public Robot {
    private:
    Sherlock* sherlock;
    Watson* watson;
    public:
    RobotSW ( int index , const Position & init_pos , Map * map , Criminal *criminal , Sherlock * sherlock , Watson * watson ) ;
    ~RobotSW() = default;
    Position getNextPosition();
    long long distancetoWats(int Robotrow, int Robotcol);
    long long distancetoSher(int Robotrow, int Robotcol);
    void move();
    long long getDistance();
    string str();
    string getName();
};

class BaseItem {
    public:
    ItemType item_type;
    BaseItem* next;
    ItemType getItemType();
    BaseItem(ItemType item_type);
    virtual bool canUse(Character* obj, Robot * robot) = 0;
    virtual void use(Character* obj, Robot * robot) = 0;
    string getItemName();
};

class MagicBook : public BaseItem{
    public:
    MagicBook() : BaseItem(MAGIC_BOOK){
        this->item_type = MAGIC_BOOK;
    }
    bool canUse(Character* obj, Robot * robot);
    void use(Character* obj, Robot * robot);
};

class EnergyDrink : public BaseItem{
    public:
    EnergyDrink() : BaseItem(ENERGY_DRINK){
        this->item_type = ENERGY_DRINK;
    }
    bool canUse(Character* obj, Robot * robot);
    void use(Character* obj, Robot * robot);
};
class FirstAid : public BaseItem{
    public:
    FirstAid() : BaseItem(FIRST_AID){
        this->item_type = FIRST_AID;
    }
    bool canUse(Character* obj, Robot * robot);
    void use(Character* obj, Robot * robot);
};
class ExcemptionCard : public BaseItem{
    public:
    ExcemptionCard() : BaseItem(EXCEMPTION_CARD){
        this->item_type = EXCEMPTION_CARD;
    }
    bool canUse(Character* obj, Robot * robot);
    void use(Character* obj, Robot * robot);
};
class PassingCard : public BaseItem{
    public:
    PassingCard() : BaseItem(PASSING_CARD){
        this->item_type = PASSING_CARD;
    }
    
    PassingCard(string challenge) : BaseItem(PASSING_CARD){
        this->challenge = challenge;
    }

    bool canUse(Character* obj, Robot * robot);
    void use(Character* obj, Robot * robot);
    string RobotTypeToString(RobotType robot_type);
    string challenge = "";
    string getChallenge() const;
};

class BaseBag{
    public:
    BaseItem* head;
    Character* obj;
    int count;
    int capacity;
    BaseBag(Character* obj, int capacity);
    ~BaseBag();
    virtual bool insert(BaseItem* newItem);
    virtual BaseItem* get();
    virtual BaseItem* get(ItemType itemType);
    virtual string str() const;
    string listname() const;
    int getCount() const;
    int getCapacity() const;
};
class SherlockBag : public BaseBag{
    public:
    SherlockBag(Sherlock* sher);
};

class WatsonBag : public BaseBag{
    public:
    WatsonBag(Watson* wats);
};


 class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;

    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    Robot *robot;
    BaseItem * item;
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);
    mutable bool caught = false;
    bool isStop() const;
    void checkEncounterOfSherlock(Sherlock* sherlock, SherlockBag& sherbag, WatsonBag& watsbag);
    void SherlockHandleRobot(Sherlock* sherlock, Robot* robot, SherlockBag& sherbag);
    void checkEncounterOfWatson(Watson* watson, SherlockBag& sherbag, WatsonBag& watsbag);
    void WatsonHandleRobot(Watson* watson, Robot* robot, WatsonBag& watsbag);
    void checkEncounterOfRobot(Robot* robot, SherlockBag& sherbag, WatsonBag& watsbag);
    void restoreHPandEXP(Character *character, SherlockBag& sherbag);
    void restoreHPandEXP(Character *character, WatsonBag& watsbag);
    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        
        SherlockBag sherbag(sherlock);
        WatsonBag watsbag(watson);
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                MovingObject* obj = arr_mv_objs->get(i);
                if (obj == sherlock){
                    checkEncounterOfSherlock(sherlock, sherbag, watsbag);
                }
                else if (obj == watson) {
                    checkEncounterOfWatson(watson, sherbag, watsbag);
                }
                else if (obj != sherlock && obj != watson && obj != criminal) {
                    Robot* robot = dynamic_cast<Robot*>(obj);
                    if(robot) checkEncounterOfRobot(robot, sherbag, watsbag);
                }
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if(criminal->getSteps() % 3 == 0) {
                    criminal->createRobot();
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }


    ~StudyPinkProgram();
}; 

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
