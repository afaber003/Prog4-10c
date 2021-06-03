#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#include "HashTable.h"
#define test cout << "Here" << endl;

using namespace std;

struct token {
    int frequency = 1;
    string word = "";
};

bool operator<(token lefthandside, token righthandside) {
    if (lefthandside.frequency < righthandside.frequency) {
        return true;
    } else
        return false;
}

//helper function
vector<token*> seperateWords(string fileInput);

// Encrypt with file input to file output
void encrypt(string fileInputName, string fileOutputName, string encoderdatafile, string decoderdatafile);

// Decrypt with file input and file output
void decrypt(string fileInputName, string fileOutputName) {}

////////////////////////////////////
//        MAIN
////////////////////////////////////

int main() {
    char input = ' ';

    cout << "Type 'e' to encrypt or 'q' to exit: ";

    // basically the menu
    while (tolower(input) != 'q') {
        cin >> input;

        // Encrypt from file to file
        if (input == 'e') {
            cout << "Enter the name of the input file: ";
            string tempinput = "";
            cin >> tempinput;
            cout << "Enter the name of the output file: ";
            string tempoutput = "";
            cin >> tempoutput;
            cout << "Enter the name of the encrypt data output file: ";
            string encodeoutput = "";
            cin >> encodeoutput;
            cout << "Enter the name of the decrypt data output file: ";
            string decodeoutput = "";
            cin >> decodeoutput;
            encrypt(tempinput, tempoutput, encodeoutput, decodeoutput);
        }//"testinput.txt", "testoutput.txt", "testencoder.txt"

        else if (input == 'q'){
            return 0;
        }

        else {
            cout << "That was not one of the choices" << endl;
        }

        cout << "Type 'e' to encrypt or 'q' to exit: ";
    }

    return 0;
}

// returns a vector with each token seperated (hopefully)
vector<token*> seperateWords(string stufftoEncrypt) {
    vector<token*> tokens;
    //empty case
    if (stufftoEncrypt == "") {
        return tokens;
    }

    //list of words that appear in the string
    string thingstofind = " ,.-!?;:\"\'()@\n";
    unsigned location = 0;
    unsigned location2 = location;

//partitioning of big string into tokens
topofEncrypt:
    while (stufftoEncrypt.find_first_of(thingstofind, location) != string::npos) {
        token* newtoken = new token();
        for (char i : thingstofind) {  //check for punctuation
            if (stufftoEncrypt[location] == i) {
                location++;
                newtoken->word = stufftoEncrypt.substr(location-1, 1);
                //checking to see if its already there
                for (token* i : tokens){
                    if (newtoken->word == i->word){
                        i->frequency += 1;
                        delete newtoken;
                        goto topofEncrypt;
                    }
                }
                tokens.push_back(newtoken);
                goto topofEncrypt;
            }
        }
        location2 = stufftoEncrypt.find_first_of(thingstofind, location);
        newtoken->word = stufftoEncrypt.substr(location, location2 - location);
        location = location2;
        //checking for if its already in the list of tokens
        for (unsigned i = 0; i < tokens.size(); i++) {
            if (newtoken->word == tokens[i]->word) {
                tokens[i]->frequency += 1;
                delete newtoken;
                goto topofEncrypt;
            }
        }
        tokens.push_back(newtoken);
    }

    if (location >= stufftoEncrypt.size()){
        return tokens;
    }
    token* n = new token();
    n->word = stufftoEncrypt.substr(location);
    for (unsigned i = 0; i < tokens.size(); i++) {  //end case
        if (n->word == tokens[i]->word) {
            tokens[i]->frequency += 1;
            delete n;
            return tokens;
        }
    }
    tokens.push_back(n);
    return tokens;
}

void encrypt(string inputFile, string outputFile, string encoderdatafile, string decoderdatafile) {
    string ans = "";
    string stufftoEncrypt = "";
    vector<string> encoderQueue;  // list of words sorted by frequency

    // reading file
    ifstream input;
    input.open(inputFile);
    if (!input.is_open()) {
        cout << "File failed to open" << endl;
        return;
    }
    string tem = "";
    while (!input.eof()) {
        getline(input, tem);
        stufftoEncrypt += tem;
    }
    input.close();

    // Partitioning
    vector<token*> tokens = seperateWords(stufftoEncrypt);

    //create encoder
    for (token* i : tokens){
        cout << i->word << ", " << i->frequency << endl;
    }
    cout << endl;
    
    //sorting
    bool sorted = false;
    while (!sorted){
        sorted = true;
        for (int i = 0; i < tokens.size() - 1; i++){
            if (tokens[i]->frequency > tokens[i+1]->frequency){
                token* temp = tokens[i];
                tokens[i] = tokens[i+1];
                tokens[i+1] = temp;
                sorted = false;
                break;
            }
        }
    }

    for (token* i : tokens){
        cout << i->word << ", " << i->frequency << endl;
    }
    for (int i = tokens.size() - 1; i >= 0; i--) {
        encoderQueue.push_back(tokens[i]->word);
    }

    //creates the encoded hashtable
    HashTable encoder(1000);
    HashTable decoder (1000);
    for (int i = 0; i < encoderQueue.size(); i++) {
        encoder.insert(encoderQueue.at(i), to_string(i));
        decoder.insert(encoderQueue.at(i), to_string(i));
    }
    

    
    // Subtitution
    vector<string*> finalQueue;
/************************************************/

    //list of words that appear in the string
    string thingstofind = " ,.-!?;:\"\'()@\n";
    unsigned location = 0;
    unsigned location2 = location;

    //partitioning of big string into tokens
    repeat:
    while (stufftoEncrypt.find_first_of(thingstofind, location) != string::npos) {
        string* newstring = new string;
        for (char i : thingstofind) {  //check for punctuation
            if (stufftoEncrypt[location] == i) {
                location++;
                *newstring = stufftoEncrypt.substr(location-1, 1);
                finalQueue.push_back(newstring);
                goto repeat;
            }
        }
        location2 = stufftoEncrypt.find_first_of(thingstofind, location);
        *newstring = stufftoEncrypt.substr(location, location2 - location);
        location = location2;
        finalQueue.push_back(newstring);
    }

    string* n = new string;
    if (location >= stufftoEncrypt.size()){
        delete n;
        goto endd;
    }
    *n = stufftoEncrypt.substr(location);
    finalQueue.push_back(n);
    endd:
/************************************************/
    for (string* i : finalQueue){
        ans += encoder.getMappedValue(*i);
    }


    //We can maybe implement decode like this
    /*
        HashTable decoder(1000);
        for (int i = 0; i < encoderQueue.size(); i++){
          hashtoken* newhashtoken = new hashtoken(encoderQueue.at(i), to_string(i));
          newhashtoken->word = tokens[i]->word;

          decoder.insert(to_string(i), encoderQueue.at(i));
    }
*/

    // print out files
    ofstream output(outputFile);
    if (!output.is_open()) {
        cout << "Output file failed to open";
        return;
    }
    output << ans;

    ofstream decoderoutput(decoderdatafile);
    ofstream encoderoutput(encoderdatafile);
    if (!decoderoutput.is_open()) {
        cout << "Decoder data file failed to open";
        return;
    }
    decoderoutput << "Code -> Word" << endl;
    for (int i = tokens.size() - 1; i >= 0; i--) {
        if (tokens[i]->word == "") {
            break;
        }
        if (tokens[i]->word == "\n"){
        decoderoutput << "newline" << endl << decoder.getMappedValue(tokens[i]->word) << endl;
        continue;
        }
        decoderoutput << decoder.getMappedValue(tokens[i]->word) << " -> " << tokens[i]->word << endl;
    }

    encoderoutput << "Word - > Code" << endl;
    for (int i = tokens.size() - 1; i >= 0; i--) {
        if (tokens[i]->word == "") {
            break;
        }
        if (tokens[i]->word == "\n"){
        encoderoutput << "newline" << endl << encoder.getMappedValue(tokens[i]->word) << endl;
        continue;
        }
        encoderoutput << tokens[i]->word << " -> " << encoder.getMappedValue(tokens[i]->word) << endl;
    }

    encoderoutput.close();
    decoderoutput.close();
    output.close();
    
      
    
}