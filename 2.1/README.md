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

### Summary - Lexical Analysis
* lexical analysis character stream into token stream
* syntax analysis turns stream of tokens into parse tree, or abstract syntax tree
* these phases effectively undo the linear sequencing of the program as it was written
* abstract syntax tree = only semantically important nodes
* simplify source program processing by reading in entire program to memory - helps memory management, token isolation, file position tracking, and error reporting
* stadnardize newline characters as soon as encountered
* tokens = class, representation, position
* form of tokens are as described by its regular expression
* lexical analyzer is repeating pattern matcher, matches tokens to token patterns of source language
* ambigous patterns are resolved by matching longest pattern
* lexical analyzers can be handwritten or generated
* handwritten lexical analyzers make decision based on first token, then ad-hoc code thereafter
* lexical analyzer is only part of compiler that sees every part of source program, so it does magnitudes more work than other parts of compiler
* much computation of lexical analyzer can be replaced by precomputed tables, increasing efficiency
* resulting tables allow/require compression
* generated lexical analyzers represent knowledge as set of items, regexps with dots indiciating matched expressions and to-be-matched following expressions
* this is called the shift-reduce pattern, and can be avoided by precomputing states and transitions
* states, transition tables, and transition mechanism are toegther called a Finite State Automota FSA
* handwritten lexical anayzers and generated FSAs can be close in efficiency
* transition tables are mostly empty entries, can be compressed by cutting up into rows/columns, then fitting other rows/columns into each other by shifting starting positions of the columns/rows
* another compression scheme, fit groups together using graph coloring, then suprimpose those rows/columns
* identifiers must often be identified further before being passed to syntax analyzer, having to be looked up in a symbol table
* this can serve as a type identifier, keyword identification, macro processing, conditional compilation, and file inclusion
* symbol table = extensible array of records indexed by string. string is identifier and corresponding record holds info about identifier
* string indexable arrays can be implemented using hashing
* macro substitution, macro parameter expansion, conditional compilation, and file inclusion can be implemented simultaneously using a single stack of input buffers.
* generics can often be implemented by using file inclusion and macro processing. makes generics a form of token insertion, between the lecial and syntax analyzer

### Summary - Parsing
* two ways of parsing - bottom up and top down
* top down = mimics program production process
* bottom up = tries to roll back program production process
* top down parsers can be written manually or generated automatically from a CFG
* handwritten top-down parser consists of a set of recursive routines, corresponding to rules in grammar - called a Recursive Descent parser
* generated top-down parsers use precomputation, unambiguous transition tables are obtained for LL(1) grammars only
* construction of table is based on FIRST and FOLLOW sets of non-terminals.
* FIRST = all tokens a production of N can start with
* FOLLOW = contains all tokens that can follow any production of N
* LL(1) conflicts can be resolved by substitution, left-factoring, and left-recursion removal
* LL(1) parsers can recover from errors by plotting shortest path out, deleting input tokens until acceptable token is found (acceptable set error recovery)
* bottom-up parsers work by repeatedly identifying a handle ( list of children of last node expanded in producing program), then reduce it to parent node and repeat process
* finding handle is the problem, many approximative techniques
* LR parsing techniques use item set of proposed handles
* LR arser can shift or reduce by consulting ACTION table, if shifting use GOTO table. for LR parsers with 1 token lookahead, ACTION and GOTO tables cna be superimposed
* LALR(1) item set and tables obtained by combining LR(1) item sets that differ in lookahead sets only. reduces table size to LR(0) parsers, keeps almost all parsing power
* LR item has shift/reduce conflict if both shift and reduce are orded by item. resolve by always preferring shift over reduce.
* reduce/reduce conflict if item orders two different reduces. resolve by accept longest sequence of tokens, precedence can also help
* error recovery for LR parser is difficult, one approach is to unroll error-recovering states, install dummy node, then continue on 
