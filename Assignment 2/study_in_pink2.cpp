#include "study_in_pink2.h"
int FakeWall::getReqExp() const
{
    return req_exp;
}

int Position::getRow() const
{
    return this->r;
}
int Position::getCol() const
{
    return this->c;
}
void Position::setRow(int row)
{
    this->r = row;
}
void Position::setCol(int col)
{
    this->c = col;
}
string Position::str() const
{
    string R = to_string(r);
    string C = to_string(c);
    string str = "(" + R + "," + C + ")";
    return str;
}
bool Position::isEqual(int in_r, int in_c) const
{
    if ((r == in_r) && (c == in_c))
        return true;
    else
        return false;
}

bool Position::isEqual(const Position &pos) const
{
    if ((r == pos.getRow()) && (c == pos.getCol()))
        return true;
    else
        return false;
}

Position MovingObject::getCurrentPosition() const
{
    return pos;
}

Position Sherlock::getNextPosition()
{
    int r = pos.getRow();
    int c = pos.getCol();
    // moving rule = RUU
        char move = moving_rule[i++];
        if (i == moving_rule.length())
            i = 0;
        switch (move)
        {
        case 'L':
            c--;
            break;

        case 'U':
            r--;
            break;

        case 'R':
            c++;
            break;

        case 'D':
            r++;
            break;

        default:
            break;
        }

        Position nextpos(r, c);
        if (!map->isValid(nextpos, this))
            return Position::npos;
        else
        {
            pos = nextpos;
            return pos;
        }
        return Position::npos;
}

void Sherlock::move()
{
    if (hp <= 0 || exp <= 0)
        return;
    else
    {
        Position nextpos = getNextPosition();
        if ((nextpos.getRow() != -1) && (nextpos.getCol() != -1) && map->isValid(nextpos, this))
        {
            pos = nextpos;
        }
    }
}

string Sherlock::str() const
{
    return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

Position Watson::getNextPosition()
{
int r = pos.getRow();
int c = pos.getCol();
    char move = this->moving_rule[i++];
    if (i == this->moving_rule.length())
        i = 0;
    switch (move)
    {
    case 'L':
        c--;
        break;

    case 'U':
        r--;
        break;

    case 'R':
        c++;
        break;

    case 'D':
        r++;
        break;

    default:
        break;
    }

    Position nextpos(r, c);
    if (!map->isValid(nextpos, this))
        return Position::npos;
    else
    {
        pos = nextpos;
        return pos;
    }
    return Position::npos;
}

void Watson::move()
{
    if (this->hp <= 0 || this->exp <= 0)
        return;
    else
    {
        Position nextPos = getNextPosition();
        if ((nextPos.getRow() != -1) && (nextPos.getCol() != -1) && map->isValid(nextPos, this))
        {
            pos = nextPos;
        }
    }
}
string Watson::str() const
{
    return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + this->moving_rule + "]";
}

long long Criminal::distance_to_sher(int crim_row, int crim_col)
{
    return abs(sherlock->getRow() - crim_row) + abs(sherlock->getCol() - crim_col);
}
long long Criminal::distance_to_wats(int crim_row, int crim_col)
{
    return abs(watson->getRow() - crim_row) + abs(watson->getCol() - crim_col);
}

// U=0 , L=1, D=2, R=3
Position Criminal::calculateNextPos(Position current, int direction)
{
    Position next;
    switch (direction)
    {
    case 0:
        next = Position(current.getRow() - 1, current.getCol());
        break;
    case 1:
        next = Position(current.getRow(), current.getCol() - 1);
        break;
    case 2:
        next = Position(current.getRow() + 1, current.getCol());
        break;
    case 3:
        next = Position(current.getRow(), current.getCol() + 1);
        break;
    }
    if (map->isValid(next, this))
        return next;
    else
        return current;
    // co the se~ can (else return current;) neu vi tri inValid
}
long long Criminal::ManhattanDistance(Position current)
{
    return distance_to_sher(current.getRow(), current.getCol()) + distance_to_wats(current.getRow(), current.getCol());
}

const Position Position::npos(-1, -1);

Position Criminal::getPreviousPosition()
{
    return previousposition;
}

string Criminal::str() const
{
    return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

Position Criminal::getNextPosition()
{
    Position current = getCurrentPosition();
    Position bestmove = current;
    //Position bestmove = Position::npos;
    long long MaxDist = -1;
    int bestDirection = -1;
    for (int i = 0; i < 4; i++){
        Position next = calculateNextPos(current, i);
    if (MaxDist < ManhattanDistance(next) || ManhattanDistance(next) == MaxDist && i < bestDirection)
        {
            MaxDist = ManhattanDistance(next);
            bestmove = next;
            bestDirection = i;
        }
    }
    // if(map->isValid(bestmove,this)) return bestmove;
    //     return Position::npos;
    if(bestmove.isEqual(current.getRow(),current.getCol())) return Position::npos;
    else return bestmove;
    //return bestmove;
}

void Criminal::createRobot()
{
    if (moving_obj->isFull()) return;
    MovingObject *robot = nullptr;
    long long distancetoSher = distance_to_sher(getPreviousPosition().getRow(), getPreviousPosition().getCol());
    long long distancetoWats = distance_to_wats(getPreviousPosition().getRow(), getPreviousPosition().getCol());

    if (robotsCreated == 0)
    {
        robot = new RobotC(index, getPreviousPosition(), map, this);
        robotsCreated++;
    }
    else if (distancetoSher < distancetoWats)
        robot = new RobotS(index, getPreviousPosition(), map, this, sherlock);
    else if (distancetoSher > distancetoWats)
        robot = new RobotW(index, getPreviousPosition(), map, this, watson);
    else if (distancetoSher == distancetoWats)
        robot = new RobotSW(index, getPreviousPosition(), map, this, sherlock, watson);

    if (robot != nullptr) moving_obj->add(robot);
}

void Criminal::move()
{
    if (this->hp < 0)
        return;
    else
    {
        Position nextPos = getNextPosition();
        if (map->isValid(nextPos, this) && (nextPos.getCol() != -1) && (nextPos.getRow() != -1)) {
            previousposition = pos;
            pos = nextPos;
            moved = true;
            steps++;
            //if (steps % 3 == 0) createRobot();
        }
        else
            return;
    }
}

int Criminal::getSteps() const
{
    return this->steps;
}

bool ArrayMovingObject::isFull() const
{
    return count == capacity;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    if (!isFull())
    {
        arr_mv_objs[count] = mv_obj;
        count++;
        return true;
    }
    else
        return false;
}

MovingObject *ArrayMovingObject::get(int index) const
{
    if (index >= 0 && index < count)
        return arr_mv_objs[index];
    else
        return nullptr;
}

string ArrayMovingObject::str() const
{
    string result = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity);
    for (int i = 0; i < count; i++)
    {
        result += ";" + arr_mv_objs[i]->str();
    }
    result += "]";
    return result;
}

int ArrayMovingObject::getCapacity() const {
    return this->capacity;
}

int ArrayMovingObject::size() const{
    return this->count;
}

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
{
    this->num_rows = num_rows;
    this->num_cols = num_cols;

    map = new MapElement **[num_rows];

    for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement *[num_cols];
    }

    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            map[i][j] = nullptr;
        }
    }

    for (int i = 0; i < num_walls; i++){
        map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall();
    }

    for (int i = 0; i < num_fake_walls; i++){
        int in_req_exp = (array_fake_walls[i].getRow() * 257 + array_fake_walls[i].getCol() * 139 + 89) % 900 + 1;
        map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()] = new FakeWall(in_req_exp);
    }

    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            if (map[i][j] == nullptr)
                map[i][j] = new Path();
        }
    }
}

Map::~Map() {
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}

int Map::getNumRows() const{
    return num_rows;
}
int Map::getNumCols() const{
    return num_cols;
}

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const{
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
        return false;

    if (map[pos.getRow()][pos.getCol()]->getType() == WALL)
        return false;

    else if (map[pos.getRow()][pos.getCol()]->getType() == FAKE_WALL)
    {
        string concac = mv_obj->str();

        if (concac.find("Watson") != string::npos)
        {
            FakeWall *fake = dynamic_cast<FakeWall *>(map[pos.getRow()][pos.getCol()]);
            return dynamic_cast<Watson *>(mv_obj)->getEXP() > fake->getReqExp();
        }
    }
    return true;
}

Position::Position(int r, int c)
{
    this->r = r;
    this->c = c;
}
Position::Position(const string &str_pos)
{
    this->r = stoi(str_pos.substr(1, str_pos.find(",") - 1));
    this->c = stoi(str_pos.substr(str_pos.find(",") + 1, str_pos.size() - str_pos.find(",") - 2));
}

MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name)
{
    this->index = index;
    this->pos = pos;
    this->map = map;
    this->name = name;
}
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) : Character(index, init_pos, map, "Sherlock")
{
    if (init_hp > 500)
        hp = init_hp = 500;
    // else if (init_hp < 0) pos = Position::npos;
    else
        hp = init_hp;
    if (init_exp > 900)
        exp = init_exp = 900;
    else
        exp = init_exp;
    this->moving_rule = moving_rule;
    i = 0;
}
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) : Character(index, init_pos, map, "Watson")
{
    if (init_hp > 500)
        this->hp = init_hp = 500;
    else
        this->hp = init_hp;
    if (init_exp > 900)
        this->exp = init_exp = 900;
    else
        this->exp = init_exp;
    this->moving_rule = moving_rule;
}
Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson) : Character(index, init_pos, map, "Criminal")
{
    this->sherlock = sherlock;
    this->watson = watson;
    this->hp = 0;
    this->exp = 0;
    previousposition = pos;
    steps = 0;
    robotsCreated = 0;
}
ArrayMovingObject::ArrayMovingObject(int capacity)
{
    this->capacity = capacity;
    this->count = 0;
    arr_mv_objs = new MovingObject *[capacity];
}
ArrayMovingObject::~ArrayMovingObject()
{
    delete[] arr_mv_objs;
}

MovingObject::~MovingObject() {}

Configuration::Configuration(const string &filepath)
{
    ifstream file(filepath);
     map_num_cols = 0;
     map_num_rows = 0;
     max_num_moving_objects = 0;
     num_walls = 0;
     num_fake_walls = 0;
     sherlock_init_exp = 0;
     sherlock_init_hp = 0;
     sherlock_init_pos = Position(0, 0);
     watson_init_pos = Position(0, 0);
     watson_init_exp = 0;
     watson_init_hp = 0;
     watson_init_pos = 0;
     num_steps = 0;
     sherlock_moving_rule = "U";
     watson_moving_rule = "U";
     arr_walls = nullptr;
     arr_fake_walls = nullptr;

    //  if (file.is_open()) {

    string line;
    // khi getline thi se nhap cac dong tu file vao string line, moi khi xuong dong no se doc tiep cho toi khi het file
    while (getline(file, line))
    {
        stringstream ss(line);
        string key, value;
        getline(ss, key, '=');
        getline(ss, value);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (key == "MAP_NUM_ROWS")
            map_num_rows = stoi(value);
        else if (key == "MAP_NUM_COLS")
            map_num_cols = stoi(value);
        else if (key == "MAX_NUM_MOVING_OBJECTS")
            max_num_moving_objects = stoi(value);
        else if (key == "ARRAY_WALLS")
        {
            int count = 0;
            for (int i = 0; i < value.length(); i++)
            {
                if (value[i] == ',')
                    count++;
            }
            num_walls = count;

            if (num_walls > 1)
            {
                arr_walls = new Position[num_walls];
                for (int i = 0; i < num_walls; i++)
                {
                    size_t position = value.find(';');
                    size_t obracketpos = value.find('(');
                    size_t cbracketpos = value.find(')');
                    size_t comma_position = value.find(',');
                    string row = value.substr(obracketpos + 1, comma_position - obracketpos);
                    int r = stoi(row);
                    string col = value.substr(comma_position + 1, cbracketpos - comma_position);
                    int c = stoi(col);
                    arr_walls[i] = Position(r, c);
                    value = value.substr(position + 1);
                    position = value.find(';');
                }
            }
            else if(num_walls ==0){
            
            }
            else
            {
                arr_walls = new Position[num_walls];
                size_t obracketpos = value.find('(');
                size_t cbracketpos = value.find(')');
                size_t comma_position = value.find(',');
                string row = value.substr(obracketpos + 1, comma_position - obracketpos);
                int r = stoi(row);
                string col = value.substr(comma_position + 1, cbracketpos - comma_position);
                int c = stoi(col);
                arr_walls[0] = Position(r, c);
            }
        }
        else if (key == "ARRAY_FAKE_WALLS")
        {
            int count = 0;
            for (int i = 0; i < value.length(); i++)
            {
                if (value[i] == ',')
                    count++;
            }
            num_fake_walls = count;
            if (num_fake_walls > 1)
            {
                arr_fake_walls = new Position[num_fake_walls];
                for (int i = 0; i < num_fake_walls; i++)
                {
                    size_t position = value.find(';');
                    size_t obracketpos = value.find('(');
                    size_t cbracketpos = value.find(')');
                    size_t comma_position = value.find(',');
                    string row = value.substr(obracketpos + 1, comma_position - obracketpos);
                    int r = stoi(row);
                    string col = value.substr(comma_position + 1, cbracketpos - comma_position);
                    int c = stoi(col);
                    arr_fake_walls[i] = Position(r, c);
                    value = value.substr(position + 1);
                    position = value.find(';');
                }
            }
            else if(num_fake_walls == 0){}
            else
            {
                arr_fake_walls = new Position[num_fake_walls];
                size_t obracketpos = value.find('(');
                size_t cbracketpos = value.find(')');
                size_t comma_position = value.find(',');
                string row = value.substr(obracketpos + 1, comma_position - obracketpos);
                int r = stoi(row);
                string col = value.substr(comma_position + 1, cbracketpos - comma_position);
                int c = stoi(col);
                arr_fake_walls[0] = Position(r, c);
            }
        }
        else if (key == "SHERLOCK_MOVING_RULE")
            sherlock_moving_rule = value;
        else if (key == "SHERLOCK_INIT_HP")
            sherlock_init_hp = stoi(value);
        else if (key == "SHERLOCK_INIT_EXP")
            sherlock_init_exp = stoi(value);
        else if (key == "WATSON_MOVING_RULE")
            watson_moving_rule = value;
        else if (key == "WATSON_INIT_HP")
            watson_init_hp = stoi(value);
        else if (key == "WATSON_INIT_EXP")
            watson_init_exp = stoi(value);
        else if (key == "NUM_STEPS")
            num_steps = stoi(value);
        else if (key == "WATSON_INIT_POS")
        {
            size_t obracketpos = value.find('(');
            size_t cbracketpos = value.find(')');
            size_t comma_position = value.find(',');
            string row = value.substr(obracketpos + 1, comma_position - obracketpos);
            int r = stoi(row);
            string col = value.substr(comma_position + 1, cbracketpos - comma_position);
            int c = stoi(col);
            watson_init_pos = Position(r, c);
        }
        else if (key == "SHERLOCK_INIT_POS")
        {
            size_t obracketpos = value.find('(');
            size_t cbracketpos = value.find(')');
            size_t comma_position = value.find(',');
            string row = value.substr(obracketpos + 1, comma_position - obracketpos);
            int r = stoi(row);
            string col = value.substr(comma_position + 1, cbracketpos - comma_position);
            int c = stoi(col);
            sherlock_init_pos = Position(r, c);
        }
        else if (key == "CRIMINAL_INIT_POS")
        {
            size_t obracketpos = value.find('(');
            size_t cbracketpos = value.find(')');
            size_t comma_position = value.find(',');
            string row = value.substr(obracketpos + 1, comma_position - obracketpos);
            int r = stoi(row);
            string col = value.substr(comma_position + 1, cbracketpos - comma_position);
            int c = stoi(col);
            criminal_init_pos = Position(r, c);
        }
    }

    file.close();
}

Configuration::~Configuration()
{
    delete[] arr_walls;
    delete[] arr_fake_walls;
}

string Configuration::str() const
{
    string result = "Configuration[\n";
    result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n" + "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n" + "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
    result += "NUM_WALLS=" + to_string(num_walls) + "\n";
    result += "ARRAY_WALLS=[";
    if(num_walls > 0)
    {   
        result+="(";
        for (int i = 0; i < num_walls; i++)
        {
        result += to_string(arr_walls[i].getRow()) + "," + to_string(arr_walls[i].getCol()) + ")";
        if (i < num_walls - 1)
            result += ";(";
        }
    }
    result += "]\n";

    result += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n" + "ARRAY_FAKE_WALLS=[";
    if(num_fake_walls > 0)
    {   
        result+="(";
        for (int i = 0; i < num_fake_walls; i++)
        {
        result += to_string(arr_fake_walls[i].getRow()) + "," + to_string(arr_fake_walls[i].getCol()) + ")";
        if (i < num_fake_walls - 1)
            result += ";(";
        }
    }
    result += "]\n";
    result += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n" + "SHERLOCK_INIT_POS=" + sherlock_init_pos.str() + "\n";
    result += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n" + "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
    result += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n" + "WATSON_INIT_POS=" + watson_init_pos.str() + "\n";
    result += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n" + "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
    result += "CRIMINAL_INIT_POS=" + criminal_init_pos.str() + "\n" + "NUM_STEPS=" + to_string(num_steps) + "\n" + "]\n";
    return result;
}

Robot::Robot(int index, const Position& init_pos, Map *map, Criminal *criminal, RobotType robot_type) : MovingObject(index, init_pos, map, "Robot")
{
    this->robot_type = robot_type;
    this->criminal = criminal;
    this->item  = nullptr;
    initializeItem(init_pos.getRow(), init_pos.getCol());
}

Robot::~Robot() {}

void Robot::initializeItem(int i, int j)
{
    int p = i * j;
    int s = 0;
    while (p > 0)
    {
        s += p % 10;
        p /= 10;
    }
    while (s >= 10)
    {
        int temp = s;
        s = 0;
        while (temp > 0)
        {
            s += temp % 10;
            temp /= 10;
        }
    }
    if (s >= 0 && s <= 1)
        item = new MagicBook();
    else if (s >= 2 && s <= 3)
        item = new EnergyDrink();
    else if (s >= 4 && s <= 5)
        item = new FirstAid();
    else if (s >= 6 && s <= 7)
        item = new ExcemptionCard();
    else if (s >= 8 && s <= 9)
    {
        int t = (i * 11 + j) % 4;
        switch (t)
        {
        case 0:
            item = new PassingCard("RobotS");
            break;
        case 1:
            item = new PassingCard("RobotC");
            break;
        case 2:
            item = new PassingCard("RobotSW");
            break;
        case 3:
            item = new PassingCard("all");
            break;
        }
    }
}

string Robot::str() const
{
    return "";
}

RobotType Robot::getRobotType() const
{
    return robot_type;
}

BaseItem *Robot::getItem() const
{
    return item;
}

RobotC::RobotC(int index, const Position& init_pos, Map *map, Criminal *criminal) : Robot(index, init_pos, map, criminal, RobotType::C)
{
    
}
RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock) : Robot(index, init_pos, map, criminal, RobotType::S)
{
    this->sherlock = sherlock;
}

RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson) : Robot(index, init_pos, map, criminal, RobotType::W)
{
    this->watson = watson;
}

RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson) : Robot(index, init_pos, map, criminal, RobotType::SW)
{
    this->sherlock = sherlock;
    this->watson = watson;
}

long long RobotC::distancetoSher(Sherlock *sher) const
{
    return abs(pos.getRow() - sher->getCurrentPosition().getRow()) + abs(pos.getCol() - sher->getCurrentPosition().getCol());
}

long long RobotC::distancetoWats(Watson *wats) const
{
    return abs(this->pos.getRow() - wats->getCurrentPosition().getRow()) + abs(this->pos.getCol() - wats->getCurrentPosition().getCol());
}

Position RobotC::getNextPosition()
{
    if (criminal->moved)
        return criminal->getPreviousPosition();
    else
        return Position::npos;
}
void RobotC::move()
{
    Position nextpos = getNextPosition();
    if ((nextpos.getRow() != -1) && (nextpos.getCol() != -1) && map->isValid(nextpos, this))
    {
        pos = nextpos;
    }
}

string RobotC::str()
{
    return "Robot[pos=" + pos.str() + ";type=C;dist=]";
}

string RobotC::getName(){
    return "RobotC";
}

long long RobotS::distancetoSherlock(int Robotrow, int Robotcol)
{
    int RobotS_row = Robotrow;
    int RobotS_col = Robotcol;
    return abs(RobotS_row - sherlock->getRow()) + abs(RobotS_col - sherlock->getCol());
}

Position RobotS::getNextPosition() {;
    Position potentialPos = pos;
    int potentialRow = pos.getRow();
    int potentialCol = pos.getCol();
    long long min_distance = distancetoSherlock(pos.getRow(), pos.getCol());
    Position nextpos = this->pos;
    // U=0, R=1, D=2, L=3
    for (int i = 0; i < 4; i++) {
        if(i==0){
            potentialRow = pos.getRow() - 1;
            potentialCol = pos.getCol();
        }
        else if(i==1){
            potentialRow = pos.getRow();
            potentialCol = pos.getCol() + 1;
        }
        else if(i==2){
            potentialRow = pos.getRow() + 1;
            potentialCol = pos.getCol();
        }
        else if(i==3){
            potentialRow = pos.getRow();
            potentialCol = pos.getCol() - 1;
        }
        int newRow = potentialRow;
        int newCol = potentialCol;
        switch (i) {
        case 0:
            potentialPos = Position(newRow, newCol);
            break;
        case 1:
            potentialPos = Position(newRow, newCol);
            break;
        case 2:
            potentialPos = Position(newRow, newCol);
            break;
        case 3:
            potentialPos = Position(newRow, newCol);
            break;
        default:
            break;
        }
        if (map->isValid(potentialPos, this)) {
            long long distance = distancetoSherlock(newRow, newCol);
            if (distance < min_distance) {
                min_distance = distance;
                nextpos = potentialPos;
            }
        }
    }
    if (nextpos.isEqual(pos.getRow(), pos.getCol()))
        return Position::npos;
    return nextpos;
}

void RobotS::move() {
    Position nextpos = getNextPosition();
    
    if ((nextpos.getRow() != -1) && (nextpos.getCol() != -1) && (map->isValid(nextpos, this)))
        pos = nextpos;
}

long long RobotS::getDistance()
{
    return distancetoSherlock(this->pos.getRow(), this->pos.getCol());
}

string RobotS::str()
{
    return "Robot[pos=" + pos.str() + ";type=S;dist=" + to_string(getDistance()) + "]";
}

string RobotS::getName(){
    return "RobotS";
}

long long RobotW::distancetoWatson(int Robotrow, int Robotcol)
{
    return abs(Robotrow - watson->getRow()) + abs(Robotcol - watson->getCol());
}

long long RobotW::getDistance()
{
    return distancetoWatson(this->pos.getRow(), this->pos.getCol());
}

Position RobotW::getNextPosition()
{
    Position potentialPos = pos;
    int potentialRow = pos.getRow();
    int potentialCol = pos.getCol();
    int min_distance = distancetoWatson(pos.getRow(), pos.getCol());
    Position nextpos = this->pos;
    // U=0, R=1, D=2, L=3
    for (int i = 0; i < 4; i++) {
        if(i==0){
            potentialRow = pos.getRow() - 1;
            potentialCol = pos.getCol();
        }
        else if(i==1){
            potentialRow = pos.getRow();
            potentialCol = pos.getCol() + 1;
        }
        else if(i==2){
            potentialRow = pos.getRow() + 1;
            potentialCol = pos.getCol();
        }
        else if(i==3){
            potentialRow = pos.getRow();
            potentialCol = pos.getCol() - 1;
        }
        int newRow = potentialRow;
        int newCol = potentialCol;
        switch (i) {
        case 0:
            potentialPos = Position(newRow, newCol);
            break;
        case 1:
            potentialPos = Position(newRow, newCol);
            break;
        case 2:
            potentialPos = Position(newRow, newCol);
            break;
        case 3:
            potentialPos = Position(newRow, newCol);
            break;
        default:
            break;
        }
        if (map->isValid(potentialPos, this)) {
            long long distance = distancetoWatson(newRow, newCol);
            if (distance < min_distance)
            {
                min_distance = distance;
                nextpos = potentialPos;
            }
        }
        else
            return Position::npos;
    }
    if (nextpos.isEqual(pos.getRow(), pos.getCol()))
        return Position::npos;
    return nextpos;
}

void RobotW::move()
{
    Position nextpos = getNextPosition();
    if ((nextpos.getRow() != -1) && (nextpos.getCol() != -1) && (map->isValid(nextpos, this)))
        pos = nextpos;
}

string RobotW::str()
{
    return "Robot[pos=" + pos.str() + ";type=W;dist=" + to_string(getDistance()) + "]";
}

string RobotW::getName(){
    return "RobotW";
}

long long RobotSW::distancetoSher(int RobotSW_row, int RobotSW_col)
{
    return abs(RobotSW_row - sherlock->getRow()) + abs(RobotSW_col - sherlock->getCol());
}
long long RobotSW::distancetoWats(int RobotSW_row, int RobotSW_col)
{
    return abs(RobotSW_row - watson->getRow()) + abs(RobotSW_col - watson->getCol());
}

long long RobotSW::getDistance()
{
    return distancetoSher(this->pos.getRow(), this->pos.getCol()) + distancetoWats(this->pos.getRow(), this->pos.getCol());
}

Position RobotSW::getNextPosition()
{
    Position potentialPos = pos;
    int potentialRow = pos.getRow();
    int potentialCol = pos.getCol();
    int min_distance = distancetoWats(pos.getRow(), pos.getCol()) + distancetoSher(pos.getRow(), pos.getCol());
    Position nextpos = this->pos;

    // U=0, R=1, D=2, L=3
    for (int i = 0; i < 4; i++) {
        if(i==0){
            potentialRow = pos.getRow() - 2;
            potentialCol = pos.getCol();
        }
        else if(i==1){
            potentialRow = pos.getRow();
            potentialCol = pos.getCol() + 2;
        }
        else if(i==2){
            potentialRow = pos.getRow() + 2;
            potentialCol = pos.getCol();
        }
        else if(i==3){
            potentialRow = pos.getRow();
            potentialCol = pos.getCol() - 2;
        }
        int newRow = potentialRow;
        int newCol = potentialCol;
        switch (i) {
        case 0:
        potentialPos = Position(newRow, newCol);
            break;
        case 1:
            potentialPos = Position(newRow, newCol);
            break;
        case 2:
            potentialPos = Position(newRow, newCol);
            break;
        case 3:
            potentialPos = Position(newRow, newCol);
            break;
        default:
            break;
        }
        if (map->isValid(potentialPos, this)) {
            long long distance = distancetoSher(newRow, newCol) + distancetoWats(newRow, newCol);
            if (distance < min_distance) {
                min_distance = distance;
                nextpos = potentialPos;
            }
        }
    }

    if (nextpos.isEqual(pos.getRow(), pos.getCol()))
        return Position::npos;
    return nextpos;
}

void RobotSW::move()
{
    Position nextpos = getNextPosition();
    if ((nextpos.getRow() != -1) && (nextpos.getCol() != -1) && (map->isValid(nextpos, this)))
        pos = nextpos;
}

string RobotSW::str()
{
    return "Robot[pos=" + pos.str() + ";type=SW;dist=" + to_string(getDistance()) + "]";
}

string RobotSW::getName(){
    return "RobotSW";
}

Character::Character(int index, const Position &init_pos, Map *map, const string &name) : MovingObject(index, init_pos, map, name)
{
    hp = 0;
    exp = 0;
}

string Character::getName()
{
    return name;
}

int Character::getHP() const
{
    return hp;
}

int Character::getEXP() const
{
    return exp;
}

void Character::setHP(int HP)
{
    this->hp = HP;
}

void Character::setEXP(int EXP)
{
    this->exp = EXP;
}

int Character::getRow() const
{
    return pos.getRow();
}

int Character::getCol() const
{
    return pos.getCol();
}

ItemType BaseItem::getItemType()
{
    return item_type;
}

bool MagicBook::canUse(Character *obj, Robot *robot)
{
    return obj->getEXP() <= 350;
}

void MagicBook::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot))
    {
        int increase = obj->getEXP() * 0.25;
        obj->setEXP(obj->getEXP() + increase + 0.999);
    }
}

bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    return obj->getHP() <= 100;
}

void EnergyDrink::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot))
    {
        int increase = obj->getHP() * 0.2;
        obj->setHP(obj->getHP() + increase + 0.999);
    }
}
bool FirstAid::canUse(Character *obj, Robot *robot)
{
    if (obj->getEXP() <= 350 || obj->getHP() <= 100)
        return true;
    else
        return false;
}

void FirstAid::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot))
    {
        int increase = obj->getHP() * 0.5;
        obj->setHP(obj->getHP() + increase + 0.999);
    }
}

bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    if ((obj->getName() == "Sherlock") && (obj->getEXP() % 2 != 0))
        return true;
    else
        return false;
}

void ExcemptionCard::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot))
    {
        int originalHP = obj->getHP();
        int originalEXP = obj->getEXP();
        obj->setEXP(originalEXP);
        obj->setHP(originalHP);
    }
}

bool PassingCard::canUse(Character *obj, Robot *robot)
{
    if ((obj->getName() == "Watson") && (obj->getEXP() % 2 == 0))
        return true;
    else
        return false;
}

string PassingCard::RobotTypeToString(RobotType robot_type)
{
    switch (robot_type)
    {
    case RobotType::C:
        return "RobotC";
    case RobotType::S:
        return "RobotS";
    case RobotType::W:
        return "RobotW";
    case RobotType::SW:
        return "RobotSW";
    default:
        return "";
    }
}

void PassingCard::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot))
    {
        if (challenge == RobotTypeToString(robot->getRobotType()) || challenge == "all")
        {
            return; 
        }
        else
            obj->setEXP(obj->getEXP() - 50);
    }
}

string PassingCard::getChallenge() const
{
    return challenge;
}

BaseItem::BaseItem(ItemType itemtype)
{
    this->item_type = itemtype;
    this->next = nullptr;
}

BaseBag::BaseBag(Character *obj, int capacity)
{
    this->obj = obj;
    this->capacity = capacity;
    this->head = nullptr;
    this->count = 0;
}

BaseBag::~BaseBag()
{
    BaseItem *temp = head;
    while (temp != nullptr)
    {
        BaseItem *next = temp;
        temp = temp->next;
        delete next;
    }
}

bool BaseBag::insert(BaseItem *newItem) {
    if (count == capacity)
        return false;

    else if (head == nullptr)
    {
        head = newItem;
        count++;
        return true;
    }
    else
    {
        newItem->next = head;
        head = newItem;
        count++;
        return true;
    }
}

BaseItem *BaseBag::get() {
    if (head == nullptr)
        return nullptr;

    BaseItem *item = head;
    BaseItem *prev = nullptr;

    while ((item != nullptr) && (!item->canUse(obj, nullptr)))
    {
        prev = item;
        item = item->next;
    }

    if (item == nullptr)
        return nullptr;

    if (item != head)
    {
        prev->next = item->next;
        item->next = head;
        BaseItem* temp = head;
        head = item;
        temp->next = prev->next;
        prev->next = temp;
        BaseItem *itemfound = item;
        item->next = nullptr;
    }
    else{
        head = head->next;
        item->next = nullptr;
    }
    count--;
    return item;
}

BaseItem *BaseBag::get(ItemType itemtype)
{
    if (head == nullptr)
        return nullptr;
    BaseItem *item = head;
    BaseItem *prev = nullptr;
    while ((item != nullptr) && (item->getItemType() != itemtype))
    {
        prev = item;
        item = item->next;
    }
    if (item == nullptr)
        return nullptr;

    if (item == head){
        head = head->next;
        item->next = nullptr;
    }
    else
    {
        prev->next = item->next;
        head->next = item->next;
        item->next = head;
        BaseItem *temp = head;
        head = item;
        temp->next = prev->next;
        prev->next = temp;
        item->next = nullptr;
    }
    count--;
    return item;
}

string BaseItem::getItemName()
{
    switch (item_type)
    {
    case ItemType::MAGIC_BOOK:
        return "MagicBook";
    case ItemType::ENERGY_DRINK:
        return "EnergyDrink";
    case ItemType::FIRST_AID:
        return "FirstAid";
    case ItemType::EXCEMPTION_CARD:
        return "ExcemptionCard";
    case ItemType::PASSING_CARD:
        return "PassingCard";
    default:
        return "";
    }
}

string BaseBag::listname() const
{
    string result = "";
    int dem = 0;
    BaseItem *temp = head;
    while (temp != nullptr) {   
        if(dem == 0){
            result +=  temp->getItemName();
                dem++;
                temp = temp->next;
        }
        else{
            result += "," + temp->getItemName();
            temp = temp->next;
        }
    }
    return result;
}

string BaseBag::str() const {
    return "Bag[count=" + to_string(count) + ";"+ listname() + "]";
}

int BaseBag::getCount() const
{
    return count;
}

int BaseBag::getCapacity() const
{
    return capacity;
}
 
SherlockBag::SherlockBag(Sherlock *sherlock) : BaseBag(sherlock, 13) {}
WatsonBag::WatsonBag(Watson *watson) : BaseBag(watson, 15) {}

StudyPinkProgram::StudyPinkProgram(const string& config_file_path){
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
    item = nullptr;
    robot = nullptr;
}

StudyPinkProgram::~StudyPinkProgram(){
    delete config;
    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
    delete arr_mv_objs;
}

bool StudyPinkProgram::isStop() const {
    return (caught || sherlock->getHP() == 0 || watson->getHP() == 0 || sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) ||
       watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()));
} 



void StudyPinkProgram::checkEncounterOfSherlock(Sherlock* sherlock, SherlockBag& sherbag, WatsonBag& watsbag){
    for (int j = 0; j < arr_mv_objs->size(); j++){
        MovingObject* object = arr_mv_objs->get(j);
        if((object != sherlock) && (object != watson) && (object != criminal)){
            if(sherlock->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                Robot* robot = dynamic_cast<Robot*>(object);
                if(robot){
                    SherlockHandleRobot(sherlock, robot, sherbag);
                }
            }
        }
        else if(object == watson){
            if(sherlock->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                BaseItem* item = nullptr;
               while((item = sherbag.get(PASSING_CARD)) != nullptr){
                    watsbag.insert(item);
               }
               while((item = watsbag.get(EXCEMPTION_CARD)) != nullptr){
                    sherbag.insert(item);
               }
            }
        }
        else if(object == criminal){
            if(sherlock->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                caught = true;
            }
        }
    }
}

void StudyPinkProgram::SherlockHandleRobot(Sherlock* sherlock, Robot* robot, SherlockBag& sherbag){
    BaseItem* item = robot->getItem();
    BaseItem* needitem = sherbag.get(EXCEMPTION_CARD);
    ExcemptionCard *excard =nullptr;
    if(needitem){
        excard = dynamic_cast<ExcemptionCard*>(sherbag.get(EXCEMPTION_CARD));
    }
    if(robot->getRobotType() == S){
        if(sherlock->getEXP() > 400){
            if(item){
                sherbag.insert(item);
            }
        }
        else{
            if(excard && excard->canUse(sherlock, robot)){
                excard->use(sherlock, robot);
            }
            else {
                sherlock->setEXP(sherlock->getEXP() * 0.9 + 0.999);
            }
        }
    }
    else if(robot->getRobotType() == W){
        if(item){
            sherbag.insert(item);
        }
    }
    else if (robot->getRobotType() == SW){
        if(sherlock->getEXP() > 300 && sherlock->getHP() > 335){
            if(item){
                sherbag.insert(item);
            }   
        }
        else{
            if(excard && excard->canUse(sherlock, robot)){
                excard->use(sherlock, robot);
            }
            else {
                sherlock->setEXP(sherlock->getEXP() * 0.85 + 0.999);
                sherlock->setHP(sherlock->getHP() * 0.85 + 0.999);
            }
        }
    }
    else if(robot->getRobotType() == C){
        if(sherlock->getHP() > 500){
            caught = true;
        }
        else{
            sherbag.insert(item);
        }
    }
    restoreHPandEXP(sherlock, sherbag);
}

void StudyPinkProgram::checkEncounterOfWatson(Watson* watson, SherlockBag& sherbag, WatsonBag& watsbag){
    for (int j = 0; j < arr_mv_objs->size(); j++){
        MovingObject* object = arr_mv_objs->get(j);
        if((object != sherlock) && (object != watson) && (object != criminal)){
            if(watson->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                Robot* robot = dynamic_cast<Robot*>(object);
                if(robot){
                    WatsonHandleRobot(watson, robot, watsbag);
                }
            }
        }
        else if(object == sherlock){
            if(watson->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                BaseItem* item = nullptr;
               while((item = watsbag.get(PASSING_CARD)) != nullptr){
                    sherbag.insert(item);
               }
               while((item = sherbag.get(EXCEMPTION_CARD)) != nullptr){
                    watsbag.insert(item);
               }
            }
        }
        else if (object == criminal){
            if(watson->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                caught = true;
            }
        }
    }
}

void StudyPinkProgram::WatsonHandleRobot(Watson* watson, Robot* robot, WatsonBag& watsbag){
    BaseItem* item = robot->getItem();
    BaseItem* needitem = watsbag.get(PASSING_CARD);
    PassingCard *passcard =nullptr;
    if(needitem){
        passcard = dynamic_cast<PassingCard*>(watsbag.get(PASSING_CARD));
    }

    if(passcard && passcard->canUse(watson, robot)){
        passcard->use(watson, robot);
    }
    else {
        if(robot->getRobotType() == S){}
        else if(robot->getRobotType() == W){
            if(watson->getHP()>350){    
                if(item){
                    watsbag.insert(item);
                }
            }
            else {
                watson->setHP(watson->getHP() * 0.95 + 0.999);
            }
        }
        else if(robot->getRobotType() == SW){
            if(watson->getEXP() > 600 && watson->getHP() > 165){
                if(item){
                    watsbag.insert(item);
                }
            }
            else {
                watson->setEXP(watson->getEXP() * 0.85 + 0.999);
                watson->setHP(watson->getHP() * 0.85 + 0.999);
            }
        }
        else if(robot->getRobotType() == C){
            if(item){
                watsbag.insert(item);
            }
        }
    }
    restoreHPandEXP(watson, watsbag);
}

void StudyPinkProgram::checkEncounterOfRobot(Robot* robot, SherlockBag& sherbag, WatsonBag& watsbag){
    for (int j = 0; j < arr_mv_objs->size(); j++){
        MovingObject* object = arr_mv_objs->get(j);
        if((object != robot) && (object != criminal)){
            if(robot->getCurrentPosition().isEqual(object->getCurrentPosition().getRow(), object->getCurrentPosition().getCol())){
                if(object == sherlock){
                    SherlockHandleRobot(sherlock, robot, sherbag);
                }
                else if(object == watson){
                    WatsonHandleRobot(watson, robot, watsbag);
                }
            }
        }
    }
}

void StudyPinkProgram::restoreHPandEXP(Character* character, SherlockBag& sherbag){
    int capacity = sherbag.getCapacity();
    int count = 0;
    BaseItem** tempStore = new BaseItem*[capacity];
    bool used = false;
    while(!used){
        BaseItem* usableitem = sherbag.get();
        if(usableitem){
            if (usableitem->getItemType() == MAGIC_BOOK || usableitem->getItemType() == ENERGY_DRINK || usableitem->getItemType() == FIRST_AID) {
                usableitem->use(character, nullptr);
                used = true;
            }
            else {
                tempStore[count] = usableitem;
                count++;
                if(count == capacity){
                    break;
                }
            }
        }
        else
            break;
    }
    for (int i = 0; i < count; i++){
        sherbag.insert(tempStore[i]);
    }
    delete[] tempStore;
}

void StudyPinkProgram::restoreHPandEXP(Character* character, WatsonBag& watsbag){
    int capacity = watsbag.getCapacity();
    int count = 0;
    BaseItem** tempStore = new BaseItem*[capacity];
    bool used = false;
    while(!used){
        BaseItem* usableitem = watsbag.get();
        if(usableitem){
            if (usableitem->getItemType() == MAGIC_BOOK || usableitem->getItemType() == ENERGY_DRINK || usableitem->getItemType() == FIRST_AID) {
                usableitem->use(character, nullptr);
                used = true;
            }
            else {
                tempStore[count] = usableitem;
                count++;
                if(count == capacity){
                    break;
                }
            }
        }
        else
            break;
    }
    for (int i = 0; i < count; i++){
        watsbag.insert(tempStore[i]);
    }
    delete[] tempStore;

}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
