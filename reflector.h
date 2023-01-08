#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <vector>
using namespace std;

class Reflector{
  // reflector configuration --> letter mapping
  vector<int> reflect_config;

  // initialise reflector in Enigma machine
  // input: file path argument
  // return: error codes
  int load(char* argv);
  
 public:
  // constructer
  // input: file path argument
  Reflector(char* argv);

  // function to enctypt input letter when it's passed to reflector
  // return: encrypted letter
  // input: passing letter
  char encrypt(char letter);

  // variable storing error code
  int error_code = 0;
};

#endif
