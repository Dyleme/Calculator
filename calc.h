//
// Created by aleks on 12/5/2019.
//

#ifndef CALCULATOR__CALC_H_
#define CALCULATOR__CALC_H_

#include <string>
#include <fstream>
#include <vector>
#include "stack.h"
#include <sstream>
#include <cassert>

std::string ReadFromFile(std::string name);


std::vector<std::string> TurnInPolish(std::string infictional);

int ToInt(std::string);
int ToInt(char);
std::string ToString(int t);
void transform(StackOnArray<std::pair<std::string,int>>& operations, std::vector<std::string>& polish,int prioritet,std::string operation);
int calculate(std::vector<std::string> str);
int operation(StackOnArray<int>& stack_on_array, std::string action);
#endif //CALCULATOR__CALC_H_
