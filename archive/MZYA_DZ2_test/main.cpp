#include <iostream>
#include <string>

using namespace std;

int Table[14][14] = {
    {2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 10, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 5, 0, 0},
    {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 50, 0},
    {0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 13, 0, 0, 12, 14, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 12, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 11, 50, 0}
};
int Table_Id[2][4] = {{2, 0, 0, 0},{2, 2, 10, 0}};
int Table_Num[3][4] = {{2, 3, 0, 0}, {0, 3, 0, 0}, {10, 3, 10, 0}};
const std::string Sls[3] = {"const", "array", "of integer"};
const char Razd[] = {'(',')', '[', ']', ',', '.', ';', ':', '='};

bool isLatin(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isNumber(char c){
    return (c >= '0' && c <= '9');
}

bool isSign(char c){
    return (c == '+' || c == '-');
}

bool isRazd(char s){
    for (int i = 0; i < 10; i++){
        if (Razd[i] == s) return true;
    }
    return false;
}

void removeChars(std::string &str, const char *c){
    size_t pos = str.find(c);
    while (pos != string::npos) {
        str.replace(pos,1,"");
        pos = str.find(c, pos);
    }
}

void removeExtraChars(std::string &str, const char *c) {
    int index = 0;
    string res;
    res.assign(2, *c);
    while ((index = str.find(res, index)) != std::string::npos) {
        str.replace(index, 2, c);
    }
}

int NUM(string copy_str){
    string str = copy_str;
    string number = "";
    int state = 1, ind = 0, col;
    while (state!=0 && state!=10) {
        if (isSign(str[ind])) col = 0;
        else if (isNumber(str[ind])) col = 1;
        else if (isRazd(str[ind])) col = 2;
        else col = 3;

        state = Table_Num[state-1][col];
        if (state != 0 && state != 10) {
            number += str[ind];
            ind++;
        }
    }
    if (state == 10) {
        cout << "Number = " << number << endl;
        return ind;
    } else
        if (state == 0) {
            if (col == 0) {
                cout << "Two signs side by side..." << endl;
            } else  if (col == 1) {
                cout << "No numbers in the string..." << endl;
            }
            return 0;
        } else {
            cout << "Number waits..." << str << endl;
            return 0;
        }
}

int ID(std::string str){
    string s = "";
    int state = 1, ind = 0, col;
    while (state!=0 && state!=10) {
        if (isLatin(str[ind])) col = 0;
        else if (isNumber(str[ind])) col = 1;
        else if (isRazd(str[ind])) col = 2;
        else col = 3;
        
        state = Table_Id[state-1][col];
        if (state != 0 && state != 10) {
            s += str[ind];
            ind++;
        }
    }
    
    if (state == 10 && s != "") {
        cout << "Identify = " << s << endl;
        return ind;
    } else if (state == 0) {
        cout << "Wrong symbol *" << str[ind] << '*' << endl;
        return 0;
    } else {
        cout << "Identifier waits..." << str << endl;
        return 0;
    }
}

void skip(std::string &str){
    if (str.substr(0, 1) == ":") str.erase(0, 1);
    while (!isRazd(str[0])){
        str.erase(0, 1);
    }
}

void printError(string Scan, int ind){
    cout << "\t_ERROR_MESSAGE_" << endl;
    cout << "\tScanner string:" << ind << ": error: expected wrong '" << Scan[ind] << "' token" << endl;
    cout << "\t\t|" << Scan << endl;
    cout << "\t\t|";
    for (int i = 0; i < ind; i++) {cout << " ";}
    cout << "^" << endl;
}

int scanner(std::string &str, std::string &rest){
    // removeSpaces(str);
    bool flag_p = true, flag_sc1 = true, flag_sc2 = true;
    rest = "";
    std::string part = "";
    int n, pos=0;
    part = str.substr(0, 6);

    removeExtraChars(str, " ");
    if (part == "const " || part == "Const "){
        rest += "c";
        str.erase(0, 5);
    } else {skip(str);}

    removeChars(str, " ");

    n = ID(str);
    if (n != 0) {
        rest += "V";
        str.erase(0, n);
    } else {skip(str);}

    part = str.substr(0, 6);
    if (part == ":array" || part == ":Array"){
        rest += "a";
        str.erase(0, 6);
    } else {cout << str << endl; skip(str); cout << str << endl;}

    // if (!DDcheck(str, ".")) {flag_p = false;}
    // removeExtraChars(str, ".");

    part = str.substr(0, 1);
    int balance = 0;
    while (str != ""){
        if (str.substr(0, 2) == "..") {
            rest += "*";
            str.erase(0,2);
        }
        if (str.substr(0, 9) == "ofinteger"){
            rest += "i";
            str.erase(0,9);
        } else if (isRazd(str[0])) {
            if (str.substr(0, 1) == "(") balance++;
            else if (str.substr(0, 1) == ")") balance--;
            rest += str[0];
            str.erase(0,1);
            part = str.substr(0, 1);
        } else {
            n = NUM(str);
            if (n != 0) {
                rest += "N";
                str.erase(0, n);
            }
        }
    }

    rest += str[0];
    str.erase(0,1);
    return balance;
}

int main() {
    std::string Str;// = "Const A7867:array[1..3,-5..-4] of integer=((6, -6),(59,0),(89,30));";
    std::string Scan;
    std::string Vx = "caiVN[]()=*,;";

    cout << "Enter string: " << endl;
    getline(cin, Str);
    int balance = scanner(Str, Scan);
    cout << "Scan string is: " << Scan << endl;
    
    int q, pos, ind = 0;
    if (Scan.substr(0, 1) == "c") q = 1; else q = 2;
    while (q != 0 && q != 50) {
        pos = Vx.find(Scan[ind]);
        q = Table[q-1][pos];
        // cout << "-------" << endl;
        // cout << Scan[ind] << endl;
        // cout << "q = " << q << endl;
        // cout << "pos = " << pos << endl;
        ind++;
    }

    if (q == 50) cout << "String is correct!\n";
    else {
        ind -= 1;
        printError(Scan, ind);
        // cout << "balance = " << balance << endl;
        if (balance < 0) {
            ind = Scan.rfind(")");
            printError(Scan, ind);
        }
        else if (balance > 0) {
            ind = Scan.find("(");
            printError(Scan, ind);
        }
    }

// const 3a: array of integer;
// const d: aray of integer;
// connst d: array of integer;
// d: array[1..3] of integer;
// Const ABC: Aarray[1..3] of integer = ();
// Const A7867:array[1..3,-5..-4] of integer=((6, -6),(59,0),(89,30));
// Const array:array[1..3,-5..-4, 3..6] of integer = (((6, -6),(59,0),(89,30)));
    return 0;
}
