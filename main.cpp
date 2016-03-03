#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool decode() {
    while (true) {
        system("cls");
        char choise;
        cout << "Please choose what to do:" << endl <<
                " enter '0' - if you want to encode some word" << endl <<
                " enter '1' - if you want to decode some word" << endl <<
                " > ";
        cin >> choise;
        if (choise != '1' && choise != '0') {
            continue;
        }
        return choise == '1' ? true : false;
    }
}

string getInputString();
string deleteSpaces(string str);

/* ENCODING PART */

// General encoding method.
void encoding() {
    string str = getInputString();
    cout << ":" << str << endl;
    str = deleteSpaces(str);
    cout << ":" << str << endl;
}

// Getting some string.
// @return str - string that produced by user.
string getInputString() {
    string str;
    cout << "Enter the word what you want to encode: " << endl << " > ";
    cin.ignore(); // just for sync io streams
    getline(cin, str);
    return str;
}

// Deleting spaces in input string;
// @param str - input string.
// @return newString - new string, the same to 'str' but without spaces;
string deleteSpaces(string str) {
    vector<char> vec;
    for (int i = 0; i < str.size(); i++) {
        if (str.at(i) != ' ') {
            vec.push_back(str.at(i));
        }
    }
    string newString(vec.begin(), vec.end());
    return newString;
}

int main()
{
    if (!decode()) {
        encoding();
    } else {
        //decoding();
    }
    return 0;
}

