#include <iostream>
#include <fstream>
#include "errors.h"
#include "enigma.h"
#include <vector>


using namespace std;

int main(int argc, char** argv){

  // check input argument numbers
  if(argc < 4){
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  

  // initialise an Enigma machine
  Enigma* machine_1 = nullptr;
  machine_1 = new Enigma(argc, argv);
  if(machine_1->error_code){
    return machine_1->error_code;
  }

  // get input from console
  string plain_text,cipher;
  getline(cin >> ws, plain_text);
  
  // enctrypting the input string, check if letters are legal first
  for(char letter : plain_text){
    if(letter < 'A' || letter > 'Z'){
      cerr << letter << " is not a valid input character (input characters";
      cerr <<" must be upper case letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }
    else{
      cipher.push_back(machine_1->encrypt(letter));
    }
  }

  // outputting encrypted text;
  cout << cipher << endl;
  return NO_ERROR;
}
