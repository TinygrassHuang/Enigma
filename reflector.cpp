#include <iostream>
#include "errors.h"
#include "reflector.h"
#include <fstream>
#include <algorithm>

using namespace std;

Reflector::Reflector(char* argv){
  error_code = load(argv);
}

int Reflector::load(char* argv){
  ifstream in_stream;
  in_stream.open(argv);

  // check opening config file
  if(in_stream.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  // read from config file
  int i;
  in_stream.peek();
  while(!in_stream.eof() && reflect_config.size()<27){
    in_stream >> i >> ws;

    // check if config inputs are numbers
    if(in_stream.fail()){
      cerr << "Non-numeric character in reflector file " << argv << endl;
      return NON_NUMERIC_CHARACTER;
    }

    // check if config inputs are valid numbers
    if(i < 0 || i > 25){
      return INVALID_INDEX;
    }

    // check if one letter is reflected to more than one letter
    if(find(reflect_config.begin(),reflect_config.end(),i) != reflect_config.end() && reflect_config.size()<26){
      return INVALID_REFLECTOR_MAPPING;
    }

    reflect_config.push_back(i);
    in_stream.peek();
  }

  // 
  if(reflect_config.size()%2 == 0 && reflect_config.size()<26){
    cerr << "Insufficient number of mappings in reflector file: " << argv << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }else if(reflect_config.size()%2 == 1 && reflect_config.size()<26){
    cerr << "Incorrect (odd) number of parameters in reflector file " << argv << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  while(!in_stream.eof()){
    in_stream >> i >>ws;
    reflect_config.push_back(i);
  }

  if (reflect_config.size() > 26 && reflect_config.size() %2 == 1) {
    cerr << "Incorrect (odd) number of parameters in reflector file " << argv << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  //
  if (reflect_config.size() < 26) {
    cerr << "Insufficient number of mappings in reflector file: " << argv << endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

  in_stream.close();

  return NO_ERROR;
}

char Reflector::encrypt(char letter){

  // match passing letter to its reflecting letter, return reflecting letter
  int counter = 0;
  for(int i: reflect_config){
    if( (letter-'A') == i){
      if(i%2 == 0){
	letter = reflect_config[counter+1]+'A';
	break;
      }
      else{
	letter = reflect_config[counter-1]+'A';
	break;
      }
    }
    counter++;
  }
  return letter;
}
