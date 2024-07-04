#include <iostream>
#include <string>

using namespace std;

int Table[10][11] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {2,0,0,0,0,0,0,0,0,0,0},
    {0,3,0,0,0,0,0,0,0,0,0},
    {0,0,4,0,0,0,0,0,0,0,0},
    {0,0,0,5,0,0,0,0,0,0,0},
    {0,0,0,0,4,6,0,0,0,0,0},
    {0,0,0,0,0,0,7,0,0,0,0},
    {0,0,0,5,0,0,0,8,9,0,0},
    {0,0,0,0,0,0,7,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,10,0},
};
int TableId[2][4] = {{2, 0, 0, 0},{2, 2, 10, 0}};
int TableNum[3][4] = {{2, 3, 0, 0}, {0, 3, 0, 0}, {10, 3, 10, 0}};
const string words[] = {"case", "of", "else", "end"};
const char Razd[] = {',', ':', ';', ' '};

bool isOperator(string& str, string& rest);

bool isLatin(char symbol){
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}

bool isNumber(char symbol){
    return (symbol >= '0' && symbol <= '9');
}

bool isSign(char symbol){
    return (symbol == '+' || symbol == '-');
}

bool isRazd(char symbol){
    for (int i = 0; i < 10; i++){
        if (Razd[i] == symbol) return true;
    }
    return false;
}

bool isEqual(string str, int ind = 0) {
    string part = str.substr(ind, 2);
    if (part == ":=")
        return true;
    return false;
}

int isWord(string& str) {
    string part = "";
    int i = 0;
    while(isLatin(str[i])) {
        part += str[i];
        i++;
    }
    if (part == "case" && str[i] == ' ')
        return 1;
    else if (part == "of" && str[i] == ' ')
        return 2;
    else if (part == "else" && str[i] == ' ')
        return 3;
    else if (part == "end")
        return 4;
    else
        return 0;
}

void removeExtra(string& str, char symbol = ' ') {
    int i = 0;
    while(str[i] == symbol)
        i++;
    str = str.substr(i);
}

int whichRazd(string& str, string& rest) {
    char symbol;
    removeExtra(str);
    symbol = str[0];
    switch (symbol)
    {
    case ',':
        str.erase(0, 1);
        rest += ",";
        return 1;
        break;
    case ':':
        str.erase(0, 1);
        rest += ":";
        return 2;
        break;
    case ';':
        str.erase(0, 1);
        rest += ";";
        return 3;
        break;
    default:
        return 0;
        break;
    }
}

bool isNumber(string& str, string& rest){
    string number = "";
    int state = 1, ind = 0, col;
    while (state!=0 && state!=10) {
        if (isSign(str[ind])) 
            col = 0;
        else if (isNumber(str[ind])) 
            col = 1;
        else if (isRazd(str[ind])) 
            col = 2;
        else 
            col = 3;

        state = TableNum[state-1][col];
        if (state != 0 && state != 10) {
            number += str[ind];
            ind++;
        }
    }
    if (state == 10) {
        cout << "Number = " << number << endl;
        rest += "N";
        str.erase(0, ind);
        return ind;
    }
    return false;
}

bool isId(string& str, string& rest){
    removeExtra(str, ' ');
    string s = "";
    int state = 1, ind = 0, col;
    while (state!=0 && state!=10) {
        if (isLatin(str[ind])) 
            col = 0;
        else if (isNumber(str[ind]))
            col = 1;
        else if (isRazd(str[ind]))
            col = 2;
        else 
            col = 3;
        
        state = TableId[state-1][col];
        if (state != 0 && state != 10) {
            s += str[ind];
            ind++;
        }
    }
    
    if (state == 10 && s != "") {
        cout << "Identify = " << s << endl;
        rest += "Id";
        str.erase(0, ind);
        return true;
    } 
    return false;
}

bool isAssign(string& str, string& rest) {
    bool result = false;
    if (isId(str, rest)) {
        removeExtra(str, ' ');
        if (str != "")
            if (str.substr(0, 2) == ":=") {
                str.erase(0, 2);
                rest += ":=";
                removeExtra(str, ' ');
                if (isId(str, rest) || isNumber(str, rest)) {
                    removeExtra(str);
                    if (str[0] == ';') {
                        str.erase(0, 1);
                        rest += ";";
                        result = true;
                    } else {
                        cout << "error: expected ';'" << endl;
                    }
                }
            }
    }
    if (!result)
        cout << "error in assignment operator" << endl;
    return result;
}

bool isCase(string& str, string& rest) {
    bool result = true;
    string part = "";
    int n, state = 1, i = 0, col = 10;
    while (state != 0 && state != 10 && str != "") {
        removeExtra(str);
        if (state == 6 || state == 8) {
            if (isOperator(str, rest)) {
                col = 6;
            }
        } else {
            n = isWord(str);
            if (n)
                switch (n) {
                case 1:
                    col = 0;
                    rest += "case_";
                    str.erase(0, 5);
                    break;
                case 2:
                    col = 2;
                    rest += "_of_";
                    str.erase(0, 3);
                    break;
                case 3:
                    col = 7;
                    rest += "_else_";
                    str.erase(0, 5);
                    break;
                case 4:
                    col = 8;
                    rest += "_end";
                    str.erase(0, 3);
                    break;
                }
            else if (isId(str, rest)) 
                col = 1;
            else if (isNumber(str, rest))
                col = 3;
            else {
                n = whichRazd(str, rest);
                switch (n) {
                case 1:
                    col = 4;
                    break;
                case 2:
                    col = 5;
                    break;
                case 3:
                    col = 9;
                    break;
                }
            }
        }
        state = Table[state][col];
        if (state == 10)
            result = true;
    }
    return result;
}

bool isOperator(string& str, string& rest) {
    string part = "";
    int n;
    bool result = true;
    removeExtra(str, ' ');
    n = isWord(str);
    if(n == 1) {
        result = isCase(str, rest);
    }
    else if (n == 0) {
        result = isAssign(str, rest);
    }
    return result;
}

int main() {
    std::string str;
    std::string scan = "";
    bool result;

    cout << "Enter string: " << endl;
    getline(cin, str);
    result = isOperator(str, scan);
    cout << "Scan string is: " << scan << endl;
    removeExtra(str);
    if (result && str == "") {
        cout << "String is correct!\n";
    }
    else {
        cout << "Error: invalid input";
    }
}