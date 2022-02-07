I have basically executed the file in Linux Operating System. I have taken input through a file "input.txt" and saved output in another file "output.txt".
In order to do that, I have executed following instructions:

1) lex Solution.l
2) gcc lex.yy.c -o regex.out
3) cat input.txt | ./regex.out > output.txt

I have given a sample input file named "input.txt" and corresponding output file named "output.txt".

Following Points are Noteworthy:
1) To maintain uniformity I have adopted following convention:
    (a) Any character (for example, 'a') or any string (for example, "Apple") will be represented by the token "STRING".
    (b) Any real number will be represented by the token "NUMBER".
    (c) Any identifier will bre represented by the token "ID".
2) If any value is entered such that it is already present in the symbol table of the corresponding token, then instead of creating new index for that value in symbol table, already existing index will be printed.
3) Contents of all the three Symbol Table are printed at the end.
