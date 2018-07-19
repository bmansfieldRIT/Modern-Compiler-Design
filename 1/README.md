## Chapter 1
* Compilation - fast execution
* Interpretation - slow execution

* Regular expressions -> lexical analysis
* Context Free Grammars -> Syntax Analysis
* Attribute Grammars -> used for context, could be used for code generation/interpretation, but there are better ways
* Code Generation -> messy when manual, but can be automated - no widely accepted formalisms


#### Program generators
* regexp ->lexical analysis
* grammar -> parsers
* machine descriptions -> code generation
* Pros: more reliable, easier to debug, correctness, modifiability, formal descriptions can generate many useful programs

#### data structures in compilers:
* hashing
* precompiled tables
* stack mechanisms
* garbage collection
* dynamic programming
* graph algorithms

#### Intermediate Code:
1. linked lists of psuedo instructions
2. annotated abstract syntax trees
3. many others

* syntax tree = parse tree
* parsing = syntax analysis

* ast usually means annotated w more info about semantics
* annotations: type information
* attributes: optimized info
  handled by context handling module
  
* lexical analyzer - tokenizes input
* syntax analysis - structures input into AST

* recursive descent parsing - sonstruct parse tree by descending recursively
  - weak method, inferior error handling
  - very simple to implement
* predictive rdp - use lookahead sets, implementation of LL(1) parsing

#### modules of a compiler
* program text input - find file, read efficiently, turn into stream of tokens
* lexical analaysis module - isolate tokens in a stream, determine class
* syntax analysis - convert stream of tokens into AST
* context handling module - collext context info, attatch to nodes (type, goto label)
* intermediate code generation - convert language specific constructs into generalized form
  - usually IC is only control-flow and expressions
* IC optimization - preprocess IC, constant folding etc.
* code generation - rewrite AST into linear symbolic instructions for target machine
* target code optimization - uses target machine specific properties
* machine code generation - convert symbolic instruction into corresponding bit patterns
* executable code output - combine instructions, headers, tables etc. into an exe

#### runtime systems
* need machine dependant instructions/routines during runtime
* allocating arrays, manipulating stack frames, etc.
* compile those routines once, reference as libraries = runtime system
* parts of library can be linked in using a linker, or used dynamically

* generating machine code / executable code = use local assembler
* backend can be replaced by just generating C code from IC

#### Compiler Architectures
* width of a program - granularity of data passed between modules
* size of data - smallest meaningful unit, or entire program?

* narrow compiler - read small part of program, process, produce few bytes of instruction code, discard extra info
* broad compiler - read entire program, process, produce all instr code
* narrow + broad - read routine, process, produce code, keep global data about routine

* real compilers are often narrow
* more memeory = broader compilers however
* tools are already written for narrow compilers
* narrow is better for simple languages, less dynamic memeory allocation
* narrow compiler may partially trasnform program, then use 2nd pass to fully transform (using info from 1st pass)
  - = 2 pass/ 2 scan 

#### Compiler Autority:
* broad compiler uses driver, calls each module in sequence
* narrow compilers usually use parser as main loop/module
  - parser pulls program text in the lexer, out through code gen
  - no co-routines (multiple stacks, so one module must be main loop
  - should be module wiht biggest stack (parser)

#### Properties of a good compiler
1. Generates correct code Always
2. Conforms completely to language spec
3. handles programs of arbitrary size
4. compilation speed
  - keep compilation time linear with input
  - recompile only modified components
5. user friendlyness
  - quality of error reporting
6. size of compiler - not so important now
7. speed and size of compiled code

#### Sources of non-linearity in compilation
* linear techniques are inconvenient
* worry-free parsing can be cubic in size of input
* best code generation is found by considering all code combinations
* niave memory management, can be quadratic
* good linear time heuristics/solutions avilable for all these problems
  
#### Portability
* portability = running a compiler on any machine
* retargetability = generating code for any machine
* compiler written in good style in modern language = portable
* replaceable back end = retargetable
* more effort to replace back end, less retargetable
* can make a backend from machine descriptions

#### Optimizations
* easier to make correct code faster than fast code correct
* ex. activation records - collection of data on stack, about an activated unterminated routine

#### Context Free Grammars
* essential formalism for describing language structures
* mostly describe syntactic structure, but contains semantic info as well
* also regular grammars, and attribute grammars

* grammar = set of production rule + start symbol
* production rule defines a named syntactic construct
  - LHS -> RHS
  - name -> possible form (terminal + non-terminal sysmbols)
* terminal = token

Conventions:
* nonterminals - A, B, C
* terminals - x, y, z
* sequences of grammar symbols - alpha, beta
* lowercase - themselves, as terminals
* empty symbol

Production Process
* Sequential form is central data structure in production process
  - string of grammar symbols
  - in tree form, gives syntacic info -> production tree
* leftmost derivation - leftmost symbol is always derived first
* recursion is essential to production process to produce infinite set of strings

Extended Forms:
* can combine rules 
  - N -> a | b | c
* Backus Normal Form (BNF) good for nesting, recursion, bad for optionality, repeating
