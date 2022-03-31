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

void printAugmentation(char startSymbol){
  string output;
  output.assign(1, startSymbol);
  output.push_back('\'');
  output.push_back('-');
  output.push_back('>');
  output.push_back(startSymbol);

  cout << output << "\n";
}

void generateItems(multimap<char, vector<string>> &items, map<char, vector<string>> productions){
  auto prod = productions.begin();

  while(prod != productions.end()){
    char head = prod->first;
    vector<string> productionVector;
    productionVector = prod->second;

    for(int i = 0; i < productionVector.size(); i++){
      string str = productionVector[i];
      if(str.size() == 1 && str[0] == '#'){
        vector<string> strVector;
        strVector.push_back(".");
        items.insert(pair<char, vector<string>>(head, strVector));
      }else{
        vector<string> strVector;

        int n = str.size();
        for(int j = 0; j < n; j++){
          string first;
          string second;

          first = str.substr(0, j);
          second = str.substr(j, n - j);

          string finalString;
          finalString = first + "." + second;
          strVector.push_back(finalString);
        }

        string finalString;
        finalString = str + ".";
        strVector.push_back(finalString);

        items.insert(pair<char, vector<string>>(head, strVector));
      }
    }

    prod++;
  }
}

void printAugmentedProductionItems(char startSymbol){
  string output;
  output.assign(1, startSymbol);
  output.push_back('\'');
  output.push_back('-');
  output.push_back('>');

  output.push_back('.');
  output.push_back(startSymbol);
  output.push_back('|');
  output.push_back(startSymbol);
  output.push_back('.');

  cout << output << "\n";
}

void printItems(multimap<char, vector<string>> items){
  auto itr = items.begin();
  while(itr != items.end()){
    char head = itr->first;
    string output;
    output.assign(1, head);
    output.push_back('-');
    output.push_back('>');

    vector<string> itemsVector;
    itemsVector = itr->second;

    int i = 0;
    for(i = 0; i < itemsVector.size() - 1; i++){
      output = output + itemsVector[i];
      output.push_back('|');
    }
    output = output + itemsVector[itemsVector.size() - 1];

    cout << output << "\n";
    itr++;
  }

  cout << "\n";
}

int main(){
  char startSymbol;
  map<char, vector<string>> initialProductions;
  takeInput(initialProductions, startSymbol);
  cout << "Grammar provided as input is: \n";
  printProductions(initialProductions);

  cout << "Grammar after augmentation is: \n";
  printAugmentation(startSymbol);
  printProductions(initialProductions);

  multimap<char, vector<string>> items;
  generateItems(items, initialProductions);

  cout << "List of all LR(0) items for the augmented grammar: \n";
  printAugmentedProductionItems(startSymbol);
  printItems(items);
}