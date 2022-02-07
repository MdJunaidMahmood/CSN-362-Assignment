%{
  #include <stdio.h>
	#include <string.h>

  /* NUMBER Symbol Table */
  int integerSymbolTable[1000];
  int i3 = 0;
  double doubleSymbolTable[1000];
  int i4 = 0;
  int intType[1000];
  int index1 = 0;

  /*  LITERAL Symbol Table */
  char stringSymbolTable[1000][100] = {""};
  int i1 = 0;
  char characterSymbolTable[1000];
  int i2 = 0;
  int charType[1000];
  int index2 = 0;

  /* Identifier Symbol Table */
  char identifierSymbolTable[1000][100] = {""};
  int i5 = 0;

  int getToken(char *str){
    char ifKey[10] = "if";
    char elseKey[10] = "else";
    char whileKey[10] = "while";
    char thenKey[10] = "then";

    if(strcmp(str, ifKey) == 0) return 0;
    if(strcmp(str, elseKey) == 0) return 0;
    if(strcmp(str, whileKey) == 0) return 0;
    if(strcmp(str, thenKey) == 0) return 0;

    return 1;
  }

  int installID(char *lexeme){
    for(int i = 0; i < i5; i++){
      if(strcmp(lexeme, identifierSymbolTable[i]) == 0) return i;
    }

    strcpy(identifierSymbolTable[i5], yytext);
    int index = i5;
    i5 = i5 + 1;
    return index;
  }

  int installNum(int flag, int valueInt, double valueDouble){
    if(flag == 0){
      for(int i = 0; i < i3; i++){
        if(valueInt == integerSymbolTable[i]){
          int j = -1;
          int counter = 0;
          while(j != i){
            if(intType[counter] == 1) j = j + 1;
            counter = counter + 1;
          }
          counter = counter - 1;
          return counter;
        }
      }
    }else{
      for(int i = 0; i < i4; i++){
        if(valueDouble == doubleSymbolTable[i]){
          int j = -1;
          int counter = 0;
          while(j != i){
            if(intType[counter] == 0) j = j + 1;
            counter = counter + 1;
          }
          counter = counter - 1;
          return counter;
        }
      }
    }

    int index = index1;
    if(flag == 0){
      integerSymbolTable[i3] = valueInt;
      i3 = i3 + 1;

      intType[index1] = 1;
      index1 = index1 + 1;
    }else{
      doubleSymbolTable[i4] = valueDouble;
      i4 = i4 + 1;

      intType[index1] = 0;
      index1 = index1 + 1;
    }

    return index;
  }

  int installString(int flag, char valueChar, char *valueString){
    if(flag == 0){
      for(int i = 0; i < i2; i++){
        if(valueChar == characterSymbolTable[i]){
          int j = -1;
          int counter = 0;
          while(j != i){
            if(charType[counter] == 1) j = j + 1;
            counter = counter + 1;
          }
          counter = counter - 1;
          return counter;
        }
      }
    }else{
      for(int i = 0; i < i1; i++){
        if(strcmp(valueString, stringSymbolTable[i]) == 0){
          int j = -1;
          int counter = 0;
          while(j != i){
            if(charType[counter] == 0) j = j + 1;
            counter = counter + 1;
          }
          counter = counter - 1;
          return counter;
        }
      }
    }

    int index = index2;
    if(flag == 0){
      characterSymbolTable[i2] = valueChar;
      i2 = i2 + 1;

      charType[index2] = 1;
      index2 = index2 + 1;
    }else{
      strcpy(stringSymbolTable[i1], valueString);
      i1 = i1 + 1;

      charType[index2] = 0;
      index2 = index2 + 1;
    }

    return index;
  }
%}

/* regular definitions */
delim [ \t]
ws {delim}+
newLine [\n]
letter [A-Za-z]|[_]
digit [0-9]
id {letter}({letter}|{digit})*
integerNum [-]?{digit}+
fractionNum [-]?{digit}+((\.{digit}+)|(E[+-]?{digit}+)|(\.{digit}+)(E[+-]?{digit}+))
charLiteral \'((.)|(\\(.)))\'
stringLiteral ([\"])(.)*([\"])
doubleq \"
if if
then then
else else
while while
relop <|<=|>|>=|==|!=

%%
{ws} {}
{newLine} {printf("\n\n");}
{if} {printf("<IF> ");}
{then} {printf("<THEN> ");}
{else} {printf("<ELSE> ");}
{while} {printf("<WHILE> ");}

{relop} {
  char LT[3] = "<";
  int result1 = strcmp(yytext, LT);
  if(result1 == 0) printf("<LT, RELOP> ");

  char LE[3] = "<=";
  int result2 = strcmp(yytext, LE);
  if(result2 == 0) printf("<LE, RELOP> ");

  char EQ[3] = "==";
  int result3 = strcmp(yytext, EQ);
  if(result3 == 0) printf("<EQ, RELOP> ");

  char GE[3] = ">=";
  int result4 = strcmp(yytext, GE);
  if(result4 == 0) printf("<GE, RELOP> ");

  char GT[3] = ">";
  int result5 = strcmp(yytext, GT);
  if(result5 == 0) printf("<GT, RELOP> ");

  char NQ[3] = "!=";
  int result6 = strcmp(yytext, NQ);
  if(result6 == 0) printf("<NE, RELOP> ");
}

{id} {
  int value = getToken(yytext);
  int index = installID(yytext);
  printf("<ID, Value: %s, Identifier Symbol Table Entry: %d>", yytext, index);
}

{integerNum} { 
  int value = atoi(yytext);
  int index = installNum(0, value, 0.0);
  
  printf("<NUMBER, Value: %d, Number Symbol Table Entry: %d> ", value, index);
}

{fractionNum} {
  double value;
  sscanf(yytext, "%lf", &value);

  int index = installNum(1, 0, value);
  printf("<NUMBER, Value: %lf, Number Symbol Table Entry: %d> ", value, index);
}

{charLiteral} {
  char ch;
  if(yytext[1] == 92) ch = yytext[2];
  else ch = yytext[1];

  int index = installString(0, ch, yytext);
  printf("<STRING, Value: %c, Literal Symbol Table Entry: %d>", ch, index);
  
}

{stringLiteral} {
  char sample[100];
  int flag = 0;
  int counter = 0;
  int i = 1;

  while(i < yyleng - 1){
    if(yytext[i] == 92){
      sample[counter] = yytext[i + 1];
      i = i + 2;
      counter = counter + 1;
    }else{
      sample[counter] = yytext[i];
      i = i + 1;
      counter = counter + 1;
    }
  }

  sample[counter] = '\0';

  int index = installString(1, yytext[0], sample);
  printf("<STRING, Value: %s, Literal Symbol Table Entry: %d>", sample, index);
}

%%

int yywrap(){}

int main(){
	yylex();
  printf("\n----------------------------------------------------\n");
  printf("Literal Symbol Table:\n");
  int a = 0;
  int b = 0;
  for(int i = 0; i < index2; i++){
    if(charType[i] == 1){
      printf("Index: %d, Value: %c\n", i, characterSymbolTable[a]);
      a = a + 1;
    }else{
      printf("Index: %d, Value: %s\n", i, stringSymbolTable[b]);
      b = b + 1;
    }
  }

  printf("\n----------------------------------------------------\n");
  printf("Number Symbol Table:\n");
  a = 0;
  b = 0;
  for(int i = 0; i < index1; i++){
    if(intType[i] == 1){
      printf("Index: %d, Value: %d\n", i, integerSymbolTable[a]);
      a = a + 1;
    }else{
      printf("Index: %d, Value: %lf\n", i, doubleSymbolTable[b]);
      b = b + 1;
    }
  }

  printf("\n----------------------------------------------------\n");
  printf("Identifier Symbol Table:\n");
  for(int i = 0; i < i5; i++){
    printf("Index: %d, Value: %s\n", i, identifierSymbolTable[i]);
  }

	return 0;
}