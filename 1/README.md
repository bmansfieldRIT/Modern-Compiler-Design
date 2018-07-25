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

* introduce bars ( | ) and three notations
  - R+ -> One or more R
  - R? -> optional R
  - R* -> optional repitition
  
Properties of Grammars:
* terminal N is left recursive if N->N (optional symbols)
* nonempty terminal N is nullable if we can produce empty sequential form
* N is useless if it can never produce a terminal string of symbols 
  ex. exp -> '+' exp | '-' exp
* grammar chacking software should scan and reject useless non terminals
* grammar is ambiguous if it produces two different production trees with some leaves, in same order
* we lose semantics, so unambiguity is essential

Grammar Formalism:
* symbol - basic unit
* production rule - V1 -> V2
* CFG - 4 tuple, G = (Vn, Vt, S, P)

#### Closure Algorithms:
* many compiler algorithms collect info, draw conclusions/extend info
* algorithms treated as a class of algorithms

ex. Calling Graph:
* can find out which procedures are recursive, and which can be expanded inline
* ignore procedures-as-arguments, anonymous routines, etc.

* closure algorithm has three elements:
  - Data Definitions - definitions and semantics derived from nature of problem
  - Inititalizations - 1+ rules for initializing info items, convert problem to info items
  - Inference Rules - 1+ rules for inferring more info items from given: ex. if Info items I1, I2, ... are present, then II J must be present
* when all inferences are drawn, we get closure of info set

Ex for calling graph:
Data Definitions:
1. Let G be graph of routine nodes. Info items are arrows 
2. A->B = A calls B directly/indirectly
Initializations:
1. If A calls B, arrow from A to B must be present
Inference Rules:
1. If A->B, and B->C, then A->C must be present

* add a rule: no adding of arbitrary info items
  - gets us a least fixed point of closure algorithms
* above is not really algorithm, more like specification
* above gets into infinite loop, as no stop conditions are specified

* General Closure Algorithm: if I1, I2 are present, then J must be present
* Transitive Closure Algorithm: If (A,B) and (B,C) then (A,C)

* if we expand possible inference rules to removal, replacement
  - Not really proper closure algorithm
  - More like a recursive function of initial set
  - May not have a fixed point
  
