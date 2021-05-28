#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct token{
    int frequency = 1;
    string word = "";
};

// Encrypt with file input to file output
void encrypt(string fileInputName, string fileOutputName);

// Decrypt with file input and file output
void decrypt(string fileInputName, string fileOutputName);


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
            encrypt(tempinput, tempoutput);
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



void encrypt(string inputFile, string outputFile){
    string ans = "";
    string stufftoEncrypt = "";


    //TODO: READ THE STRING FROM THE intputFile INTO "stufftoEncrypt"




    //empty case
    if (stufftoEncrypt == ""){
        return;
    }

    //list of words that appear in the string
    vector<token*> tokens;
    string thingstofind = " ,.-!?;:\"\'()@";
    unsigned location = 0;

    //partitioning of big string into tokens
    topofEncrypt:
    while (stufftoEncrypt.find_first_of(thingstofind, location + 1) != string::npos){
        token* newtoken = new token();
        location = stufftoEncrypt.find_first_of(thingstofind, location + 1);
        newtoken->word = stufftoEncrypt.substr(location, stufftoEncrypt.find_first_of(thingstofind, location + 1));
        location = stufftoEncrypt.find_first_of(thingstofind, location + 1);
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
    
}