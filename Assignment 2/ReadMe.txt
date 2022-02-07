I have basically executed the file in Linux Operating System. I have taken input through a file "input.txt" and saved output in another file "output.txt".
In order to do that, I have executed following instructions:

1) lex Solution.l
2) gcc lex.yy.c -o regex.out
3) cat input.txt | ./regex.out > output.txt 

Here input.txt is the name of the input file. It is the file in which input is present.
Here output.txt is the name of the output file. It is the file in which output will be saved.

Following points are noteworthy:
1) If output is desired in command line instead of a seperate file, run the following instead of command 3: cat input.txt | ./regex.out
2) Empty string is not a part of any language L1, L2, L3 and L4.
3) In order to give empty string as an input, just press an additional enter into the "input.txt" file, as shown in the "Additional_TestCase.png"
4) Definitions of L1, L2, L3 and L4 are:
  L1 = String of a's or b's that start and end with a.
  L2 = String of a's or b's.
  L3 = String of a's or b's that the character third from the last is b.
  L4 = String of a's or b's that only contains three b.

