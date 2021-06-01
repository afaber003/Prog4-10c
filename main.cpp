#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <list>
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



void encrypt(string inputFile, string outputFile, string encoderdatafile){
    string ans = "";
    string stufftoEncrypt = "";
    string encoder[20] = {""};


    //Read input
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

    //empty case
    if (stufftoEncrypt == ""){
        return;
    }
    //list of words that appear in the string
    vector<token*> tokens;
    string thingstofind = " ,.-!?;:\"\'()@\n";
    unsigned location = 0;
    for (char i : thingstofind){ //check for start with punctuation
        if (stufftoEncrypt[location] == i){
            location++;
        }
    }
    unsigned location2 = 0;

    //partitioning of big string into tokens
    topofEncrypt:
    while (stufftoEncrypt.find_first_of(thingstofind, location) < stufftoEncrypt.size()){
        token* newtoken = new token();
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
    for (unsigned i = 0; i < tokens.size(); i++){   //end case
        n->word = stufftoEncrypt.substr(location, stufftoEncrypt.size()-location);
        if (n->word == tokens[i]->word){
            tokens[i]->frequency += 1;
            delete n;
            goto endofpartitioning;
        }
    }
    tokens.push_back(n);
    endofpartitioning:


    //create encoder
    sort(tokens.begin(), tokens.end()); //only uses "<" per c++ reference
    for (int i = 0; i < 20; i++){ //TODO: replace with hash
        if (i == tokens.size()){
            break;
        }
        encoder[i] = tokens[i]->word;
    }

    //start encoding
    location = 0;
    for (char i : thingstofind){ //check for start with punctuation
        if (stufftoEncrypt[location] == i){
            location++;
        }
    }   
    startagain:
    while (stufftoEncrypt.find_first_of(thingstofind, location) < stufftoEncrypt.size()){
        string tempp = "";
        location2 = stufftoEncrypt.find_first_of(thingstofind, location);
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
    encoderoutput << "token, code" << endl;
    for (int i = 0; i < 20; i++){
        if (encoder[i] == ""){
            break;
        }
        encoderoutput << encoder[i] << ", " << i+1 << endl;
    }

    encoderoutput.close();
    output.close();


}