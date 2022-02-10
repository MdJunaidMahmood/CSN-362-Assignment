I have executed the Converter.cpp in Linux Operating System. In order to do that just use the following set of commands:

1) g++ Converter.cpp -o convert.out
2) ./convert.out

Following points are noteworthy:
1) Input and output should be through command prompt as demonstrated in Sample_Run.png.
2) In input there should be no spaces between any operator, operand or parenthesis.
3) Only '(' and ')' are valid parenthesis.
4) Only +, -, *, / and ^ are valid operators.
5) Every operand has to be a single character only (For example, A, B, C, a, b, c, and so on).
6) ^ has highest precedence. It is followed by * and / both of which have same precedence. It is followed by + and - both of which have same precedence.
7) Above file was also executed successfully in an online compiler. The demonstration is shown in Online_Compiler_Run.png.