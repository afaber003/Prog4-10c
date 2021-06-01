#include <fstream>
#include <iostream>
#include <algorithm> 
#include <vector>
#include <cstring>
#include <list>
#include "HashTable.h"
#define test cout << "Here" << endl;

using namespace std;

struct token{
    int frequency = 1;
    string word = "";
};

bool operator< (token lefthandside, token righthandside){
    if (lefthandside.frequency < righthandside.frequency){
        return true;
    } else return false;
}

//helper function
vector<token*> seperateWords(string fileInput);

// Encrypt with file input to file output
void encrypt(string fileInputName, string fileOutputName, string encoderdatafile);

// Decrypt with file input and file output
void decrypt(string fileInputName, string fileOutputName){}


////////////////////////////////////
//        MAIN
////////////////////////////////////


int main(){

    char input = ' ';

    cout << "Type 'e' to encrypt\nType 'd' to decrypt\nMake your selection or 'q' to exit: ";

    // basically the menu
    while(tolower(input) != 'q'){
        cin >> input;

        // Encrypt from file to file
        if (input == 'e'){
            cout << "Enter the name of the input file: ";
            string tempinput = "";
            cin >> tempinput;
            cout << "Enter the name of the output file: ";
            string tempoutput;
            cin >> tempoutput;
            cout << "Enter the name of the encrypt data output file: ";
            string dataoutput;
            cin >> dataoutput;
            encrypt("testinput.txt", "testoutput.txt", "testencoder.txt");
        }

        // Decrypt from file to file
        else if (input == 'd'){
            cout << "Enter the name of the input file: ";
            string tempinput = "";
            cin >> tempinput;
            cout << "Enter the name of the output file: ";
            string tempoutput;
            cin >> tempoutput;
            decrypt(tempinput, tempoutput);
        }

        else {
            cout << "That was not one of the choices" << endl;
        }

        cout << "Type 'e' to encrypt\nType 'd' to decrypt\nMake your selection or 'q' to exit: ";
    }

    return 0;
}

// returns a vector with each token seperated (hopefully)
vector<token*> seperateWords(string stufftoEncrypt){
    vector<token*> tokens;
    //empty case
    if (stufftoEncrypt == ""){
        return tokens;
    }

    //list of words that appear in the string
    string thingstofind = " ,.-!?;:\"\'()@\n";
    unsigned location = 0;
    afewlinesup:
    for (char i : thingstofind){ //check for start with punctuation
        if (stufftoEncrypt[location] == i){
            location++;
            token* newertoken = new token;
            newertoken->word = (stufftoEncrypt[location - 1]);
            tokens.push_back(newertoken);
            goto afewlinesup;
        }
    }
    unsigned location2 = location;

    //partitioning of big string into tokens
    topofEncrypt:
    while (stufftoEncrypt.find_first_of(thingstofind, location) < stufftoEncrypt.size()){
        token* newtoken = new token();
        afewlinesup2:
        for (char i : thingstofind){ //check for punctuation
            if (stufftoEncrypt[location] == i){
                location++;
                token* newertoken = new token;
                newertoken->word = (stufftoEncrypt[location - 1]);
                tokens.push_back(newertoken);
                goto afewlinesup2;
            }
        }
        location2 = stufftoEncrypt.find_first_of(thingstofind, location);
        newtoken->word = stufftoEncrypt.substr(location, stufftoEncrypt.find_first_of(thingstofind, location) - location);
        location = location2 + 1;
        //checking for if its already in the list of tokens
        for (unsigned i = 0; i < tokens.size(); i++){
            if (newtoken->word == tokens[i]->word){
                tokens[i]->frequency += 1;
                delete newtoken;
                goto topofEncrypt;
            }
        }
        tokens.push_back(newtoken);
    }

    token* n = new token();
    n->word = stufftoEncrypt.substr(location, stufftoEncrypt.size()-location);
    for (unsigned i = 0; i < tokens.size(); i++){   //end case
        if (n->word == tokens[i]->word){
            tokens[i]->frequency += 1;
            delete n;
            return tokens;
        }
    }
    tokens.push_back(n);
    return tokens;
}

void encrypt(string inputFile, string outputFile, string encoderdatafile){
    string ans = "";
    string stufftoEncrypt = "";
    //string encoder[20] = {""};
    vector <string> encoderQueue ;

    // reading file
    ifstream input;
    input.open(inputFile);
    if (!input.is_open()){
        cout << "File failed to open";
        return;
    }
    string tem = "";
    while (!input.eof()){
        getline(input, tem);
        stufftoEncrypt += tem + "\n";
    }
    input.close();

    // Partitioning
    vector<token*> tokens = seperateWords(stufftoEncrypt);


    //create encoder
    sort(tokens.begin(), tokens.end()); //only uses "<" per c++ reference
    //int j = 0;
    for (int i = tokens.size() - 1; i >= 0; i--){
      encoderQueue.push_back(tokens[i]->word);
      //j++;
    }
    //Might have to add this if the tokens vector is smaller than encoder!!!!
    //encoder.resize(tokens.size());

    /*
    for (int i = 0; i < 20; i++){ //TODO: replace with hash
        if (i == tokens.size()){
            break;
        }
        encoder[i] = tokens[i]->word;
    }
    */

    //creates the encoded hashtable

    HashTable encoder(1000);
    for (int i = 0; i < encoderQueue.size(); i++){
      //hashtoken* newhashtoken = new hashtoken(encoderQueue.at(i), to_string(i));
      //newhashtoken->word = tokens[i]->word;

      encoder.insert(encoderQueue.at(i), to_string(i));
    }

    //We can maybe implement decode like this 
    /*
        HashTable decoder(1000);
        for (int i = 0; i < encoderQueue.size(); i++){
          //hashtoken* newhashtoken = new hashtoken(encoderQueue.at(i), to_string(i));
          //newhashtoken->word = tokens[i]->word;

          decoder.insert(to_string(i), encoderQueue.at(i));
    }
    */

    //start encoding
    /*
    unsigned location = 0;
    string thingstofind = " ,.-!?;:\"\'()@\n";
    here:
    for (char i : thingstofind){ //check for start with punctuation
        if (stufftoEncrypt[location] == i){
            location++;
            goto here;
        }
    }   
    startagain:
    while (stufftoEncrypt.find_first_of(thingstofind, location) < stufftoEncrypt.size()){
        string tempp = "";
        unsigned location2 = stufftoEncrypt.find_first_of(thingstofind, location);
        tempp = stufftoEncrypt.substr(location, stufftoEncrypt.find_first_of(thingstofind, location) - location);
        for (int i = 0; i < encoder->size(); i++){
            if (tempp == encoder[i]){
                stufftoEncrypt.replace(location, tempp.size(), encoder[i]);
                location += encoder[i].size() + 1;
                goto startagain;
            }
        }
        location = location2 + 1;
    }
    for (int i = 0; i < encoder->size(); i++){
        if (stufftoEncrypt.substr(location, stufftoEncrypt.size() - location) == encoder[i]){
            stufftoEncrypt.replace(location, stufftoEncrypt.size(), encoder[i]);
        }
    }

    */
    // print out file
    ofstream output(outputFile);
    if (!output.is_open()){
        cout << "Output file failed to open";
        return;
    }
    output << stufftoEncrypt;

    ofstream encoderoutput(encoderdatafile);
    if (!encoderoutput.is_open()){
        cout << "Encoder data file failed to open";
        return;
    }
    for (int i = 0; i < 20; i++){
        if (encoder[i] == ""){
            break;
        }
        encoderoutput << encoder[i] << ", " << i+1 << endl;
    }

    encoderoutput.close();
    output.close();
    


}