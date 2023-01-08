#include <iostream>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"

using namespace std;

Enigma::Enigma(int argc, char** argv){
  error_code = load(argc, argv);
}

int Enigma::load(int argc, char** argv){

  plugboard = new Plugboard(argv[1]);
  if(plugboard->error_code){
    return plugboard->error_code;
  }

  reflector = new Reflector(argv[2]);
  if(reflector->error_code){
    return reflector->error_code;
  }
  
  if(argc == 3){
    rotor_num = 0;
  }
  else{
    rotor_num = argc - 4;
  }

  if(rotor_num > 0){
    rotors = new Rotor(argv, rotor_num);
  }
  if(rotors->error_code){
    return rotors->error_code;
  }
  
  return NO_ERROR;
}

char Enigma::encrypt(char str){
  
  str = plugboard->encrypt(str);
  
  rotors->one_press();
  
  str = rotors->encrypt_forward(str);
  
  str = reflector->encrypt(str);
  
  str = rotors->encrypt_backward(str);
  
  str = plugboard->encrypt(str);

  
  return str;
}

Enigma::~Enigma(){
  if(plugboard){delete plugboard;}
  if(rotors){delete rotors;}
  if(reflector){delete reflector;}
}
