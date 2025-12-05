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
void wordleHelper(std::string& curr, int index, const std::string& in, int floatingLeft, const std::set<std::string>& dict, std::set<std::string>& output, int floatingMultiples[26]);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> output;
    string curr=in;
    //create array of each letter and how many floating of each there are
    int floatingMultiples[26]={0};
    //how many floating letters are left
    int floatingLeft=0;
    for(size_t i=0; i<floating.size(); i++){
        floatingMultiples[floating[i]-'a']++;
        floatingLeft++;
    }
    wordleHelper(curr, 0, in, floatingLeft, dict, output, floatingMultiples);
    return output;
    
}

// Define any helper functions here
void wordleHelper(std::string& curr, int index, const std::string& in, int floatingLeft, const std::set<std::string>& dict, std::set<std::string>& output, int floatingMultiples[26]){
  //index is pos about to fill
  //in is dashes and letters
  //floatingLeft is remaining floating
  //floatingMultiples is the number of floating of each letter
  //output is all the possible words that it could be
  
  //full word has been made
  if(index==int(in.size())){
    if( floatingLeft==0 && dict.find(curr)!=dict.end()){
      output.insert(curr);
    }
    return;
  }
  //pruning, more floating than blank spaces
  if(floatingLeft > (int(in.size()) - index)){
    return;
  }  
  
  //found green letter
  if(in[index] != '-'){
    //nothing to do here, just move to the next index
    wordleHelper(curr,index+1,in,floatingLeft,dict, output, floatingMultiples);
  }  
  //found dash, need to be filled in
  else if(in[index]=='-'){ 
    //go through all the letters
    for (char letter='a'; letter<='z'; letter++){
      //test current letter
      curr[index]=letter;
      //try to use floating
      floatingMultiples[letter-'a']--;
      int x =floatingMultiples[letter-'a'];
      //if floating can be used decrease floating left
      if(x>=0){
        floatingLeft--;
      }
      //recure to next index with this 
      wordleHelper(curr,index+1,in,floatingLeft,dict, output, floatingMultiples);
      //if it didnt work, need to backtrack
      if(x>=0){
        floatingLeft++;
      }
      floatingMultiples[letter-'a']++;
      curr[index]='-';
    }
  }
}  
      
