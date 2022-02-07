#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;

/*
following Tokens are there in the program:
  KY - Keyword 
  SP - Special-Characters
  OP - Operator 
  ID - Identifier
  NU - Number 
  LT - Literal
*/

void init(set<string> &keyWords, set<string> &specialSymbols, set<string> &operators, map<string, string> &tokens){
  // List of Keywords available in the program
  keyWords.insert("auto");
  keyWords.insert("break");
  keyWords.insert("bool");
  keyWords.insert("case");
  keyWords.insert("char");
  keyWords.insert("continue");
  keyWords.insert("do");
  keyWords.insert("double");
  keyWords.insert("delete");
  keyWords.insert("else");
  keyWords.insert("false");
  keyWords.insert("float");
  keyWords.insert("for");
  keyWords.insert("if");
  keyWords.insert("int");
  keyWords.insert("long");
  keyWords.insert("namespace");
  keyWords.insert("new");
  keyWords.insert("private");
  keyWords.insert("protected");
  keyWords.insert("public");
  keyWords.insert("return");
  keyWords.insert("short");
  keyWords.insert("signed");
  keyWords.insert("static");
  keyWords.insert("struct");
  keyWords.insert("switch");
  keyWords.insert("true");
  keyWords.insert("typedef");
  keyWords.insert("union");
  keyWords.insert("unsigned");
  keyWords.insert("using");
  keyWords.insert("void");
  keyWords.insert("while");

  // List of Special Symbols available in the program
  specialSymbols.insert("[");
  specialSymbols.insert("]");
  specialSymbols.insert("{");
  specialSymbols.insert("}");
  specialSymbols.insert("(");
  specialSymbols.insert(")");
  specialSymbols.insert(";");
  specialSymbols.insert(":");
  specialSymbols.insert(".");
  specialSymbols.insert("#");

  // List of Operators available in the program
  operators.insert("!");
  operators.insert("|");
  operators.insert("&");
  operators.insert(">>");
  operators.insert("<<");
  operators.insert("^");
  operators.insert("||");
  operators.insert("&&");
  operators.insert("+");
  operators.insert("*");
  operators.insert("-");
  operators.insert("/");
  operators.insert("=");
  operators.insert(">");
  operators.insert("<");
  operators.insert(">=");
  operators.insert("<=");
  operators.insert("!=");
  operators.insert("==");
  operators.insert("+=");
  operators.insert("-=");
  operators.insert("*=");
  operators.insert("/=");
  operators.insert("++");
  operators.insert("--");

  // List of Tokens available in the program
  tokens.insert(pair<string, string>("KY", "Keyword"));
  tokens.insert(pair<string, string>("SP", "Special-Character"));
  tokens.insert(pair<string, string>("OP", "Operator"));
  tokens.insert(pair<string, string>("ID", "Identifier"));
  tokens.insert(pair<string, string>("NU", "Number"));
  tokens.insert(pair<string, string>("LT", "Literal")); 
}

void printDescription(set<string> &keyWords, set<string> &specialSymbols, set<string> &operators, map<string, string> &tokens){
  cout << "In my program, I have considered following tokens:\n";
  cout << "Token " << tokens.at("KY") << " which consist of: ";
  auto itr = keyWords.begin();
  while(itr != keyWords.end()){
    cout << "\'" << *itr << "\', ";
    itr++;
  }
  cout << "\n\n";

  cout << "Token " << tokens.at("SP") << " which consist of: ";
  itr = specialSymbols.begin();
  while(itr != specialSymbols.end()){
    cout << "\'" << *itr << "\', ";
    itr++;
  }
  cout << "\n\n";

  cout << "Token " << tokens.at("OP") << " which consist of: ";
  itr = operators.begin();
  while(itr != operators.end()){
    cout << "\'" << *itr << "\', ";
    itr++;
  }
  cout << "\n\n";

  cout << "Token " << tokens.at("ID") << " which consist of any valid variable name. A variable name was considered valid, if it starts with an English alphabet (either small letter or capital letter) and consists of alphanumeric characters and underscore\n\n";

  cout << "Token " << tokens.at("NU") << " which consist of any valid integer or decimal number\n\n";
  cout << "Token " << tokens.at("LT") << " which consist of any valid string or character literal\n\n";

  cout << "Comments can only be entered using \'//\'\n-------------------------------------------------------------\n\n";
}

// Initialising the count of each token to 0
void initCount(map<string, int> &countTokens){
  countTokens.insert(pair<string, int>("KY", 0));
  countTokens.insert(pair<string, int>("SP", 0));
  countTokens.insert(pair<string, int>("OP", 0));
  countTokens.insert(pair<string, int>("ID", 0));
  countTokens.insert(pair<string, int>("NU", 0));
  countTokens.insert(pair<string, int>("LT", 0));
}

// Updating the value of count for each token
void updateCount(string str, map<string, int> &countTokens){
  auto itr = countTokens.find(str);
  int value = itr->second;
  value++;
  itr->second = value;
}

// Printing the token along with its value
void print(string str, string term){
  cout << "[" << str << ": \'" << term << "\']  ";
}

void printTokens(map<string, int> &countTokens){
  cout << "\n-------------------------------------------------\nIn the above program following are the count of available tokens:\n";
  cout << "Count of Keywords: " << countTokens.at("KY") << "\n";
  cout << "Count of Special-Characters: " << countTokens.at("SP") << "\n";
  cout << "Count of Operators: " << countTokens.at("OP") << "\n";
  cout << "Count of Identifier: " << countTokens.at("ID") << "\n";
  cout << "Count of Number: " << countTokens.at("NU") << "\n";
  cout << "Count of Literal: " << countTokens.at("LT") << "\n";
}

int main(){
  set<string> keyWords;
  set<string> specialSymbols;
  set<string> operators;
  map<string, string> tokens;

  map<string, int> countTokens;

  init(keyWords, specialSymbols, operators, tokens);
  initCount(countTokens);
  printDescription(keyWords, specialSymbols, operators, tokens);

  string input;
  while(getline(cin, input)){
    int size = input.size();
    int start = 0;

    while(start < size){
      while(start < size && input[start] == ' ') start++;
      if(start == size) break;

      int position = start;
      int num = (int)input[position];
      if((num >= 65 && num <= 90) || (num >= 97 && num <= 122)){
        // For getting tokens of keywords and identifiers
        while(position < size){
          num = (int)input[position];
          if(!((num >= 65 && num <= 90) || (num >= 97 && num <= 122) || (num >= 48 && num <= 57) || num == 95)) break;
          else position = position + 1;
        }

        string term = input.substr(start, position - start);
        if(keyWords.find(term) != keyWords.end()){
          print(tokens.at("KY"), term);
          updateCount("KY", countTokens);
        }else{
          print(tokens.at("ID"), term);
          updateCount("ID", countTokens);
        }

        start = position;
      }else if(num == 34){
        // For getting tokens of literals
        position = position + 1;
        while(position < size && input[position] != '"') position = position + 1;
        position = position + 1;

        string term;
        if(position - start == 2) term = "";
        else term = input.substr(start + 1, position - start - 1);
        print(tokens.at("LT"), term);
        updateCount("LT", countTokens);

        start = position;
      }else if(num == 39){
        // For getting tokens of literals
        position = position + 3;

        string term = input.substr(start + 1, 1);
        print(tokens.at("LT"), term);
        updateCount("LT", countTokens);

        start = position;
      }else if(num >= 48 && num <= 57){
        // For getting tokens of numbers
        while(position < size){
          num = (int)input[position];
          if(!((num >= 48 && num <= 57) || num == 46)) break;
          else position = position + 1;
        }

        string term = input.substr(start, position - start);
        print(tokens.at("NU"), term);
        updateCount("NU", countTokens);

        start = position;
      }else{
        string singleChar(1, input[position]);
        if(specialSymbols.find(singleChar) != specialSymbols.end()){
          // For getting tokens of special-characters
          string term = input.substr(start, 1);
          print(tokens.at("SP"), term);
          updateCount("SP", countTokens);

          start = position + 1;
        }else{
          // For getting tokens of operators
          while(position < size){
            string singleChar(1, input[position]);
            if(operators.find(singleChar) == operators.end()) break;
            else position = position + 1;
          }

          string term = input.substr(start, position - start);
          if(term == "//") break;
          print(tokens.at("OP"), term);
          updateCount("OP", countTokens);

          start = position;
        }
      }
    }
    cout << "\n\n";
  }

  printTokens(countTokens);
}