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
Form of data: (char) -> (tokens) -> (AST) -> (AST)

Text -> Tokens: Lexical Structure
