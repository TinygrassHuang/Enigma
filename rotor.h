#ifndef ROTOR_H
#define ROTOR_H

#include <vector>
using namespace std;

class Rotor{
  // number of rotors
  int rotor_num;
  
  // reflector configuration --> all the letter mapping among rotors
  vector<vector<int>> rotor_config;

  // present notch(es) in all the rotors
  vector<vector<int>> notch;

  // starting position of the rotors
  vector<int> start_pos;

  // initialise all the rotors in Enigma machine
  // input: file path argument, number of rotors
  // return: error codes
  int load(char** argv, int rotor_num);
  
 public:
  // constructer
  Rotor(char** argv, int rotor_num);

  // check if the top absolute position (position[0]) is notch
  // input: rotor code (0,1,2,3...), starting from left to right
  // return: true -> if it is a notch, vice versa
  bool check_if_notch(int rotor_code);

  // function that rotate a rotor by 1 step
  // input: rotor code (0,1,2,3...), starting from left to right
  void rotate_single_rotor_by_1(int rotor_code);

  // keyboard pressed one time, used to increment rotors before passing letter
  void one_press();

  // encrypt input letter when it's passed forward to the reflector (from right to left)
  // input: passing letter
  // return: enctypted letter
  char encrypt_forward(char letter);

  // encrypt input letter when it's passed backward to the reflector (from left to right)
  // input: passing letter
  // return: encrypted letter
  char encrypt_backward(char letter);

  // variable storing error code
  int error_code;
};

#endif
