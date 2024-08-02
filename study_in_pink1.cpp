#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int adjustEXP(int& exp) {
    if (exp > 600) {
        exp = 600;
    }
    else if (exp < 0) {
        exp = 0;
    }
    return exp;
}
int adjustHP(int& HP) {
    if (HP > 666) {
        HP = 666;
    }
    else if (HP < 0) {
        HP = 0;
    }
    return HP;
}
int adjustM(int& M) {
    if (M > 3000) {
        M = 3000;
    }
    else if (M < 0) {
        M = 0;
    }
    return M;
}

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    adjustEXP(exp2);
    adjustEXP(exp1);
    //moi them
    if (e1 < 0 || e1>99) {
        return -99;
    }
    //moi them o tren
    int E1 = e1;
    if (e1 >= 0 && e1 <= 3)
    {
        if (e1 == 0) {
            exp2 += 29;
        }
        else if (e1 == 1) {
            exp2 += 45;
        }
        else if (e1 == 2) {
            exp2 += 75;
        }
        else if (e1 == 3) {
            exp2 += 29 + 45 + 75;
        }
        adjustEXP(exp2);
        int D = e1 * 3 + exp1 * 7;
        if (D % 2 == 0) {
            
           // exp1 = float((exp1 + float(D / 200) + 0.999));
            float Dd = static_cast<float>(D) / 200;
            exp1 += Dd + 0.999;
        }
        else {
            float Dd = static_cast<float>(D) / 100;
            
            exp1 = exp1 - Dd + 0.999;
            
        }
        adjustEXP(exp1);
    }
    else if (e1 >= 4 && e1 <= 99) {
        if (e1 >= 4 && e1 <= 19) {
            float A = static_cast<float>(E1) / 4 + 19;
            e1 = A + 0.999;
            exp2 += e1;
            //   adjustEXP(exp2);
        }
        else if (e1 >= 20 && e1 <= 49) {
            float A = static_cast<float>(E1) / 9 + 21;
            e1 = A+0.999;
            exp2 += e1;

        }
        else if (e1 >= 50 && e1 <= 65) {
            float A = static_cast<float>(E1) / 16 + 17;
            e1 = A + 0.999;
            exp2 += e1;
        }
        else if (e1 >= 66 && e1 <= 79) {
            float A = static_cast<float>(E1) / 4 + 19;
            e1 = A + 0.999;
            exp2 += e1;
            e1 = E1;
            adjustEXP(exp2);
            if (exp2 > 200) {
                float A = static_cast<float>(E1) / 9 + 21;
                e1 = A + 0.999;
                exp2 += e1;

            }
        }
        else if (e1 >= 80 && e1 <= 99) {
            float A = static_cast<float>(E1) / 4 + 19;
            e1 = A + 0.999;
            exp2 += e1;
            e1 = E1;
            adjustEXP(exp2);
            A = static_cast<float>(E1) / 9 + 21;
            e1 = A + 0.999;
            exp2 += e1;
            e1 = E1;
            adjustEXP(exp2);
            if (exp2 > 400) {
                float A = static_cast<float>(E1) / 16 + 17;
                e1 = A + 0.999;
                exp2 += e1;
                adjustEXP(exp2);
                float C = static_cast<float>(exp2) * 1.15;
                exp2 = C + 0.999;
             //   exp2 = ceil(C);
                adjustEXP(exp2);

            }
        }
        exp1 = exp1 - E1;
        adjustEXP(exp1);
    }
    adjustEXP(exp1);
    adjustEXP(exp2);
    
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    adjustEXP(EXP1);
    adjustHP(HP1);
    adjustM(M1);
    if (E2 < 0 || E2 > 99) {
        return -99;
    }
    int P[10] = { 32,47,28,79,100,50,22,83,64,11 };
    int square = sqrt(EXP1);
    int S = 0;

    if (abs(square * square - EXP1) > abs((square + 1) * (square + 1) - EXP1))
     S = (square + 1)*(square+1);
    else   S = square * square;

    double P1, P2, P3;
    double avgP;

    if (EXP1 >= S) {
        P1 = 1;
    }
    else {
        P1 = (static_cast<double>(EXP1) / S + 80) / 123;
    }

    double HalfofM1 = M1 * 0.5;
    int spentmoney = 0;

    if (E2 % 2 != 0) {
        while (spentmoney < HalfofM1) {

            if (HP1 < 200) {

                HP1 = double((HP1 * 1.3) + 0.999);

                M1 = M1 - 150;
                
                spentmoney += 150;
                adjustHP(HP1);
                adjustM(M1);
                if (spentmoney > HalfofM1) {
                    break;
                }
            }
            else {
     
                HP1 = double((HP1 * 1.1) + 0.999);
                M1 = M1 - 70;

                spentmoney += 70;
                adjustHP(HP1);
                adjustM(M1);
                if (spentmoney > HalfofM1) {
                    break;
                }
            }
            

            if (EXP1 < 400) {

                M1 = M1 - 200;
                EXP1 = double((EXP1 * 1.13) + 0.999);

                spentmoney += 200;
                adjustEXP(EXP1);
                adjustM(M1);
                if (spentmoney > HalfofM1) {
                    break;
                }
            }
            else {
                M1 = M1 - 120;
                spentmoney += 120;
                EXP1 = double((EXP1 * 1.13) + 0.999);
                adjustEXP(EXP1);
                adjustM(M1);
                if (spentmoney > HalfofM1) {
                    break;
                }
            }
            
            

            if (EXP1 < 300) {
                M1 = M1 - 100;
                EXP1 = double((EXP1 * 0.9) + 0.999);
                spentmoney += 100;
                adjustEXP(EXP1);
                adjustM(M1);

                if (spentmoney > HalfofM1) {
                    break;
                }
            }
            else if (EXP1 > 300) {
                M1 = M1 - 120;
                spentmoney += 120;
                EXP1 = double((EXP1 * 0.9) + 0.999);
                adjustEXP(EXP1);
                adjustM(M1);

                if (spentmoney > HalfofM1) {
                    break;
                }
            }
            
           

        }
        if (spentmoney > HalfofM1) {

            HP1 = double((HP1 * 0.83) + 0.999);

            EXP1 = double((EXP1 * 1.17) + 0.999);
            adjustHP(HP1);
            adjustEXP(EXP1);
        }

    }
    else if (E2 % 2 == 0) {

        if (M1 > 0) {
            if (HP1 < 200) {
                HP1 = double((HP1 * 1.3) + 0.999);
                M1 = M1 - 150;
                adjustHP(HP1);
                adjustM(M1);
                spentmoney += 150;
            }
            else {
                HP1 = double((HP1 * 1.1) + 0.999);
                M1 = M1 - 70;
                adjustHP(HP1);
                adjustM(M1);
                spentmoney += 70;
                
            }
            if (M1 == 0) {
                HP1 = double((HP1 * 0.83) + 0.999);
                EXP1 = double((EXP1 * 1.17) + 0.999);
                adjustHP(HP1);
                adjustEXP(EXP1);
            }
        }
        if (M1 > 0) {
            if (EXP1 < 400) {
                M1 = M1 - 200;
                EXP1 = double((EXP1 * 1.13) + 0.999);
                adjustEXP(EXP1);
                adjustM(M1);
                spentmoney += 200;

            }
            else {
                M1 = M1 - 120;
                spentmoney += 120;

                EXP1 = double((EXP1 * 1.13) + 0.999);
                adjustEXP(EXP1);
                adjustM(M1);
            }
            if (M1 == 0) {
                HP1 = double((HP1 * 0.83) + 0.999);
                EXP1 = double((EXP1 * 1.17) + 0.999);
                adjustHP(HP1);
                adjustEXP(EXP1);
            }
        }
        if (M1 > 0) {
            if (EXP1 < 300) {
                M1 = M1 - 100;
                EXP1 = double((EXP1 * 0.9) + 0.999);
                spentmoney += 100;
                adjustEXP(EXP1);
                adjustM(M1);

            }
            else if (EXP1 > 300) {
                M1 = M1 - 120;
                EXP1 = double((EXP1 * 0.9) + 0.999);
                spentmoney += 120;
                adjustEXP(EXP1);
                adjustM(M1);
            }
           HP1 = double((HP1 * 0.83) + 0.999);

            EXP1 = double((EXP1 * 1.17) + 0.999);
            adjustHP(HP1);
            adjustEXP(EXP1); 
        }
    }

    square = sqrt(EXP1);

    if (abs(square * square - EXP1) > abs((square + 1) * (square + 1) - EXP1))
        S = (square + 1) * (square + 1);
    else   S = square * square;


    if (EXP1 >= S)   P2 = 1;
    else  P2 = (static_cast<double>(EXP1) / S + 80) / 123;
        

    if (E2 >= 0 && E2 < 10) {
        P3 = static_cast<double>(P[E2]) / 100;
    }

    else if (E2 >= 10) {
        int sum = 0;
        while (E2 != 0) {
            int so = E2 % 10;
            sum += so;
            E2 /= 10;
        }
        P3 = P[sum % 10];
        P3 /= 100;
    }

    if (P1 == 1 && P2 == 1 && P3 == 1)  EXP1 = double((EXP1 * 0.75) + 0.999);
    else {
        avgP = (P1 + P2 + P3) / 3;

        if (avgP < 0.5) {

            HP1 = double((HP1 * 0.85) + 0.999);

            EXP1 = double((EXP1 * 1.15) + 0.999);

        }
        else {

            HP1 = double((HP1 * 0.9) + 0.999);

            EXP1 = double((EXP1 * 1.2) + 0.999);

        }
    }
    adjustEXP(EXP1);
    adjustHP(HP1);
    adjustM(M1);

    return HP1 + EXP1 + M1;
}

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    if (E3 < 0 || E3 > 99) {
        return -99;
    }
    const int row = 10;
    const int col = 10;

    int matrix[row][col] = { 0 };
    int numberofpositive = 0;
    int numberofnegative = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0;j < col;j++) {
            matrix[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            if (matrix[i][j] > E3 * 2) {
                numberofpositive++;
            }
            else if (matrix[i][j] < -E3) {
                numberofnegative++;
            }
        }
    }

    int i = 0;
    if (i < 10) {

        while (numberofpositive != 0) {
            int digit = numberofpositive % 10;
            i += digit;
            numberofpositive /= 10;
        }
    }
    if (i >= 10) {
        numberofpositive = i;
        i = 0;
        while (numberofpositive != 0) {
            int digit = numberofpositive % 10;
            i += digit;
            numberofpositive /= 10;
        }
    }

    int j = 0;
    if (j < 10) {

        while (numberofnegative != 0) {
            int digit = numberofnegative % 10;
            j += digit;
            numberofnegative /= 10;
        }
    }
    if (j >= 10) {
        numberofnegative = j; //cho nay numberofnegative =i ??
        j = 0;
        while (numberofnegative != 0) {
            int digit = numberofnegative % 10;
            j += digit;
            numberofnegative /= 10;
        }
    }

    int Sherlockscore = matrix[i][j];

    if (i <= j) {
        for (int a = 0, b = j - i; (a < row) && (b < col);a++, b++) {
            if (matrix[a][b] > Sherlockscore) {
                Sherlockscore = matrix[a][b];
            }
        }
    }

    else if (i > j) {
        for (int a = i - j, b = 0;(a < row) && (b < col);a++, b++) {
            if (matrix[a][b] > Sherlockscore) {
                Sherlockscore = matrix[a][b];
            }
        }
    }

    for (int a = 0, b = j + i;(a < col) && (b >= 0) && (b < col);a++, b--) {
        if (matrix[a][b] > Sherlockscore) {
            Sherlockscore = matrix[a][b];
        }
    }

    if (i + j > 9) {
        for (int a = i - (9 - j), b = 9; (a < row) && (b >= 0) && (b < col);a++, b--) {
            if (matrix[a][b] > Sherlockscore) {
                Sherlockscore = matrix[a][b];
            }
        }
    }

    int GTLN = abs(matrix[i][j]);
    int returnvalue = 0;
    if (GTLN > Sherlockscore) {
        EXP1 = double((EXP1 * 0.88) + 0.999);
        EXP2 = double((EXP2 * 0.88) + 0.999);
        HP1 = double((HP1 * 0.9) + 0.999);
        HP2 = double((HP2 * 0.9) + 0.999);
        returnvalue = matrix[i][j];
    }
    else if (Sherlockscore >= GTLN) {
        EXP1 = double((EXP1 * 1.12) + 0.999);
        EXP2 = double((EXP2 * 1.12) + 0.999);
        HP1 = double((HP1 * 1.1) + 0.999);
        HP2 = double((HP2 * 1.1) + 0.999);
        returnvalue = Sherlockscore;
    }
    adjustEXP(EXP1);
    adjustEXP(EXP2);
    adjustHP(HP1);
    adjustHP(HP2);

    return returnvalue;
}

bool kytubinhthuong(char c) {
    if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
    {
        return true;
    }
    return false;
}
bool kytudacbiet(char c) {
    if ((c == '@') || (c == '#') || (c == '%') || (c == '$') || (c == '!')) {
        return true;
    }
    return false;
}

// Task 4
int checkPassword(const char* s, const char* email) {
    int taivitri = strchr(email, '@') - email;
    string se = string(email, taivitri);

    if (strlen(s) < 8) {
        return -1;
    }
    else if (strlen(s) > 20) {
        return -2;
    }

    const char* sei = strstr(s, se.c_str());

    if (sei != nullptr) {

        return -(300 + static_cast<int>(sei - s));
    }

    for (int i = 0; i < strlen(s) - 2; i++)
    {
        if ((s[i] == s[i + 1]) && (s[i] == s[i + 2])) {
            return -(400 + i);
        }
    }

    bool cokytudacbiet = false;

    for (const char* check = s; *check != '\0'; *check++) {
        if (!kytubinhthuong(*check)) {
            if (kytudacbiet(*check)) cokytudacbiet = true;

            else return static_cast<int>(check - s);
        }
    }

    if (cokytudacbiet == false) {
        return -5;
    }

    return -10;
}

int checkPassword(const char * s, const char * email) {
    string se="";
    for (int i=0;i<strlen(email);i++)
        {
            if (email[i]=='@')  break;
            else se.push_back(email[i]);
        }
    if (strlen(s)<8)   return -1;
    if (strlen(s)>20)   return -2;
    
    if (se=="")  return -300;
    for (int i=0;i<strlen(s);i++)
        if (s[i]==se[0]){
            bool check=true;
            for (int j = 1; j < se.length(); j++)
                if (s[i+j] != se[j]) {
                    check=false; 
                    break;
                    }
                   if(check) return -(300+i);}

    for (int i = 0; i < strlen(s) - 2; i++)
        if (s[i] == s[i + 1] && s[i] == s[i + 2])  return -(400+i);

    bool checkktdb=false;
    for (int i=0;i<strlen(s);i++)
        if (s[i]=='@' || s[i]=='#' || s[i]=='$' || s[i]=='%' || s[i]=='!'){
            checkktdb=true; 
            break;
        }

    if (!checkktdb)  return -5;

    for (int i=0;i<strlen(s);i++)
        if (s[i]=='@' || s[i]=='#' || s[i]=='$' || s[i]=='%' || s[i]=='!'
        || s[i]>='a' && s[i]<='z' || s[i]>='A' && s[i]<='Z' || s[i]>='0' && s[i]<='9')
        {}
        else return i;
    return -10;
}


// Task 5
int findCorrectPassword(const char* arr_pwds[], int num_pwds) {
    const char* mostFrequentPass = nullptr;
    int countmax = 0;

    for (int i = 0; i < num_pwds; ++i) {
        const char* pass = arr_pwds[i];
        int count = 0;
        for (int j = 0; j < num_pwds; ++j) {
            if (i != j && strcmp(pass, arr_pwds[j]) == 0) {
                count++;
            }
        }

        if (count > countmax || (count == countmax && (mostFrequentPass == nullptr || strlen(pass) > strlen(mostFrequentPass)))) {
            mostFrequentPass = pass;
            countmax = count;
        }
    }

    for (int i = 0; i < num_pwds; ++i) {
        if (strcmp(arr_pwds[i], mostFrequentPass) == 0) {
            return i;
        }
    }
    return -1;
    
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////