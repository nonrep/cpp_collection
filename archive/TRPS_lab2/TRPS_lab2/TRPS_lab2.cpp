#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//нет close();
//sin(x) 
//R не объявлена, имелось P
//нет выхода
// перепутан порядок комманд на выбор

int main() {
    ifstream rs;
    ofstream ws;
    string Fname, S; bool Fc, FOpenOK; unsigned char P, r;
    int i;

    Fc = true;
    while (Fc) {
        cout << "Menu:\n1. Read\n2. Append\n3. Create\n4. Exit\n" << endl;
        cout << "Input num: " << flush; cin >> P;
        switch (P) {
        case '1': {
            cout << "Name file for read: " << flush;
            cin >> Fname;
            rs = ifstream(Fname);
            if (rs)
            {
                while (getline(rs, S)) cout << S << endl;
            }
            else
                cout << Fname << " - not exist!" << endl;
            rs.close();
            break;
        }
        case '2': {
            cout << "Name file for append: " << flush;
            cin >> Fname;
            rs = ifstream(Fname);
            if (rs)
            {
                ws = ofstream(Fname, ios_base::app);
                cout << "Write line." << endl; 
                cin >> S;
                ws << S;
                ws.close();
            }
            else 
                cout << Fname << " - not exist!" << endl;
            rs.close();
            break;
        }
        case '3': {
            cout << "Name file for create: " << flush;
            cin >> Fname;
            ws.open(Fname);
            ws.close();
            break;
        }
        case '4': 
            Fc = false;
            break;
            
        }
    }
}
