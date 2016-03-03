#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool decode() {
    while (true) {
        //system("clear");
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

int getKey() {
    int key;
    cout << "Enter the key: " << endl << " > ";
    cin >> key;
    return key;
}

string encode(string str, int key);

/* ENCODING PART */
// General encoding method.
void encoding() {
    string str = getInputString();
    int key = getKey();
    cout << "user string:" << str << endl;
    str = deleteSpaces(str);
    cout << " new string:" << str << endl;
    str = encode(str, key);
    // ...
}

string encode(string str, int key) {
       string cryptogram = str;
       int size = cryptogram.size();

       // declare array
       char arr[key][size];
       for (int i = 0; i < key; i++) {
           for (int j = 0; j < size; j++) {
              arr[i][j] = ' ';
           }
       }

       // fill array
       int row = key;
       bool switcher = 0;
       for (int i = 0; i < size; i++) {
           //arr[key - (i % key) - 1][i] = cryptogram.at(i);
           arr[row][i] = cryptogram.at(i);
           if ((row == key) && (row == 0)) {
             switcher = true;
           } else {
             switcher = false;
           }
           switcher ? row++ : row--;
       }

       // print array
       for (int i = 0; i < key; i++) {
           for (int j = 0; j < size; j++) {
               cout << " " << arr[i][j] << " ";
           }
           cout << endl;
       }
    cin;
       return cryptogram;
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

int main() {
    if (!decode()) {
        encoding();
    } else {
        //decoding();
    }
    //system("pause");
    return 0;
}
