#include <iostream>
#include <stack>
#include <string>
using namespace std;

string reverseTheString(string str){
  int n = str.size();
  string retString;

  for(int i = n - 1; i >= 0; i--){
    if(str[i] == '(') retString.push_back(')');
    else if(str[i] == ')') retString.push_back('(');
    else retString.push_back(str[i]);
  }

  return retString;
}

int main(){
  string input;
  cout << "Enter The String: ";
  getline(cin, input);
  cout << "Infix Notation given as Input: " << input << "\n";

  input = reverseTheString(input);
  
  stack<char> stack;
  string postfix;

  for(int i = 0; i < input.size(); i++){
    if(input[i] == ' ') continue;
    else if(input[i] == '('){
      stack.push('(');
    }else if(input[i] == ')'){
      while(stack.size() > 0 && stack.top() != '('){
       postfix.push_back(stack.top());
       stack.pop(); 
      }
      stack.pop();
    }else if(input[i] == '/'){
      stack.push('/');
    }else if(input[i] == '*'){
      while(stack.size() > 0 && stack.top() == '/'){
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.push('*');
    }else if(input[i] == '+'){
      while(stack.size() > 0 && stack.top() == '/'){
        postfix.push_back(stack.top());
        stack.pop();
      }
      while(stack.size() > 0 && stack.top() == '*'){
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.push('+');
    }else if(input[i] == '-'){
      while(stack.size() > 0 && stack.top() == '/'){
        postfix.push_back(stack.top());
        stack.pop();
      }
      while(stack.size() > 0 && stack.top() == '*'){
        postfix.push_back(stack.top());
        stack.pop();
      }
      while(stack.size() > 0 && stack.top() == '+'){
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.push('-');
    }else{
      postfix.push_back(input[i]);
    }
  }
  
  while(stack.size() != 0){
    postfix.push_back(stack.top());
    stack.pop();
  }

  string prefix = reverseTheString(postfix);
  cout << "Corresponding Prefix Notation: " << prefix << "\n";
}