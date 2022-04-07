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

  cout << "\n";
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
          if(*itr == '^') flag = false;
          else firstHead.insert(*itr);
          itr++;
        }

        if(flag) break;
        else index = index + 1;
      }

      if(index == lenStr) firstHead.insert('^');
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

  cout << "\n";
}

bool isTerminal(char head){
  if(head == '^') return false;

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

      if(str.size() == 1 && str[0] == '^') continue;

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
                if(*node == '^') flag = true;
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

  cout << "\n";
}

void findTerminals(set<char> &terminals, map<char, vector<string>> initialProductions){
  auto itr = initialProductions.begin();
  while(itr != initialProductions.end()){
    vector<string> right = itr->second;
    for(int i = 0; i < right.size(); i++){
      string prod = right[i];
      for(int j = 0; j < prod.size(); j++){
        if(isTerminal(prod[j])) terminals.insert(prod[j]);
      }
    }
    itr++;
  }
}

void findNonTerminals(set<char> &nonTerminals, map<char, set<char>> firstSet){
  auto itr = firstSet.begin();
  while(itr != firstSet.end()){
    nonTerminals.insert(itr->first);
    itr++;
  }
}

void createPredictiveParsingTable(map<char, vector<string>> initialProductions, map<char, set<char>> followSet, map<char, set<char>> firstSet, map<char, map<char, set<string>>> &table, set<char> terminals){
  auto nonTerminal = initialProductions.begin();
  while(nonTerminal != initialProductions.end()){
    char head = nonTerminal->first;
    vector<string> productionSet = nonTerminal->second;

    map<char, set<string>> rowMap;
    auto term = terminals.begin();
    while(term != terminals.end()){
      set<string> termSet;
      rowMap.insert(pair<char, set<string>>(*term, termSet));
      term++;
    }

    for(int i = 0; i < productionSet.size(); i++){
      string prod = productionSet[i];
      set<char> first;

      int j = 0;
      for(j = 0; j < prod.size(); j++){
        if(prod[j] == '^'){
          continue;
        }else if(isTerminal(prod[j])){
          first.insert(prod[j]);
          break;
        }else{
          set<char> addOnFirst = (firstSet.find(prod[j]))->second;
          bool flag = true;
          auto itr = addOnFirst.begin();
          while(itr != addOnFirst.end()){
            if(*itr == '^') flag = false;
            else first.insert(*itr);
            itr++;
          }

          if(flag) break;
        }
      }

      if(j == prod.size()){
        set<char> addOnFollow = (followSet.find(head))->second;
        
        auto itr = addOnFollow.begin();
        while(itr != addOnFollow.end()){
          first.insert(*itr);
          itr++;
        }
      }

      auto itr = first.begin();

      while(itr != first.end()){
        set<string> temp = (rowMap.find(*itr))->second;
        temp.insert(prod);

        auto del = rowMap.find(*itr);
        rowMap.erase(del);

        rowMap.insert(pair<char, set<string>>(*itr, temp));
        itr++;
      }
    }

    table.insert(pair<char, map<char, set<string>>>(head, rowMap));
    nonTerminal++;
  } 
}

string addSpace(string str){
  int global = 12;
  int size = str.size();

  string retStr;
  for(int i = size + 1; i <= global; i++) retStr = retStr +  " ";

  return retStr;
}

void printPredictiveParsingTable(map<char, map<char, set<string>>> table, set<char> terminals, set<char> nonTerminals){
  cout << "Predictive Parsing Table for the given Grammar: \n";

  string spaceLine;
  spaceLine = "\n\n";
  
  cout << "     ";
  auto itr = terminals.begin();
  while(itr != terminals.end()){
    string start;
    start.push_back(*itr);
    cout << start << addSpace(start);

    itr++;
  }

  itr = nonTerminals.begin();
  while(itr != nonTerminals.end()){
    cout << spaceLine;
    string head;
    head.push_back(*itr);
    cout << head << "    ";

    string str;
    map<char, set<string>> rowMap = (table.find(*itr))->second;
    auto term = terminals.begin();
    while (term != terminals.end()){
      if(((rowMap.find(*term))->second).size() == 0) str = str + addSpace("");
      else{
        string prod;
        prod = head + "->";
        auto tempSet = ((rowMap.find(*term))->second).begin();
        while(tempSet != ((rowMap.find(*term))->second).end()){
          prod = prod + *tempSet;
          prod.push_back('|');
          tempSet++;
        }
        prod.pop_back();

        str = str + prod + addSpace(prod);
      }
      term++;
    }
    cout << str;
    itr++;
  }

  cout << "\n";
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

  printFirstSet(firstSet);
  map<char, set<char>> followSet;
  itr = initialProductions.begin();
  while(itr != initialProductions.end()){
    char head = itr->first;
    if(followSet.find(head) == followSet.end()) findFollow(initialProductions, followSet, firstSet, head, startSymbol);
    itr++;
  }
  
  printFollowSet(followSet);

  set<char> terminals;
  findTerminals(terminals, initialProductions);
  terminals.insert('$');

  set<char> nonTerminals;
  findNonTerminals(nonTerminals, firstSet);

  map<char, map<char, set<string>>> table;
  createPredictiveParsingTable(initialProductions, followSet, firstSet, table, terminals);

  printPredictiveParsingTable(table, terminals, nonTerminals);
}