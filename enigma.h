#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include <vector>
using namespace std;

class Enigma{
  // Enigma machine components
  Plugboard* plugboard = nullptr;
  Rotor* rotors = nullptr;
  Reflector* reflector = nullptr;
  
  // Number of rotor(s)
  int rotor_num;

  // function to initialise a Enigma machine
  // input: number of input arguments, file path arguments
  // return: error codes
  int load(int argc, char** argv);
  
 public:
  // constructer
  Enigma(int argc,char** argv);

  // function to encrypt input letter, passing through all the components
  // input: passing letter
  // return: enctypted letter to be outputted
  char encrypt(char str);

  // destructer
  ~Enigma();

  // variable to store error code
  int error_code = 0;

};


#endif
