I have executed the Solution.cpp in Linux Operating System. In order to do that just use the following set of commands:
1) g++ Solution.cpp -o first.out
2) cat input.txt | ./first.out > output.txt

Here input.txt and output.txt refers to the input and output file respectively. Sample execution of the program is demonstarted in "Sample_Run.png".

Following points are noteworthy:
1) Empty String is represented by @. All capital English alphabets represent Non-Terminals and any other symbol representes Terminals.
2) It has been assumed that the grammar is not left recursive.
3) The input should strictly follow the following format:
  (a) Only a single character (A, B, C,..., Z) is allowed as a non-terminal.
  (b) Each non-terminal must be followed by ->.
  (c) All productions corresponding to a single non-terminal must be in one line, seperated by | symbol.
  (d) Productions of two different non-terminals must be in two different line.
  (e) Spaces should not be present anywhere. There should neither be any spaces between -> and first production, nor between any two productions seperated by |. There should not be any spaces between non terminal and ->.
4) "input.txt" and "output.txt" contains sample input and output file.