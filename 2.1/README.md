# Chapter 2.1, a simple lexical analyzer
Takes `program.txt` as input, returns a list of token class->representation

## How to run:
* run `make` from the command line
* run `./lex`

## Chapter 2.1 Notes
* front end - stream of characters->AST
* parse tree contains all grammar expressions
* abtract syntax tree contains just neccessary info

* annotated AST - from parsing to code generation, annotation grows

Phases: Input -> Lexical Analysis -> Syntax Analysis -> Context Handling -> Annotated AST

Annotated AST is the goal of a compiler front end

Form of data: (char) -> (tokens) -> (AST) -> (AST)

Text -> Tokens: Lexical Structure

### Reading in the file
* should read in entire file with one system call
* as long as there is enough memory, it is the fastest method
* ex. no need to read string in one char at a time, entails complicated memory tricks
* instead read whole file, read beginnning of string, find length, and alocate
* or just point to beginning of string in memory, with length of string

### Newlines
* newlines = headaches, not standardized, instead convert to fixed internal format ASAP
* convenient format if single array for chars, each line consecutive terminated with a newline char

### Tokens
if it can be separated from neighbors with whitespace, it is a token
```C
struct Token {
  class
  repr
  filename
  line #
}
```

### Basic task of Lexical Analyzer
* Given set S of token descriptions, and position P in input stream, determine which of the regular expressions in S will match a segment of the input starting at P and what that segment is.
* we want the longest segment match possible.
