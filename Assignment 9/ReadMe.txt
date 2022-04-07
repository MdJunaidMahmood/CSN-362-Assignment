I have executed the Solution.cpp in Linux Operating System. In order to do that just use the following set of commands:
1) g++ Solution.cpp -o solution.out
2) cat input.txt | ./solution.out > output.txt

Here input.txt and output.txt refers to the input and output file respectively. In the output, input grammar, first set, follow set and predictive parsing table has been printed. Sample execution of the program on the given textcase is demonstarted in "Sample_Input.png" and "Sample_Output.png"file.

Following points are noteworthy:
1)Empty String is represented by ^. All capital English alphabets (such as, A, B, C,..., Z) represent Non-Terminals and any other symbol representes Terminals. A terminal can only be a single character.

2)It has been assumed that the grammar is not left recursive. This is a necessary condition for calculating first and follow set of the grammar by the program.

3)The input should strictly follow the following format:
  (a) Each non-terminal must be followed by -> without any space or other character.
  (b) Spaces should not be present anywhere. There should neither be any spaces between -> and first production, nor between any two productions seperated by |. There should not be any spaces between non terminal and ->.

4)It must be noted that a maximum size of 12 spaces has been given for each entry in the predictive parsing table. Thus, in order to view the table correctly size of production in a particular entry should not exceed 12. If size exceeds this limit, then variable "global" (in the function addSpace(string str)) at line number 321 in the source code must be changed accordingly.

5)"input.txt" and "output.txt" contains sample input and output file.