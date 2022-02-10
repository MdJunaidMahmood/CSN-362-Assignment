#include <cmath>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

string infixToPostfix(string infix){
  int n = infix.size();
  string postfix = "";

  stack<char> opStack;

  for(int i = 0; i < n; i++){
    char ch = infix[i];

    if(ch == '('){
      opStack.push('(');
    }else if(ch == ')'){
      char opChar = opStack.top();
      while(opChar != '('){
        postfix.push_back(opChar);
        opStack.pop();
        opChar = opStack.top();
      }
      opStack.pop();
    }else if(ch == '^'){
      if(opStack.size() > 0){
        char opChar = opStack.top();
        while(opChar == '^'){
          postfix.push_back(opChar);
          opStack.pop();
          if(opStack.size() == 0) break;
          else opChar = opStack.top();
        }
      }
      opStack.push(ch);
    }else if(ch == '/' || ch == '*'){
      if(opStack.size() > 0){
        char opChar = opStack.top();
        while(opChar == '^' || opChar == '/' || opChar == '*'){
          postfix.push_back(opChar);
          opStack.pop();
          if(opStack.size() == 0) break;
          else opChar = opStack.top();
        }
      }
      opStack.push(ch);
    }else if(ch == '+' || ch == '-'){
      if(opStack.size() > 0){
        char opChar = opStack.top();
        while(opChar == '^' || opChar == '/' || opChar == '*' || opChar == '+' || opChar == '-'){
          postfix.push_back(opChar);
          opStack.pop();
          if(opStack.size() == 0) break;
          else opChar = opStack.top();
        }
      }
      opStack.push(ch);
    }else{
      postfix.push_back(ch);
    }
  }

  while(opStack.size() != 0){
    postfix.push_back(opStack.top());
    opStack.pop();
  }

  return postfix;
}


string postfixToPrefix(string postfix){
  int n = postfix.size();
  string prefix = "";

  stack<string> strStack;

  for(int i = 0; i < n; i++){
    char ch = postfix[i];
    
    if(ch == '^' || ch == '/' || ch == '*' || ch == '+' || ch == '-'){
      string first = strStack.top();
      strStack.pop();

      string second = strStack.top();
      strStack.pop();

      string operand = postfix.substr(i, 1);
      string newTop = operand + second + first;
      strStack.push(newTop);
    }else{
      string newTop = postfix.substr(i, 1);
      strStack.push(newTop);
    }
  }

  while(strStack.size() != 0){
    prefix = strStack.top() + prefix;
    strStack.pop();
  }

  return prefix;
}


int main(){
  string infix, postfix, prefix;

  cout << "Enter Infix Expression: ";
  cin >> infix;

  postfix = infixToPostfix(infix);
  cout << "Infix to Postfix Conversion: " << infix << " is converted to " << postfix << "\n";

  prefix = postfixToPrefix(postfix);
  cout << "Postfix to Prefix Conversion: " << postfix << " is converted to " << prefix << "\n";

  return 0;
}