I have executed the Solution.cpp in Linux Operating System. In order to do that just use the following set of commands:
1) g++ Solution.cpp -o solution.out
2) cat input.txt | ./solution.out > output.txt

Here input.txt and output.txt refers to the input and output file respectively. Sample execution of the program on the given textcases is demonstarted in "Sample_Run.png" file.

Following points are noteworthy:
1)Empty String is represented by #. All capital English alphabets (such as, A, B, C,..., Z) represent Non-Terminals and any other symbol representes Terminals. Only exception to this rule is Non-Terminal E' (where E is variable representing Start Symbol of the Grammar). This Non-Terminal is necessary for augmenting the grammar.

2)The input should strictly follow the following format:
  (a) Each non-terminal must be followed by -> without any space or other character.
  (b) Spaces should not be present anywhere. There should neither be any spaces between -> and first production, nor between any two productions seperated by |. There should not be any spaces between non terminal and ->.

3)"input.txt" and "output.txt" contains sample input and output file. It must be noted that an unaugmented grammar must be given as input as augmentation is done inside the program.