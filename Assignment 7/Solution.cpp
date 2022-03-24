#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

void takeInput(map<char, vector<string>> &productions, char &startSymbol){
  string prodString;
  bool flag = true;

  while(cin >> prodString){
    char start = prodString[0];
    int init = 3;
    int terminate = init;
    int length = prodString.size();

    vector<string> productionSet;
    if(productions.find(start) != productions.end()) productionSet = (productions.find(start))->second;

    while(terminate < length){
      if(prodString[terminate] == '|'){
        string str = prodString.substr(init, terminate - init);
        productionSet.push_back(str);
        init = terminate + 1;
      }

      terminate = terminate + 1;
    }
    productionSet.push_back(prodString.substr(init, terminate - init));


    if(productions.find(start) != productions.end()){
      auto del = productions.find(start);
      productions.erase(del);
    }
    productions.insert(pair<char, vector<string>>(start, productionSet));  

    if(flag){
      startSymbol = start;
      flag = false;
    }  
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
          if(*itr == '#') flag = false;
          else firstHead.insert(*itr);
          itr++;
        }

        if(flag) break;
        else index = index + 1;
      }

      if(index == lenStr) firstHead.insert('#');
    }

    firstSet.insert(pair<char, set<char>>(head, firstHead));
    return firstHead;
  }
}

bool isTerminal(char head){
  int num = (int)head;
  if(num >= 65 && num <= 90) return false;
  else return true;
}

set<char> findFollow(map<char, vector<string>> initialProductions, map<char, set<char>> &followSet, map<char, set<char>> firstSet, char head, char startSymbol){
  if(followSet.find(head) != followSet.end()) return (followSet.find(head))->second;

  set<char> follow;
  if(head == startSymbol) follow.insert('$');

  auto itr = initialProductions.begin();
  while(itr != initialProductions.end()){
    vector<string> productions = itr->second;
    
    for(int i = 0; i < productions.size(); i++){
      string str = productions[i];

      if(str.size() == 1 && str[0] == '#') continue;

      for(int j = 0; j < str.size(); j++){
        if(str[j] == head){
          int k = j + 1;
          bool flag = true;
          while(k < str.size() && flag){
            flag = false;
            if(isTerminal(str[k])){
              follow.insert(str[k]);
            }else{
              set<char> first;
              first = (firstSet.find(str[k]))->second;
              auto node = first.begin();
              while(node != first.end()){
                if(*node == '#') flag = true;
                else follow.insert(*node);

                node++;
              }
              k = k + 1;
            } 
          }

          if(flag && itr->first != head){
            set<char> obtain;
            obtain = findFollow(initialProductions, followSet, firstSet, itr->first, startSymbol);
            auto node = obtain.begin();
            while(node != obtain.end()){
              follow.insert(*node);
              node++;
            }
          }
          
          j = k;
        }
      }
    }

    itr++;
  }

  followSet.insert(pair<char, set<char>>(head, follow));
  return follow;
}

void printFollowSet(map<char, set<char>> followSet){
  cout << "Follow of each of the non-terminals in the productions set:\n";

  auto itr = followSet.begin();
  while(itr != followSet.end()){
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

    if((itr->second).begin() != (itr->second).end()){
      right.pop_back();
      right.pop_back();
      right.push_back('}');
    }else right.push_back('}');

    cout << right << "\n";

    itr++;
  }

  cout << "\n\n";
}

int main(){
  char startSymbol;

  map<char, vector<string>> initialProductions;
  takeInput(initialProductions, startSymbol);
  printProductions(initialProductions);

  map<char, set<char>> firstSet;
  auto itr = initialProductions.begin();
  while(itr != initialProductions.end()){
    char head = itr->first;
    if(firstSet.find(head) == firstSet.end()) findFirst(initialProductions, firstSet, head);
    itr++;
  }

  map<char, set<char>> followSet;
  itr = initialProductions.begin();
  while(itr != initialProductions.end()){
    char head = itr->first;
    if(followSet.find(head) == followSet.end()) findFollow(initialProductions, followSet, firstSet, head, startSymbol);
    itr++;
  }

  printFollowSet(followSet);

  
}