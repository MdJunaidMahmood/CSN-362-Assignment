/*** Definition Section ***/
%{
  int num = 0;
%}

/*** Rule Section ***/
%%
(a([a])*b([a])*b([a])*baa) {printf("Language L1, L2, L3, L4 found: ");
ECHO;
num = 1;
}
(a([a])*b([a])*bba) {printf("Language L1, L2, L3, L4 found: ");
ECHO;
num = 1;
}

(a([ab])*b[ab]a) {printf("Language L1, L2, L3 found: ");
ECHO;
num = 1;
}

(a([a])*b([a])*b([a])*b([a])*a) {printf("Language L1, L2, L4 found: ");
ECHO;
num = 1;
}

(([a])*b([a])*b([a])*baa) {printf("Language L2, L3, L4 found: ");
ECHO;
num = 1;
}
(([a])*b([a])*b(ab|ba)) {printf("Language L2, L3, L4 found: ");
ECHO;
num = 1;
}
(([a])*bbb) {printf("Language L2, L3, L4 found: ");
ECHO;
num = 1;
}

([a](.)*[a])|([a]) {printf("Language L1, L2 found: ");
ECHO;
num = 1;
}

(([ab])*[b][ab][ab]) {printf("Language L2, L3 found: ");
ECHO;
num = 1;
}

(([a])*[b]([a])*[b]([a])*[b]([a])*) {printf("Language L2, L4 found: ");
ECHO;
num = 1;
}

([ab])+ {printf("Language L2 found: ");
ECHO;
num = 1;
}

([ ]*[\n]) {if(num == 0){
printf("No Language found for an empty string\n\n");
}else{
  printf("\n\n");
  num = 0;
}
}
%%

int yywrap(){}
/*** Code Section ***/

int main(){
  yylex();
  return 0;
}
