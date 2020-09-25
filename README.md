# BracketBug
Little C program which scans the output of a file and tells you which line in an output, you have an open bracket.

# How to use


------------

Compile the program using any C compiler.
`cc bracket-debugger.c`

Then pipe your c program into the compiled program.
`cat test.c | bracket-debugger.out`

The output will print errors to the console.
This current version only works for square, curly and round brackets.
