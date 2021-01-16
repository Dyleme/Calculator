#include <iostream>
#include "calc.h"
#include "stack.h"


int main() {
  StackOnArray<std::string> operators;
  StackOnArray<int> operands;
  std::string infictional;
  infictional =  ReadFromFile("txt.txt");
  std::vector<std::string> polish(TurnInPolish(infictional));
  for(auto k: polish){
    std::cout << k <<" ";
  }

  std::cout <<'\n' <<calculate(polish);
  int a = {4 + 5 * 3 - 34};
  std::cout <<'\n' << a ;
  return 0;
}