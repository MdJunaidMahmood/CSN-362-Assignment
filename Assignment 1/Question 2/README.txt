I have basically executed the file in Linux Operating System. I have taken input through a file "input.txt" and saved output in another file "output.txt".
In order to do that, I have executed following instructions:

1) g++ Ques2.cpp -o ques2.out
2) cat input.txt | ./ques2.out > output.txt


Here input.txt is the name of the input file. File in which input is present.
Here output.txt is the name of the output file. File in which output will be saved.

If output is desired in command line, run the following instead of command 2: cat input.txt | ./ques2.out

In addition, lexical analysis is done considering user has given an correct sequence of input. If there is an error in the input program, then my code will not be able to highlight that.
