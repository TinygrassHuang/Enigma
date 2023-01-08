#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <vector>
using namespace std;

class Plugboard{
  // Plugboard wire configuration
  vector<int> wire_config;
  
  // Initialise plugboard in Enigma machine
  // return: error codes;
  // input: file path argument
  int load(char* argv);
  
 public:
  // constructer
  // input: file path argument
  Plugboard(char* argv);

  // function to encrypt input letter when it's passed to plugboard
  // return: enctypted letter
  // input: passing letter
  char encrypt(char letter);

  // variable storing error code
  int error_code = 0;  
};


#endif
