/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
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

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};

/**
 * @class MapElement
 * Base class for all map elements (Path, Wall, FakeWall)
 */
class MapElement
{
protected:
    ElementType type;

public:
    /**
     * Constructor for MapElement
     * @param in_type The type of the map element (PATH, WALL, or FAKE_WALL)
     */
    MapElement(ElementType in_type)
    {
        type = in_type;
    }
    virtual ~MapElement() {}

    /**
     * Get the type of the map element
     * @return ElementType The type of this element
     */
    virtual ElementType getType() const
    {
        return type;
    }
};

/**
 * @class Path
 * Represents a walkable path on the map
 */
class Path : public MapElement
{
public:
    /**
     * Constructor for Path element
     */
    Path() : MapElement(PATH) {}
};

/**
 * @class Wall
 * Represents an impassable wall on the map
 */
class Wall : public MapElement
{
public:
    /**
     * Constructor for Wall element
     */
    Wall() : MapElement(WALL) {}
};

/**
 * @class FakeWall
 * Represents a fake wall that can be passed through if character has enough EXP
 */
class FakeWall : public MapElement
{
private:
    int req_exp;

public:
    /**
     * Constructor for FakeWall element
     * @param in_req_exp The required experience to pass through this wall
     */
    FakeWall(int in_req_exp) : MapElement(FAKE_WALL)
    {
        this->req_exp = in_req_exp;
    }

    /**
     * Get the required experience to pass through this fake wall
     * @return int The required EXP value
     */
    int getReqExp() const;
};

/**
 * @class Map
 * Represents the game map containing all map elements
 */
class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    /**
     * Constructor for Map
     * @param num_rows Number of rows in the map
     * @param num_cols Number of columns in the map
     * @param num_walls Number of wall positions
     * @param array_walls Array of wall positions
     * @param num_fake_walls Number of fake wall positions
     * @param array_fake_walls Array of fake wall positions
     */
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);

    /**
     * Destructor for Map, deallocates all map elements
     */
    ~Map();

    /**
     * Check if a position is valid for a moving object
     * @param pos The position to validate
     * @param mv_obj The moving object attempting to move
     * @return bool True if position is valid and accessible
     */
    bool isValid(const Position &pos, MovingObject *mv_obj) const;

    /**
     * Get the number of rows in the map
     * @return int Number of rows
     */
    int getNumRows() const;

    /**
     * Get the number of columns in the map
     * @return int Number of columns
     */
    int getNumCols() const;
};

/**
 * @class Position
 * Represents a position on the map with row and column coordinates
 */
class Position
{
private:
    int r, c;

public:
    /** Static constant representing an invalid position (-1, -1) */
    static const Position npos;

    /**
     * Constructor with row and column values
     * @param r Row coordinate (default: 0)
     * @param c Column coordinate (default: 0)
     */
    Position(int r = 0, int c = 0);

    /**
     * Constructor that parses position from string format "(r,c)"
     * @param str_pos String in format "(row,col)"
     */
    Position(const string &str_pos);

    /**
     * Get the row coordinate
     * @return int Row value
     */
    int getRow() const;

    /**
     * Get the column coordinate
     * @return int Column value
     */
    int getCol() const;

    /**
     * Set the row coordinate
     * @param r New row value
     */
    void setRow(int r);

    /**
     * Set the column coordinate
     * @param c New column value
     */
    void setCol(int c);

    /**
     * Convert position to string format
     * @return string Position in format "(row,col)"
     */
    string str() const;

    /**
     * Check if position equals given coordinates
     * @param in_r Row to compare
     * @param in_c Column to compare
     * @return bool True if positions match
     */
    bool isEqual(int in_r, int in_c) const;

    /**
     * Check if position equals another Position object
     * @param pos Position to compare
     * @return bool True if positions match
     */
    bool isEqual(const Position &pos) const;
};

// const Position Position::npos(-1, -1);

/**
 * @class MovingObject
 * Abstract base class for all objects that can move on the map
 */
class MovingObject
{
protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    /**
     * Constructor for MovingObject
     * @param index Unique identifier for the object
     * @param pos Initial position on the map
     * @param map Pointer to the game map
     * @param name Name of the object (optional)
     */
    MovingObject(int index, const Position pos, Map *map, const string &name = "");

    /**
     * Virtual destructor for proper cleanup
     */
    virtual ~MovingObject();

    /**
     * Calculate the next position based on movement rules (pure virtual)
     * @return Position Next position or Position::npos if invalid
     */
    virtual Position getNextPosition() = 0;

    /**
     * Get the current position of the object
     * @return Position Current position
     */
    Position getCurrentPosition() const;

    /**
     * Execute movement to the next position (pure virtual)
     */
    virtual void move() = 0;

    /**
     * Get string representation of the object (pure virtual)
     * @return string Object details as string
     */
    virtual string str() const = 0;

    /**
     * Get the name of the object (pure virtual)
     * @return string Object name
     */
    virtual string getName() = 0;
};

/**
 * @class Character
 * Abstract base class for game characters (Sherlock, Watson, Criminal)
 */
class Character : public MovingObject
{
protected:
    int hp, exp;
    string moving_rule;

public:
    /**
     * Constructor for Character
     * @param index Character index
     * @param init_pos Starting position
     * @param map Pointer to the game map
     * @param name Character name
     */
    Character(int index, const Position &init_pos, Map *map, const string &name);

    /**
     * Destructor for Character
     */
    ~Character() {}

    /**
     * Get the character's name
     * @return string Character name
     */
    virtual string getName();

    /**
     * Get the character's HP (Health Points)
     * @return int Current HP value
     */
    virtual int getHP() const;

    /**
     * Get the character's EXP (Experience Points)
     * @return int Current EXP value
     */
    virtual int getEXP() const;

    /**
     * Set the character's HP
     * @param HP New HP value
     */
    virtual void setHP(int HP);

    /**
     * Set the character's EXP
     * @param EXP New EXP value
     */
    virtual void setEXP(int EXP);

    /**
     * Get the row of character's current position
     * @return int Row coordinate
     */
    virtual int getRow() const;

    /**
     * Get the column of character's current position
     * @return int Column coordinate
     */
    virtual int getCol() const;
};

/**
 * @class Sherlock
 * Represents the detective Sherlock Holmes character
 */
class Sherlock : public Character
{
private:
    int i; /**< Index for cycling through moving_rule */

public:
    /**
     * Constructor for Sherlock
     * @param index Sherlock's index
     * @param moving_rule String of movement directions (e.g., "RUU")
     * @param init_pos Starting position
     * @param map Pointer to the game map
     * @param init_hp Initial HP (capped at 500)
     * @param init_exp Initial EXP (capped at 900)
     */
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);

    /**
     * Calculate next position based on moving_rule
     * @return Position Next position or Position::npos if invalid
     */
    Position getNextPosition();

    /**
     * Move Sherlock to the next valid position
     * @note Does not move if HP <= 0 or EXP <= 0
     */
    void move();

    /**
     * Get string representation of Sherlock
     * @return string Format: "Sherlock[index=X;pos=(r,c);moving_rule=XXX]"
     */
    string str() const;
};

/**
 * @class Watson
 * Represents the character Dr. John Watson
 */
class Watson : public Character
{
private:
    int i = 0; /**< Index for cycling through moving_rule */

public:
    /**
     * Constructor for Watson
     * @param index Watson's index
     * @param moving_rule String of movement directions (e.g., "LU")
     * @param init_pos Starting position
     * @param map Pointer to the game map
     * @param init_hp Initial HP (capped at 500)
     * @param init_exp Initial EXP (capped at 900)
     */
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);

    /**
     * Calculate next position based on moving_rule
     * @return Position Next position or Position::npos if invalid
     */
    Position getNextPosition();

    /**
     * Move Watson to the next valid position
     * @note Does not move if HP <= 0 or EXP <= 0
     */
    void move();

    /**
     * Get string representation of Watson
     * @return string Format: "Watson[index=X;pos=(r,c);moving_rule=XXX]"
     */
    string str() const;
};

/**
 * @class Criminal
 * Represents the criminal that Sherlock and Watson are chasing
 */
class Criminal : public Character
{
private:
    Sherlock *sherlock;
    Watson *watson;
    ArrayMovingObject *moving_obj;
    Position previousposition;
    int steps;
    int robotsCreated;

public:
    /**
     * Constructor for Criminal
     * @param index Criminal's index
     * @param init_pos Starting position
     * @param map Pointer to the game map
     * @param sherlock Pointer to Sherlock for distance calculation
     * @param watson Pointer to Watson for distance calculation
     */
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);

    /**
     * Calculate Manhattan distance from a position to Sherlock
     * @param crim_row Row coordinate
     * @param crim_col Column coordinate
     * @return long long Manhattan distance to Sherlock
     */
    long long distance_to_sher(int crim_row, int crim_col);

    /**
     * Calculate Manhattan distance from a position to Watson
     * @param crim_row Row coordinate
     * @param crim_col Column coordinate
     * @return long long Manhattan distance to Watson
     */
    long long distance_to_wats(int crim_row, int crim_col);

    bool moved = false; /**< Flag indicating if criminal has moved */

    /**
     * Calculate next position in a given direction
     * @param current Current position
     * @param direction Direction (0=Up, 1=Left, 2=Down, 3=Right)
     * @return Position New position if valid, current position otherwise
     */
    Position calculateNextPos(Position current, int direction);

    /**
     * Calculate total Manhattan distance to both Sherlock and Watson
     * @param current Position to calculate from
     * @return long long Sum of distances to both characters
     */
    long long ManhattanDistance(Position current);

    /**
     * Get Criminal's previous position (for robot spawning)
     * @return Position Previous position
     */
    Position getPreviousPosition();

    /**
     * Find optimal next position to maximize distance from pursuers
     * @return Position Best next position or Position::npos
     */
    Position getNextPosition();

    /**
     * Create a robot at Criminal's previous position
     * @note First robot is RobotC, subsequent based on distance comparison
     */
    void createRobot();

    /**
     * Move Criminal to next position and increment step counter
     */
    void move();

    /**
     * Get string representation of Criminal
     * @return string Format: "Criminal[index=X;pos=(r,c)]"
     */
    string str() const;

    /**
     * Get number of steps Criminal has taken
     * @return int Step count
     */
    int getSteps() const;
};

/**
 * @class ArrayMovingObject
 * Container class for storing all moving objects in the game
 */
class ArrayMovingObject
{
private:
    int count, capacity;
    MovingObject **arr_mv_objs;

public:
    /**
     * Constructor for ArrayMovingObject
     * @param capacity Maximum number of objects the array can hold
     */
    ArrayMovingObject(int capacity);

    /**
     * Destructor for ArrayMovingObject
     */
    ~ArrayMovingObject();

    /**
     * Check if array has reached maximum capacity
     * @return bool True if full
     */
    bool isFull() const;

    /**
     * Add a moving object to the array
     * @param mv_obj Pointer to the moving object
     * @return bool True if added successfully
     */
    bool add(MovingObject *mv_obj);

    /**
     * Get object at specified index
     * @param index Array index
     * @return MovingObject* Pointer to object or nullptr if invalid index
     */
    MovingObject *get(int index) const;

    /**
     * Get string representation of all objects
     * @return string Format: "ArrayMovingObject[count=X;capacity=Y;obj1;obj2;...]"
     */
    string str() const;

    /**
     * Get maximum capacity
     * @return int Capacity
     */
    int getCapacity() const;

    /**
     * Get current size (alias for getCount)
     * @return int Object count
     */
    int size() const;
};

/**
 * @class Configuration
 * Reads and stores game configuration from a file
 */
class Configuration
{
    friend class StudyPinkProgram;

private:
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls, num_fake_walls;
    Position *arr_walls;
    Position *arr_fake_walls;
    int sherlock_init_hp, sherlock_init_exp;
    string sherlock_moving_rule, watson_moving_rule;
    Position watson_init_pos;
    Position criminal_init_pos;
    Position sherlock_init_pos;
    int watson_init_hp, watson_init_exp, num_steps;

public:
    /**
     * Constructor that reads configuration from file
     * @param filepath Path to the configuration file
     */
    Configuration(const string &filepath);

    /**
     * Destructor for Configuration
     */
    ~Configuration();

    /**
     * Get string representation of configuration
     * @return string Multi-line configuration details
     */
    string str() const;
};

/**
 * @class Robot
 * Abstract base class for all robot types
 */
class Robot : public MovingObject
{
protected:
    Criminal *criminal;
    RobotType robot_type;
    BaseItem *item;

public:
    /**
     * Constructor for Robot
     * @param index Robot's index
     * @param init_pos Initial position
     * @param map Pointer to the game map
     * @param criminal Pointer to the Criminal
     * @param robot_type Type of robot (C, S, W, SW)
     */
    Robot(int index, const Position &init_pos, Map *map, Criminal *criminal, RobotType robot_type);

    /**
     * Virtual destructor for Robot
     */
    virtual ~Robot();

    /**
     * Initialize the item this robot carries based on position
     * @param i Row coordinate
     * @param j Column coordinate
     * @note Item determined by digit sum of (i*j)
     */
    void initializeItem(int i, int j);

    /**
     * Calculate next position (pure virtual)
     * @return Position Next position
     */
    virtual Position getNextPosition() = 0;

    /**
     * Execute movement (pure virtual)
     */
    virtual void move() = 0;

    /**
     * Get string representation of robot
     * @return string Robot details
     */
    string str() const;

    /**
     * Get the robot's type
     * @return RobotType Robot type enum value
     */
    virtual RobotType getRobotType() const;

    /**
     * Get the item this robot carries
     * @return BaseItem* Pointer to the robot's item
     */
    virtual BaseItem *getItem() const;
};
/**
 * @class RobotC
 * Robot that follows Criminal's previous position
 */
class RobotC : public Robot
{
public:
    /**
     * Constructor for RobotC
     * @param index Robot's index
     * @param init_pos Initial position
     * @param map Pointer to the game map
     * @param criminal Pointer to the Criminal
     */
    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal);

    /**
     * Destructor for RobotC
     */
    ~RobotC() {}

    /**
     * Get next position (Criminal's previous position)
     * @return Position Criminal's previous position or npos
     */
    Position getNextPosition();

    /**
     * Calculate Manhattan distance to Sherlock
     * @param sher Pointer to Sherlock
     * @return long long Distance to Sherlock
     */
    long long distancetoSher(Sherlock *sher) const;

    /**
     * Calculate Manhattan distance to Watson
     * @param wats Pointer to Watson
     * @return long long Distance to Watson
     */
    long long distancetoWats(Watson *wats) const;

    /**
     * Move RobotC to Criminal's previous position
     */
    void move();

    /**
     * Get string representation
     * @return string Format: "Robot[pos=(r,c);type=C;dist=]"
     */
    string str();

    /**
     * Get robot name
     * @return string "RobotC"
     */
    string getName();
};

/**
 * @class RobotS
 * Robot that chases Sherlock, moves toward him
 */
class RobotS : public Robot
{
private:
    Sherlock *sherlock;

public:
    /**
     * Constructor for RobotS
     * @param index Robot's index
     * @param init_pos Initial position
     * @param map Pointer to the game map
     * @param criminal Pointer to the Criminal
     * @param sherlock Pointer to Sherlock for tracking
     */
    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock);

    /**
     * Destructor for RobotS
     */
    ~RobotS() {}

    /**
     * Find position that minimizes distance to Sherlock
     * @return Position Best position or npos
     */
    Position getNextPosition();

    /**
     * Calculate Manhattan distance to Sherlock from given position
     * @param Robotrow Row coordinate
     * @param Robotcol Column coordinate
     * @return long long Distance to Sherlock
     */
    long long distancetoSherlock(int Robotrow, int Robotcol);

    /**
     * Get current distance to Sherlock
     * @return long long Manhattan distance
     */
    long long getDistance();

    /**
     * Move RobotS toward Sherlock
     */
    void move();

    /**
     * Get string representation
     * @return string Format: "Robot[pos=(r,c);type=S;dist=X]"
     */
    string str();

    /**
     * Get robot name
     * @return string "RobotS"
     */
    string getName();
};

/**
 * @class RobotW
 * Robot that chases Watson, moves toward him
 */
class RobotW : public Robot
{
private:
    Watson *watson;

public:
    /**
     * Constructor for RobotW
     * @param index Robot's index
     * @param init_pos Initial position
     * @param map Pointer to the game map
     * @param criminal Pointer to the Criminal
     * @param watson Pointer to Watson for tracking
     */
    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson);

    /**
     * Destructor for RobotW
     */
    ~RobotW() {}

    /**
     * Find position that minimizes distance to Watson
     * @return Position Best position or npos
     */
    Position getNextPosition();

    /**
     * Calculate Manhattan distance to Watson from given position
     * @param Robotrow Row coordinate
     * @param Robotcol Column coordinate
     * @return long long Distance to Watson
     */
    long long distancetoWatson(int Robotrow, int Robotcol);

    /**
     * Move RobotW toward Watson
     */
    void move();

    /**
     * Get current distance to Watson
     * @return long long Manhattan distance
     */
    long long getDistance();

    /**
     * Get string representation
     * @return string Format: "Robot[pos=(r,c);type=W;dist=X]"
     */
    string str();

    /**
     * Get robot name
     * @return string "RobotW"
     */
    string getName();
};

/**
 * @class RobotSW
 * Robot that chases both Sherlock and Watson, moves 2 steps at a time
 */
class RobotSW : public Robot
{
private:
    Sherlock *sherlock;
    Watson *watson;

public:
    /**
     * Constructor for RobotSW
     * @param index Robot's index
     * @param init_pos Initial position
     * @param map Pointer to the game map
     * @param criminal Pointer to the Criminal
     * @param sherlock Pointer to Sherlock for tracking
     * @param watson Pointer to Watson for tracking
     */
    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);

    /**
     * Destructor for RobotSW
     */
    ~RobotSW() = default;

    /**
     * Find position that minimizes total distance to both characters
     * @return Position Best position or npos (moves 2 cells at a time)
     */
    Position getNextPosition();

    /**
     * Calculate Manhattan distance to Watson from given position
     * @param Robotrow Row coordinate
     * @param Robotcol Column coordinate
     * @return long long Distance to Watson
     */
    long long distancetoWats(int Robotrow, int Robotcol);

    /**
     * Calculate Manhattan distance to Sherlock from given position
     * @param Robotrow Row coordinate
     * @param Robotcol Column coordinate
     * @return long long Distance to Sherlock
     */
    long long distancetoSher(int Robotrow, int Robotcol);

    /**
     * Move RobotSW toward both characters (2 steps)
     */
    void move();

    /**
     * Get sum of distances to both Sherlock and Watson
     * @return long long Total Manhattan distance
     */
    long long getDistance();

    /**
     * Get string representation
     * @return string Format: "Robot[pos=(r,c);type=SW;dist=X]"
     */
    string str();

    /**
     * Get robot name
     * @return string "RobotSW"
     */
    string getName();
};

/**
 * @class BaseItem
 * Abstract base class for all items in the game
 */
class BaseItem
{
public:
    ItemType item_type; /**< Type of the item */
    BaseItem *next;     /**< Pointer to next item in bag (linked list) */

    /**
     * Get the item's type
     * @return ItemType Item type enum value
     */
    ItemType getItemType();

    /**
     * Constructor for BaseItem
     * @param item_type Type of the item
     */
    BaseItem(ItemType item_type);

    /**
     * Check if item can be used by character (pure virtual)
     * @param obj Character attempting to use the item
     * @param robot Robot involved in encounter (can be nullptr)
     * @return bool True if item can be used
     */
    virtual bool canUse(Character *obj, Robot *robot) = 0;

    /**
     * Use the item on character (pure virtual)
     * @param obj Character using the item
     * @param robot Robot involved in encounter (can be nullptr)
     */
    virtual void use(Character *obj, Robot *robot) = 0;

    /**
     * Get item name as string
     * @return string Item name ("MagicBook", "EnergyDrink", etc.)
     */
    string getItemName();
};

/**
 * @class MagicBook
 * Item that increases EXP by 25% when used
 */
class MagicBook : public BaseItem
{
public:
    /**
     * Constructor for MagicBook
     */
    MagicBook() : BaseItem(MAGIC_BOOK)
    {
        this->item_type = MAGIC_BOOK;
    }

    /**
     * Check if MagicBook can be used
     * @param obj Character attempting to use
     * @param robot Robot in encounter (unused)
     * @return bool True if character's EXP <= 350
     */
    bool canUse(Character *obj, Robot *robot);

    /**
     * Use MagicBook to increase EXP by 25%
     * @param obj Character using the item
     * @param robot Robot in encounter (unused)
     */
    void use(Character *obj, Robot *robot);
};

/**
 * @class EnergyDrink
 * Item that increases HP by 20% when used
 */
class EnergyDrink : public BaseItem
{
public:
    /**
     * Constructor for EnergyDrink
     */
    EnergyDrink() : BaseItem(ENERGY_DRINK)
    {
        this->item_type = ENERGY_DRINK;
    }

    /**
     * Check if EnergyDrink can be used
     * @param obj Character attempting to use
     * @param robot Robot in encounter (unused)
     * @return bool True if character's HP <= 100
     */
    bool canUse(Character *obj, Robot *robot);

    /**
     * Use EnergyDrink to increase HP by 20%
     * @param obj Character using the item
     * @param robot Robot in encounter (unused)
     */
    void use(Character *obj, Robot *robot);
};
/**
 * @class FirstAid
 * Item that increases HP by 50% when used
 */
class FirstAid : public BaseItem
{
public:
    /**
     * Constructor for FirstAid
     */
    FirstAid() : BaseItem(FIRST_AID)
    {
        this->item_type = FIRST_AID;
    }

    /**
     * Check if FirstAid can be used
     * @param obj Character attempting to use
     * @param robot Robot in encounter (unused)
     * @return bool True if EXP <= 350 OR HP <= 100
     */
    bool canUse(Character *obj, Robot *robot);

    /**
     * Use FirstAid to increase HP by 50%
     * @param obj Character using the item
     * @param robot Robot in encounter (unused)
     */
    void use(Character *obj, Robot *robot);
};
/**
 * @class ExcemptionCard
 * Item that protects Sherlock from robot challenge penalties
 */
class ExcemptionCard : public BaseItem
{
public:
    /**
     * Constructor for ExcemptionCard
     */
    ExcemptionCard() : BaseItem(EXCEMPTION_CARD)
    {
        this->item_type = EXCEMPTION_CARD;
    }

    /**
     * Check if ExcemptionCard can be used
     * @param obj Character attempting to use
     * @param robot Robot in encounter
     * @return bool True if Sherlock and EXP is odd
     */
    bool canUse(Character *obj, Robot *robot);

    /**
     * Use ExcemptionCard to prevent HP/EXP loss
     * @param obj Character using the item
     * @param robot Robot in encounter
     */
    void use(Character *obj, Robot *robot);
};
/**
 * @class PassingCard
 * Item that allows Watson to bypass robot challenges
 */
class PassingCard : public BaseItem
{
public:
    /**
     * Default constructor for PassingCard
     */
    PassingCard() : BaseItem(PASSING_CARD)
    {
        this->item_type = PASSING_CARD;
    }

    /**
     * Constructor with challenge type
     * @param challenge Robot type name ("RobotS", "RobotC", etc.) or "all"
     */
    PassingCard(string challenge) : BaseItem(PASSING_CARD)
    {
        this->challenge = challenge;
    }

    /**
     * Check if PassingCard can be used
     * @param obj Character attempting to use
     * @param robot Robot in encounter
     * @return bool True if Watson and EXP is even
     */
    bool canUse(Character *obj, Robot *robot);

    /**
     * Use PassingCard to bypass robot challenge
     * @param obj Character using the item
     * @param robot Robot in encounter
     * @note If challenge doesn't match, Watson loses 50 EXP
     */
    void use(Character *obj, Robot *robot);

    /**
     * Convert RobotType enum to string
     * @param robot_type Robot type enum
     * @return string "RobotC", "RobotS", "RobotW", or "RobotSW"
     */
    string RobotTypeToString(RobotType robot_type);

    string challenge = ""; /**< Challenge type for this card */

    /**
     * Get the challenge type of this card
     * @return string Challenge type
     */
    string getChallenge() const;
};

/**
 * @class BaseBag
 * Base class for character bags (inventory system using linked list)
 */
class BaseBag
{
public:
    BaseItem *head; /**< Head of the linked list of items */
    Character *obj; /**< Owner of the bag */
    int count;      /**< Current number of items */
    int capacity;   /**< Maximum capacity of the bag */

    /**
     * Constructor for BaseBag
     * @param obj Owner of the bag
     * @param capacity Maximum items the bag can hold
     */
    BaseBag(Character *obj, int capacity);

    /**
     * Destructor for BaseBag
     */
    ~BaseBag();

    /**
     * Insert an item at the front of the bag (stack behavior)
     * @param newItem Item to add
     * @return bool True if added successfully, false if bag is full
     */
    virtual bool insert(BaseItem *newItem);

    /**
     * Get and remove the first usable item from the bag
     * @return BaseItem* First item where canUse() returns true, or nullptr
     */
    virtual BaseItem *get();

    /**
     * Get and remove a specific item type from the bag
     * @param itemType Type of item to find
     * @return BaseItem* Found item or nullptr
     */
    virtual BaseItem *get(ItemType itemType);

    /**
     * Get string representation of the bag
     * @return string Format: "Bag[count=X;Item1,Item2,...]"
     */
    virtual string str() const;

    /**
     * Get comma-separated list of item names
     * @return string Item names list
     */
    string listname() const;

    /**
     * Get current number of items
     * @return int Item count
     */
    int getCount() const;

    /**
     * Get maximum capacity
     * @return int Capacity
     */
    int getCapacity() const;
};
/**
 * @class SherlockBag
 * Sherlock's inventory bag with capacity of 13
 */
class SherlockBag : public BaseBag
{
public:
    /**
     * Constructor for SherlockBag
     * @param sher Pointer to Sherlock
     */
    SherlockBag(Sherlock *sher);
};

/**
 * @class WatsonBag
 * Watson's inventory bag with capacity of 15
 */
class WatsonBag : public BaseBag
{
public:
    /**
     * Constructor for WatsonBag
     * @param wats Pointer to Watson
     */
    WatsonBag(Watson *wats);
};

/**
 * @class StudyPinkProgram
 * @brief Main game controller class that runs the Study in Pink game
 */
class StudyPinkProgram
{
private:
    Configuration *config;          /**< Game configuration */
    Sherlock *sherlock;             /**< Pointer to Sherlock */
    Watson *watson;                 /**< Pointer to Watson */
    Criminal *criminal;             /**< Pointer to Criminal */
    Robot *robot;                   /**< Pointer to current robot */
    BaseItem *item;                 /**< Pointer to current item */
    Map *map;                       /**< Pointer to game map */
    ArrayMovingObject *arr_mv_objs; /**< Array of all moving objects */

public:
    /**
     * @brief Constructor that initializes game from config file
     * @param config_file_path Path to configuration file
     */
    StudyPinkProgram(const string &config_file_path);

    mutable bool caught = false; /**< Flag indicating if Criminal is caught */

    /**
     * @brief Check if game should end
     * @return bool True if Criminal caught, or Sherlock/Watson HP=0, or positions match
     */
    bool isStop() const;

    /**
     * @brief Handle Sherlock's encounters with other objects
     * @param sherlock Pointer to Sherlock
     * @param sherbag Reference to Sherlock's bag
     * @param watsbag Reference to Watson's bag
     */
    void checkEncounterOfSherlock(Sherlock *sherlock, SherlockBag &sherbag, WatsonBag &watsbag);

    /**
     * @brief Handle Sherlock's robot challenge
     * @param sherlock Pointer to Sherlock
     * @param robot Pointer to the robot
     * @param sherbag Reference to Sherlock's bag
     */
    void SherlockHandleRobot(Sherlock *sherlock, Robot *robot, SherlockBag &sherbag);

    /**
     * @brief Handle Watson's encounters with other objects
     * @param watson Pointer to Watson
     * @param sherbag Reference to Sherlock's bag
     * @param watsbag Reference to Watson's bag
     */
    void checkEncounterOfWatson(Watson *watson, SherlockBag &sherbag, WatsonBag &watsbag);

    /**
     * @brief Handle Watson's robot challenge
     * @param watson Pointer to Watson
     * @param robot Pointer to the robot
     * @param watsbag Reference to Watson's bag
     */
    void WatsonHandleRobot(Watson *watson, Robot *robot, WatsonBag &watsbag);

    /**
     * @brief Handle robot's encounter with characters after robot moves
     * @param robot Pointer to the robot
     * @param sherbag Reference to Sherlock's bag
     * @param watsbag Reference to Watson's bag
     */
    void checkEncounterOfRobot(Robot *robot, SherlockBag &sherbag, WatsonBag &watsbag);

    /**
     * @brief Use items from Sherlock's bag to restore HP/EXP
     * @param character Pointer to the character
     * @param sherbag Reference to Sherlock's bag
     */
    void restoreHPandEXP(Character *character, SherlockBag &sherbag);

    /**
     * @brief Use items from Watson's bag to restore HP/EXP
     * @param character Pointer to the character
     * @param watsbag Reference to Watson's bag
     */
    void restoreHPandEXP(Character *character, WatsonBag &watsbag);

    /**
     * @brief Print final game result
     */
    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }

    /**
     * @brief Print current step state
     * @param si Step index
     */
    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    /**
     * @brief Main game loop
     * @param verbose If true, prints each step
     */
    void run(bool verbose)
    {

        SherlockBag sherbag(sherlock);
        WatsonBag watsbag(watson);
        for (int istep = 0; istep < config->num_steps; ++istep)
        {
            for (int i = 0; i < arr_mv_objs->size(); ++i)
            {
                arr_mv_objs->get(i)->move();
                MovingObject *obj = arr_mv_objs->get(i);
                if (obj == sherlock)
                {
                    checkEncounterOfSherlock(sherlock, sherbag, watsbag);
                }
                else if (obj == watson)
                {
                    checkEncounterOfWatson(watson, sherbag, watsbag);
                }
                else if (obj != sherlock && obj != watson && obj != criminal)
                {
                    Robot *robot = dynamic_cast<Robot *>(obj);
                    if (robot)
                        checkEncounterOfRobot(robot, sherbag, watsbag);
                }
                if (isStop())
                {
                    printStep(istep);
                    break;
                }
                if (criminal->getSteps() % 3 == 0)
                {
                    criminal->createRobot();
                }
                if (verbose)
                {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    /**
     * @brief Destructor for StudyPinkProgram
     */
    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
