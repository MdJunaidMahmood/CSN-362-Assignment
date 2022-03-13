#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

void takeInput(map<char, vector<string>> &productions){
  string prodString;

  while(cin >> prodString){
    char start = prodString[0];
    int init = 3;
    int terminate = init;
    int length = prodString.size();

    vector<string> productionSet;
    while(terminate < length){
      if(prodString[terminate] == '|'){
        string str = prodString.substr(init, terminate - init);
        productionSet.push_back(str);
        init = terminate + 1;
      }

      terminate = terminate + 1;
    }
    productionSet.push_back(prodString.substr(init, terminate - init));
    productions.insert(pair<char, vector<string>>(start, productionSet));    
  }
}

void printProductions(map<char, vector<string>> productions){
  cout << "Production set provided as input is: \n";

  auto itr = productions.begin();
  while(itr != productions.end()){
    string production;
    production.assign(1, itr->first);

    production = production + "->";
    for(int i = 0; i < (itr->second).size(); i++){
      production = production + (itr->second)[i];
      production.push_back('|');
    }
    production.pop_back();
    cout << production << "\n";

    itr++;
  }

  cout << "\n\n";
}

set<char> findFirst(map<char, vector<string>> initialProductions, map<char, set<char>> &firstSet, char head){
  if(firstSet.find(head) != firstSet.end()) return (firstSet.find(head))->second;
  else{
    auto headItr = initialProductions.find(head);
    set<char> firstHead;
    
    int n = (headItr->second).size();
    for(int i = 0; i < n; i++){
      string right = (headItr->second)[i];
      int lenStr = right.size();
      int index = 0;

      while(index < lenStr){
        if(!(right[index] >= 'A' && right[index] <= 'Z')){
          firstHead.insert(right[index]);
          break;
        }
        
        bool flag = true;
        set<char> tempFirst = findFirst(initialProductions, firstSet, right[index]);
        auto itr = tempFirst.begin();
        while(itr != tempFirst.end()){
          if(*itr == '@') flag = false;
          else firstHead.insert(*itr);
          itr++;
        }

        if(flag) break;
        else index = index + 1;
      }

      if(index == lenStr) firstHead.insert('@');
    }

    firstSet.insert(pair<char, set<char>>(head, firstHead));
    return firstHead;
  }
}

void printFirstSet(map<char, set<char>> firstSet){
  cout << "First of each of the non-terminals in the productions set:\n";

  auto itr = firstSet.begin();
  while(itr != firstSet.end()){
    cout << itr->first;
    string right;
    right = " = {";
    auto tempItr = (itr->second).begin();
    while(tempItr != (itr->second).end()){
      right.push_back(*tempItr);
      right.push_back(',');
      right.push_back(' ');
      tempItr++;
    }
    right.pop_back();
    right.pop_back();
    right.push_back('}');

    cout << right << "\n";

    itr++;
  }

  cout << "\n\n";
}

int main(){
  map<char, vector<string>> initialProductions;
  takeInput(initialProductions);
  printProductions(initialProductions);

  map<char, set<char>> firstSet;
  auto itr = initialProductions.begin();
  while(itr != initialProductions.end()){
    char head = itr->first;
    if(firstSet.find(head) == firstSet.end()) findFirst(initialProductions, firstSet, head);
    itr++;
  }
  printFirstSet(firstSet);
}