#include "plugboard.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include <vector>
#include <algorithm>

using namespace std;

Plugboard::Plugboard(char* argv){
  error_code = load(argv);
}

int Plugboard::load(char* argv){
  ifstream in_stream;
  in_stream.open(argv);

  // check opening configuration file
  if(in_stream.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  // read from config file
  int i;
  in_stream.peek();
  while(!in_stream.eof()){
    in_stream >> i >> ws;

    // check plugboard config size
    if(wire_config.size()>=26){
      cerr << "Incorrect number of parameters in plugboard file " << argv << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }

    // check if reading elements are all numbers
    if(in_stream.fail()){
      cerr << "Non-numeric character in plugboard file " << argv << endl;
      return NON_NUMERIC_CHARACTER;
    }

    // check if elements are valid
    if(i < 0 || i > 25){
      return INVALID_INDEX;
    }

    // check if one letter is connected to more than one letter
    if(find(wire_config.begin(),wire_config.end(),i) != wire_config.end() && wire_config.size()<26){
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
    
    wire_config.push_back(i);
    in_stream.peek();
  }

  // config elements much all in pairs
  if(wire_config.size()%2 != 0){
    cerr << "Incorrect number of parameters in plugboard file " << argv << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  in_stream.close();

  return NO_ERROR;
}

char Plugboard::encrypt(char letter){
  // check if input letter has plugboard wire connecting
  int counter = 0;
  for(int i: wire_config){ 
    if( (letter-'A') == i){
      // change any matching letter to coresponding letter, if there's no match same letter will be returned.
      if(counter%2 == 0){
	letter = wire_config[counter+1]+'A';
	break;
      }
      else{
	letter = wire_config[counter-1]+'A';
	break;
      }
    }
    counter++;
  }
  return letter;
}


