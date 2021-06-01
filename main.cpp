#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include "HashTable.h"

using namespace std;
/*
1. Pass through the data once, collecting a list of token-frequency counts.
2. Sort the token-frequency counts by frequency, in descending order.
3. Assign codes to tokens using a simple counter, for example by incrementing over theintegers; this is just to keep things simple.
4. Store the new mapping (token -> code) in a hashtable called “encoder”.
5. Store the reverse mapping (code -> token) in a hashtable called "decoder".
6. Pass through the data a second time. This time, replace all tokens with their codes
*/

/*
  Old Struct:
  
  struct token
  {
    int frequency = 1;
    string word = "";

  };

  New one moved to HashTable.h
*/


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

/*
void encrypt(string inputFile, string outputFile){
  ifstream inFS;
  vector<string> tokens;
  string currToken;
  string thingstofind = " ,.-!?;:\"\'()@";

  inFS.open(inputFile);

  if(!inFS.is_open())
  {
    cout << "File could not be opened." << endl;
    return;
  }
  else
  {
    while (inFS >> currToken)
    {
      
      int startLocation = 0;
      int endLocation = 0;

      //Ex: cat.dog!frog; string size: 12; 
      //find_first_of: searches the currToken/string for the first occurence of any punctuation
      //substr: takes a part of the string using the starting index, then size of the substring as parameters 
      while (currToken.find_first_of(thingstofind, startLocation) != string::npos)
      {
        string punctuation = "";
        punctuation = currToken.find_first_of(thingstofind, startLocation);
        endLocation = currToken.at(currToken.find_first_of(thingstofind, startLocation));
        tokens.push_back(currToken.substr(startLocation, endLocation - startLocation));
        tokens.push_back(punctuation);


        currToken = currToken.substr(endLocation + 1, (currToken.size() - 1) - endLocation);
      }
      
      tokens.push_back(currToken);
    }
  }

  inFS.close();

  
}
*/



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

void decrypt(string fileInputName, string fileOutputName)
{

}