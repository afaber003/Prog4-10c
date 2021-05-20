#include <fstream>
#include <iostream>

using namespace std;

// Encrypt with string input and print
void encrypt(string stufftoencrypt);

// Encrypt with file input to file output
void encrypt(string fileInputName, string fileOutputName);

// Decrypt with string input and print
void decrypt(string input);

// Decrypt with file input and file output
void decrypt(string fileInputName, string fileOutputName);


int main(){
    char input = ' ';

    cout << "Type 'e' to encrypt from string\nType 'ef' to encrypt a file\nType 'd' to decrypt from a string\nType 'df' to decrypt from a file\nMake your selection: ";

    // basically the menu
    while(tolower(input) != 'q'){
        cin >> input;
        
        // Encrypt from string to string
        if (input == 'e'){
            //TODO: make the encrypt interface
        }

        // Encrypt from file to file
        else if (input == 'ef'){
            //TODO: make the encryption interface
        }

        // Decrypt from string to string
        else if (input == 'd'){
            //TODO: make the decrypt interface
        }

        // Decrypt from file to file
        else if (input == 'df'){
            //TODO: make the decrypt interface
        }

        else {
            cout << "That was not one of the choices" << endl;
        }

    }

    return 0;
}