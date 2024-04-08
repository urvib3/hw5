#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelp(
    std::string& in,
    const std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& ans,
    const int blanks); 


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

  // count blanks of word
  int blanks = 0; 
  for(char c : in) if(c == '-') blanks++;     

   std::set<std::string> ans; 
   std::string inCopy = in; 
   wordleHelp(inCopy, floating, dict, ans, blanks); 

   return ans;

}

// Define any helper functions here
void wordleHelp(
    std::string &in,
    const std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& ans,
    const int blanks)
{


    // check base case
    if(blanks == 0) {
        if(dict.count(in)) ans.insert(in); 
        return; 
    }

    // if blanks > floating size, try every single letter
    if(blanks > floating.size()) {
        int index = in.find_first_of('-'); 
        for(char c = 'a'; c <= 'z'; c++) {
            in[index] = c; 
            // if floating has current char, delete it from floating
            wordleHelp(in, (floating.find_first_of(c) != std::string::npos) ? ((floating.substr(0, floating.find_first_of(c)) + floating.substr(floating.find_first_of(c) + 1))) : floating, dict, ans, blanks - 1);  
            in[index] = '-';
        }
    }
    
    // if blanks = floating size, try every single floating letter
    else if(blanks == floating.size()){
        int index = in.find_first_of('-');
        for(char c : floating) {
            in[index] = c; 
            // if floating has current char, delete it from floating
            wordleHelp(in, (floating.substr(0, floating.find_first_of(c)) + floating.substr(floating.find_first_of(c) + 1)), dict, ans, blanks - 1); 
            in[index] = '-';
        }
    }

}