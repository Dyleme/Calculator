//
// Created by aleks on 12/5/2019.
//

#include <iostream>
#include "calc.h"

std::string ReadFromFile(std::string name) {
  std::ifstream file;
  file.open(name);
  if (!file.is_open()) std::cout << "Error";
  std::string ss;
  std::getline(file, ss);
  file.close();
  return ss;
}
std::vector<std::string> TurnInPolish(std::string infictional) {
  std::vector<std::string> polish;
  StackOnArray<std::pair<std::string, int>> operands;
  char c;
  for (unsigned i = 0; i < infictional.size(); ++i) {
    int number;
    std::string temp_s;
    switch (infictional[i]) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        number = ToInt(infictional[i]);
        while (infictional[i + 1] <= '9' && infictional[i + 1] >= '0') {
          i++;
          number = number * 10 + ToInt(infictional[i]);
        }
        polish.push_back(ToString(number));
        break;
      case '*':
        transform(operands, polish, 5, "*");
        break;
      case '/':
        transform(operands, polish, 5, "/");
        break;
      case '%':
        transform(operands, polish, 5, "%");
        break;
      case '+':
        transform(operands, polish, 6, "+");
        break;
      case '-':
        transform(operands, polish, 6, "-");
        break;
      case '<':
        switch (infictional[i + 1]) {
          case '=':
            i++;
            transform(operands, polish, 8, "<=");
            break;
          case '<':
            i++;
            transform(operands, polish, 7, "<<");
            break;
          default:
            transform(operands, polish, 7, "<");
            break;
        }
        break;
      case '>':
        switch (infictional[i + 1]) {
          case '=':
            i++;
            transform(operands, polish, 8, ">=");
            break;
          case '<':
            i++;
            transform(operands, polish, 7, ">>");
            break;
          default:
            transform(operands, polish, 7, ">");
            break;
        }
        break;
      case '=':
        if (infictional[i + 1] == '=') {
          i++;
          transform(operands, polish, 9, "==");
        }
        break;
      case '!':
        if (infictional[i + 1] == '=') {
          i++;
          transform(operands, polish, 9, "!=");
        }
        break;
      case '&':
        if (infictional[i + 1] == '&') {
          i++;
          transform(operands, polish, 13, "&&");
        } else {
          transform(operands, polish, 10, "&");
        }

        break;
      case '^':
        transform(operands, polish, 10, "^");
        break;
      case '|':
        if (infictional[i + 1] == '|') {
          i++;
          transform(operands, polish, 14, "||");
        } else {
          transform(operands, polish, 12, "|");
        }
        break;
      case ')':
        transform(operands, polish, 15, ")");
        break;
      case '(':
        transform(operands, polish, 15, "(");
        break;
    }
  }

  while (!operands.IsEmpty()) {
    polish.push_back(operands.Pop().first);
  }
  return polish;
}

int ToInt(std::string str) {
  std::stringstream stream;
  stream << str;
  int number;
  stream >> number;
  return number;
}

int ToInt(char ch) {
  std::stringstream stream;
  stream << ch;
  int number;
  stream >> number;
  return number;
}
std::string ToString(int t) {
  std::string str;
  std::stringstream ss;
  ss << t;
  ss >> str;
  return str;
}

void transform(StackOnArray<std::pair<std::string, int>>& operations,
               std::vector<std::string>& polish, int prioritet,
               std::string const operation) {
  if (operation == ")") {
    while (operations.Top()->first != "(") {
      polish.push_back(operations.Pop().first);
    }
    operations.Pop();
  } else if (operation == "(") {
    operations.Push(std::make_pair(operation, prioritet));
  } else {
    while (!operations.IsEmpty() && operations.Top()->second <= prioritet) {
      std::string temp_s = operations.Pop().first;
      polish.push_back(temp_s);
    }
    operations.Push(std::make_pair(operation, prioritet));
  }
}

int calculate(std::vector<std::string> str) {
  StackOnArray<int> stack_on_array;
  for (unsigned int i = 0; i < str.size(); i++) {
    if (str[i] == "*" || str[i] == "+" || str[i] == "-" || str[i] == "/" ||
        str[i] == "<<" || str[i] == ">>" || str[i] == "<" || str[i] == "<=" ||
        str[i] == ">" || str[i] == ">=" || str[i] == "==" || str[i] == "%" ||
        str[i] == "!=" || str[i] == "&" || str[i] == "^" || str[i] == "|" ||
        str[i] == "&&" || str[i] == "||") {
      int a = operation(stack_on_array, str[i]);
      stack_on_array.Push(a);
    } else {
      stack_on_array.Push(ToInt(str[i]));
    }
  }
  assert(stack_on_array.Size() == 1);
  return stack_on_array.Pop();

  return 0;
}
int operation(StackOnArray<int>& stack_on_array, std::string action) {
  int second = stack_on_array.Pop();
  int first = stack_on_array.Pop();
  if (action == "*")
    return first * second;
  else if (action == "/")
    return first / second;
  else if (action == "%")
    return first % second;
  else if (action == "+")
    return first + second;
  else if (action == "-")
    return first - second;
  else if (action == "<<")
    return first << second;
  else if (action == ">>")
    return first >> second;
  else if (action == "<")
    return first < second;
  else if (action == "<=")
    return first <= second;
  else if (action == ">=")
    return first >= second;
  else if (action == "==")
    return first == second;
  else if (action == "!=")
    return first != second;
  else if (action == "&")
    return first & second;
  else if (action == "^")
    return first ^ second;
  else if (action == "|")
    return first | second;
  else if (action == "&&")
    return first && second;
  else if (action == "||")
    return first || second;
  assert("no operation");
}
