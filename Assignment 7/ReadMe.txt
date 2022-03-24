I have executed the Solution.cpp in Linux Operating System. In order to do that just use the following set of commands:
1) g++ Solution.cpp -o follow.out
2) cat input.txt | ./follow.out > output.txt

Here input.txt and output.txt refers to the input and output file respectively. Sample execution of the program on the 4 given textcases is demonstarted in "Sample_Run" folder.

Following points are noteworthy:
1) Empty String is represented by #. All capital English alphabets represent Non-Terminals and any other symbol represents Terminals.
2) It has been assumed that the grammar is not left recursive.
3) The input should strictly follow the following format:
  (a) Only a single character (A, B, C,..., Z) is allowed as a non-terminal.
  (b) Each non-terminal must be followed by -> without any space or other character.
  (c) Spaces should not be present anywhere. There should neither be any spaces between -> and first production, nor between any two productions seperated by |. There should not be any spaces between non terminal and ->.
4) "input.txt" and "output.txt" contains sample input and output file respectively.