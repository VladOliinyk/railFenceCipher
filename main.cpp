#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

/* Global variables that are needed for output. */
int _KEY;
string _CRYPTOGRAM;
string _ORIGINAL_TEXT;

/* Function that asking user what he wants to do: ENcode or DEcode something. */
bool needToDecode();

/*
 * Encoding function.
 * Result: global variables are filled with correct data.
 */
void encoding();

/* Getting input string by asking user. */
string getInputString();

/* Getting key by asking iser. */
int getKey();

/* Delete spaces from incoming string.
   Return: string without spaces. */
string deleteSpaces(string str);

/* General encoding function.
   Here happen all the logic (a dirty job ;) ). */
string encode(string str, int key);

/*
 * Decoding function.
 * Result: global variables are filled with correct data.
 */
void decoding();

/* General decoding function.
   Here happen all the logic (a dirty job ;) ). */
string decode(string cryptogram);

/* Function that asking user about correctly decoded string. */
bool isOriginalTextCorrect(string originalText);

/* Function that print final results. */
void printResult(string originalString, int key, string cryptogram);


// Main function.
int main() {
    if (!needToDecode()) {
        encoding();
    } else {
        decoding();
    }
    printResult(_ORIGINAL_TEXT, _KEY, _CRYPTOGRAM);
    return 0;
}

// Check what need to do by asking user.
// @return choise - boolean value.
bool needToDecode() {
    while (true) {
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

// Main encoding method.
// @return str - encoded string (cryptogram)
void encoding() {
    _ORIGINAL_TEXT = getInputString();
    _KEY = getKey();
    _ORIGINAL_TEXT = deleteSpaces(_ORIGINAL_TEXT);
    _CRYPTOGRAM = encode(_ORIGINAL_TEXT, _KEY);
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

// Getting key.
// @return key - key that produced by user.
int getKey() {
    int key;
    cout << "Enter the key: " << endl << " > ";
    cin >> key;
    return key;
}

// Deleting spaces in input string;
// @param str - input string.
// @return newString - new string, the same to 'str' but without spaces;
string deleteSpaces(string str) {
    vector<char> vec;
    for (int i = 0; i < (int) str.size(); i++) {
        if (str.at(i) != ' ') {
            vec.push_back(str.at(i));
        }
    }

    string newString(vec.begin(), vec.end());
    return newString;
}

// General encoding method.
// @param str - a string that need to encode.
// @param key - a key that need to use to encode.
// @return cryptogram - an encoded string.
string encode(string str, int key) {

    int size = str.size();

    // declare array
    char arr[key][size];
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = ' ';
        }
    }

    // fill array
    int row = key-1;
    bool switcher = false;
    for (int i = 0; i < size; i++) {

        arr[row][i] = str.at(i);

        //vertical "ricochet"
        if ( row < 1 ) {
            switcher = !switcher;
        }

        //bottom "ricochet"
        if ( (row >= key - 1) && (i != 0) ) {
            switcher = !switcher;
        }

        switcher ? row++ : row--;
    }

    // print array
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < size; j++) {
            cout << " " << arr[i][j] << "";
        }
        cout << endl;
    }

    // Convert the two-dimensional array to string.
    string cryptogram = "";
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < size; j++) {
            cryptogram.push_back(arr[i][j]);
        }
    }

    _CRYPTOGRAM = deleteSpaces(cryptogram);

    return _CRYPTOGRAM;
}

// Main decoding method.
// @return str - decoded string (original text)
void decoding() {
    _CRYPTOGRAM = getInputString();
    _CRYPTOGRAM = deleteSpaces(_CRYPTOGRAM);
    _ORIGINAL_TEXT = decode(_CRYPTOGRAM);
}

// General encoding method.
// @param str - a string that need to decode.
// @return XXXXX - decoded string (original text)
string decode(string cryptogram) {
    int size = cryptogram.size();
    string originalText;

    int key = 2; // presumed key (suppose that key = 2)

    while(true) {

        // clearing our presumed originalText string
        originalText = "";

        // declare array [key*size] size
        // and fill it ' ' (space) characters
        char arr[key][size];
        for (int i = 0; i < key; i++) {
            for (int j = 0; j < size; j++) {
                arr[i][j] = ' ';
            }
        }

        // fill array in correct positions
        // fill array by correct "snake" for presumed key
        //  | after that filling we have markers in right places
        //  | and later we can replace this marker to right letters
        int rowX = key-1;
        bool switcherX = false;
        for (int i = 0; i < size; i++) {

            arr[rowX][i] = '1';

            //vertical "ricochet"
            if ( rowX < 1 ) {
                switcherX = !switcherX;
            }
            //bottom "ricochet"
            if ( (rowX >= key - 1) && (i != 0) ) {
                switcherX = !switcherX;
            }

            switcherX ? rowX++ : rowX--;
        }

        // replace not space characters (our markers)
        // by the letters from cryptogram
        int myChar = 0;
        for (int i = 0; i < key; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][j] != ' ') {
                    arr[i][j] = cryptogram.at(myChar);
                    myChar++;
                }
            }
        }

        // Print array
        for (int i = 0; i < key; i++) {
            for (int j = 0; j < size; j++) {
                cout << " " << arr[i][j] << "";
            }
            cout << endl;
        }

        // Convert the two-dimensional array to the string.
        int row = key-1;
        bool switcher = false;
        for (int i = 0; i < size; i++) {

            originalText.push_back(arr[row][i]);

            // vertical "ricochet"
            if ( row < 1 ) {
                switcher = !switcher;
            }

            // bottom "ricochet"
            if ( (row >= key - 1) && (i != 0) ) {
                switcher = !switcher;
            }

            switcher ? row++ : row--;
        }


        if (key > size) {
            cout << "Hmm.. Maybe comething wrong?" << endl <<
                    "Try again later." << endl;
            // close the program
            exit(1);
        }
        // Check the result by asking user.
        if (!isOriginalTextCorrect(originalText)) {
            // if text decoded correctly go out from cycle
            break;
        } else {
            // if text decoded incorrectly
            // increment the presumed key
            // and repeat decoding with else presumed key
            key++;
        }
    }

    _KEY = key;
    _CRYPTOGRAM = cryptogram;

    return originalText;
}

// Check for correct decoding by asking user.
// @param originalText - variant of decoded string.
// @return choise - boolean value.
bool isOriginalTextCorrect(string originalText) {
    while (true) {
        char choise;
        cout << "Please check the decoded text: " << endl <<
                "Original text is: [ " << originalText << " ] ?" << endl <<
                " enter '0' - if you think that text is decoded correctly." << endl <<
                " enter '1' - if you think that text is decoded incorrectly." << endl <<
                " > ";
        cin >> choise;
        if (choise != '1' && choise != '0') {
            continue;
        }
        return choise == '1' ? true : false;
    }
}

// Print the final results;
// @param originalString - the original text string (human-readable text / coherent text)
// @param key - the key that was used for encoding/decoding.
// @param cryptogram - the cryptotext (encrypted text / ciphertext)
void printResult(string originalString, int key, string cryptogram) {
    cout << endl << endl <<
            " So: " << endl <<
            " Original text is: [ " << originalString << " ]" << endl <<
            " Cryptogram is: [ " << cryptogram << " ]" << endl <<
            " Key = " << key << endl << endl;
}
