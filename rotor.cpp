#include <iostream>
#include <fstream>
#include "rotor.h"
#include "errors.h"
#include <algorithm>
#include <vector>

using namespace std;

Rotor::Rotor(char** argv, int rotor_num){
  error_code = load(argv, rotor_num);
}

int Rotor::load(char** argv, int rotor_num){
  this->rotor_num = rotor_num;
  
  // Initialise rotors from left to right(0-n)
  for(int row=0; row < rotor_num; row++){
    ifstream in_stream;
    in_stream.open(argv[3+row]);

    // check opening config file
    if(in_stream.fail()){
      return ERROR_OPENING_CONFIGURATION_FILE;
    }

    // read from file
    int ii;
    vector<int> temp_rotor;
    vector<int> temp_notch;
    while(!in_stream.eof()){
      in_stream >> ii >> ws;

      // check readings are all numbers
      if(in_stream.fail()){
	cerr << "Non-numeric character for mapping in rotor file " << argv[3+row] << endl;
	return NON_NUMERIC_CHARACTER;
      }

      // check readings are valid numbers
      if(ii < 0 || ii >25){
	return INVALID_INDEX;
      }

      ///////seperate mapping from notches

      // check if the rotor config has less than 25 elements, push the last one to make it 26
      if(temp_rotor.size() < 26){
	// one letter cannot map to more than one other letter
	if(find(temp_rotor.begin(),temp_rotor.end(),ii) != temp_rotor.end()){
	  int index = 0;
	  while(temp_rotor[index] != *find(temp_rotor.begin(),temp_rotor.end(),ii)){
	    index++;
	  }
	  cerr << "Invalid mapping of input " << temp_rotor.size() << " to output " << ii << " (output " << ii << " is already mapped to from input " << index << ") in rotor file: " << argv[3+row] << endl;
	  return INVALID_ROTOR_MAPPING;
	}
	temp_rotor.push_back(ii);
      }
      else{
	temp_notch.push_back(ii);
      }
      
    }

    // each rotor config must contain all the alphabets
    if(temp_rotor.size() < 26){
      cerr << "Not all inputs mapped in rotor file: " << argv[3+row] << endl;
      return INVALID_ROTOR_MAPPING;
    }
    
    rotor_config.push_back(temp_rotor);//(1-n)x26 rotor config
    notch.push_back(temp_notch);
    in_stream.close();
  }
  
  /////////get rotor starting position(s)
  ifstream pos_in;
  pos_in.open(argv[rotor_num+3]);// [rotor_num+4-1]: last argv
  
  if(pos_in.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  
  int i;
  while(!pos_in.eof()){
    
    if(pos_in.peek()=='\n'){ // peek to see if next element is '/n'
      break;
    }

    pos_in >> ws >> i;

    if(pos_in.fail()){
      cerr << "Non-numeric character in rotor positions file " << argv[rotor_num+3] << endl;
      return NON_NUMERIC_CHARACTER;
    }
    
    if(i < 0 || i > 25){
      return INVALID_INDEX;
    }

    start_pos.push_back(i);
  }
  
  pos_in.close();

  // rotor starting positions must match rotor number
  if(start_pos.size()!= rotor_num){
    return NO_ROTOR_STARTING_POSITION;
  }
  

  /////////initialise rotor position(s)
  for(int row=0; row < rotor_num; row++){
    rotate(rotor_config[row].begin(), rotor_config[row].begin()+start_pos[row], rotor_config[row].end());
  }

  return NO_ERROR;
  
}

bool Rotor::check_if_notch(int rotor_code){
  if(find(notch[rotor_code].begin(), notch[rotor_code].end(), rotor_config[rotor_code].front())!= notch[rotor_code].end()){
    return true;
  }
  return false;
}

void Rotor::rotate_single_rotor_by_1(int rotor_code){
  rotate(rotor_config[rotor_code].begin(), rotor_config[rotor_code].begin()+1, rotor_config[rotor_code].end());
}

void Rotor::one_press(){
  /////rotate right most rotor and check if a notch is hit
  ////if the first element of right most rotor is a notch, rotate next rotor
  rotate_single_rotor_by_1(rotor_num-1);
  
  if(rotor_num > 0){
    for(int row = rotor_num-1; row > 0; row--){
      if(check_if_notch(row)){
	rotate_single_rotor_by_1(row-1);
      }
    }
  }
  
}

char Rotor::encrypt_forward(char letter){
  //encrypt from right to left
  for(int row = rotor_num-1; row >= 0; row--){
    letter = rotor_config[row][letter-'A']+'A';
  }
  return letter;
}

char Rotor::encrypt_backward(char letter){
  //encrypt from left to right
  for(int row = 0; row <= rotor_num-1; row++){
    for(int i=0; i < 26; i++){
      if(rotor_config[row][i] == letter-'A'){
	letter = i + 'A';
	break;
      }
    }
  }
  return letter;
}


