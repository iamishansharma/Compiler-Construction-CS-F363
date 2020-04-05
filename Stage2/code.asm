
Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
program $ 

Top of stack: program | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 1 | X = program | a-NTER = 0 

Pushing these on stack now: 
otherModules 
driverModule 
otherModules 
moduleDeclarations 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: moduleDeclarations | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 2 | X = moduleDeclarations | a-NTER = 0 

Pushing these on stack now: 
moduleDeclarations 
moduleDeclaration 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
moduleDeclaration moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: moduleDeclaration | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 4 | X = moduleDeclaration | a-NTER = 0 

Pushing these on stack now: 
SEMICOL 
ID 
MODULE 
DECLARE 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DECLARE MODULE ID SEMICOL moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: DECLARE | Input Token: DECLARE | Input Token Lexeme: declare
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
MODULE ID SEMICOL moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: MODULE | Input Token: MODULE | Input Token Lexeme: module
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID SEMICOL moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: mod1
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
moduleDeclarations otherModules driverModule otherModules $ 

Top of stack: moduleDeclarations | Input Token: DRIVERDEF | Input Token Lexeme: <<<
Entry exists in Parse Table
Rule no to use in grammar.txt: 3 | X = moduleDeclarations | a-NTER = 2 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
otherModules driverModule otherModules $ 

Top of stack: otherModules | Input Token: DRIVERDEF | Input Token Lexeme: <<<
Entry exists in Parse Table
Rule no to use in grammar.txt: 6 | X = otherModules | a-NTER = 2 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
driverModule otherModules $ 

Top of stack: driverModule | Input Token: DRIVERDEF | Input Token Lexeme: <<<
Entry exists in Parse Table
Rule no to use in grammar.txt: 7 | X = driverModule | a-NTER = 2 

Pushing these on stack now: 
moduleDef 
DRIVERENDDEF 
PROGRAM 
DRIVER 
DRIVERDEF 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef otherModules $ 

Top of stack: DRIVERDEF | Input Token: DRIVERDEF | Input Token Lexeme: <<<
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DRIVER PROGRAM DRIVERENDDEF moduleDef otherModules $ 

Top of stack: DRIVER | Input Token: DRIVER | Input Token Lexeme: driver
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
PROGRAM DRIVERENDDEF moduleDef otherModules $ 

Top of stack: PROGRAM | Input Token: PROGRAM | Input Token Lexeme: program
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DRIVERENDDEF moduleDef otherModules $ 

Top of stack: DRIVERENDDEF | Input Token: DRIVERENDDEF | Input Token Lexeme: >>>
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
moduleDef otherModules $ 

Top of stack: moduleDef | Input Token: START | Input Token Lexeme: start
Entry exists in Parse Table
Rule no to use in grammar.txt: 25 | X = moduleDef | a-NTER = 11 

Pushing these on stack now: 
END 
statements 
START 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
START statements END otherModules $ 

Top of stack: START | Input Token: START | Input Token Lexeme: start
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statements END otherModules $ 

Top of stack: statements | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 26 | X = statements | a-NTER = 0 

Pushing these on stack now: 
statements 
statement 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statement statements END otherModules $ 

Top of stack: statement | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 30 | X = statement | a-NTER = 0 

Pushing these on stack now: 
declareStmt 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
declareStmt statements END otherModules $ 

Top of stack: declareStmt | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 93 | X = declareStmt | a-NTER = 0 

Pushing these on stack now: 
SEMICOL 
dataType 
COLON 
idList 
DECLARE 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DECLARE idList COLON dataType SEMICOL statements END otherModules $ 

Top of stack: DECLARE | Input Token: DECLARE | Input Token Lexeme: declare
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList | Input Token: ID | Input Token Lexeme: r
Entry exists in Parse Table
Rule no to use in grammar.txt: 54 | X = idList | a-NTER = 5 

Pushing these on stack now: 
idList_again 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: r
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: COLON | Input Token Lexeme: :
Entry exists in Parse Table
Rule no to use in grammar.txt: 56 | X = idList_again | a-NTER = 48 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON dataType SEMICOL statements END otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
dataType SEMICOL statements END otherModules $ 

Top of stack: dataType | Input Token: INTEGER | Input Token Lexeme: integer
Entry exists in Parse Table
Rule no to use in grammar.txt: 17 | X = dataType | a-NTER = 7 

Pushing these on stack now: 
INTEGER 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
INTEGER SEMICOL statements END otherModules $ 

Top of stack: INTEGER | Input Token: INTEGER | Input Token Lexeme: integer
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL statements END otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statements END otherModules $ 

Top of stack: statements | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 26 | X = statements | a-NTER = 0 

Pushing these on stack now: 
statements 
statement 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statement statements END otherModules $ 

Top of stack: statement | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 30 | X = statement | a-NTER = 0 

Pushing these on stack now: 
declareStmt 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
declareStmt statements END otherModules $ 

Top of stack: declareStmt | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 93 | X = declareStmt | a-NTER = 0 

Pushing these on stack now: 
SEMICOL 
dataType 
COLON 
idList 
DECLARE 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DECLARE idList COLON dataType SEMICOL statements END otherModules $ 

Top of stack: DECLARE | Input Token: DECLARE | Input Token Lexeme: declare
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList | Input Token: ID | Input Token Lexeme: m
Entry exists in Parse Table
Rule no to use in grammar.txt: 54 | X = idList | a-NTER = 5 

Pushing these on stack now: 
idList_again 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: m
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: COLON | Input Token Lexeme: :
Entry exists in Parse Table
Rule no to use in grammar.txt: 56 | X = idList_again | a-NTER = 48 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON dataType SEMICOL statements END otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
dataType SEMICOL statements END otherModules $ 

Top of stack: dataType | Input Token: REAL | Input Token Lexeme: real
Entry exists in Parse Table
Rule no to use in grammar.txt: 18 | X = dataType | a-NTER = 8 

Pushing these on stack now: 
REAL 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
REAL SEMICOL statements END otherModules $ 

Top of stack: REAL | Input Token: REAL | Input Token Lexeme: real
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL statements END otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statements END otherModules $ 

Top of stack: statements | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 26 | X = statements | a-NTER = 0 

Pushing these on stack now: 
statements 
statement 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statement statements END otherModules $ 

Top of stack: statement | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 30 | X = statement | a-NTER = 0 

Pushing these on stack now: 
declareStmt 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
declareStmt statements END otherModules $ 

Top of stack: declareStmt | Input Token: DECLARE | Input Token Lexeme: declare
Entry exists in Parse Table
Rule no to use in grammar.txt: 93 | X = declareStmt | a-NTER = 0 

Pushing these on stack now: 
SEMICOL 
dataType 
COLON 
idList 
DECLARE 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DECLARE idList COLON dataType SEMICOL statements END otherModules $ 

Top of stack: DECLARE | Input Token: DECLARE | Input Token Lexeme: declare
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList | Input Token: ID | Input Token Lexeme: v
Entry exists in Parse Table
Rule no to use in grammar.txt: 54 | X = idList | a-NTER = 5 

Pushing these on stack now: 
idList_again 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: v
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: COMMA | Input Token Lexeme: ,
Entry exists in Parse Table
Rule no to use in grammar.txt: 55 | X = idList_again | a-NTER = 6 

Pushing these on stack now: 
idList_again 
ID 
COMMA 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COMMA ID idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: COMMA | Input Token: COMMA | Input Token Lexeme: ,
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: w
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again COLON dataType SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: COLON | Input Token Lexeme: :
Entry exists in Parse Table
Rule no to use in grammar.txt: 56 | X = idList_again | a-NTER = 48 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON dataType SEMICOL statements END otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
dataType SEMICOL statements END otherModules $ 

Top of stack: dataType | Input Token: INTEGER | Input Token Lexeme: integer
Entry exists in Parse Table
Rule no to use in grammar.txt: 17 | X = dataType | a-NTER = 7 

Pushing these on stack now: 
INTEGER 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
INTEGER SEMICOL statements END otherModules $ 

Top of stack: INTEGER | Input Token: INTEGER | Input Token Lexeme: integer
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL statements END otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statements END otherModules $ 

Top of stack: statements | Input Token: SQBO | Input Token Lexeme: [
Entry exists in Parse Table
Rule no to use in grammar.txt: 26 | X = statements | a-NTER = 17 

Pushing these on stack now: 
statements 
statement 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statement statements END otherModules $ 

Top of stack: statement | Input Token: SQBO | Input Token Lexeme: [
Entry exists in Parse Table
Rule no to use in grammar.txt: 29 | X = statement | a-NTER = 17 

Pushing these on stack now: 
simpleStmt 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
simpleStmt statements END otherModules $ 

Top of stack: simpleStmt | Input Token: SQBO | Input Token Lexeme: [
Entry exists in Parse Table
Rule no to use in grammar.txt: 43 | X = simpleStmt | a-NTER = 17 

Pushing these on stack now: 
moduleReuseStmt 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
moduleReuseStmt statements END otherModules $ 

Top of stack: moduleReuseStmt | Input Token: SQBO | Input Token Lexeme: [
Entry exists in Parse Table
Rule no to use in grammar.txt: 51 | X = moduleReuseStmt | a-NTER = 17 

Pushing these on stack now: 
SEMICOL 
idList 
PARAMETERS 
WITH 
ID 
MODULE 
USE 
optional 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
optional USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: optional | Input Token: SQBO | Input Token Lexeme: [
Entry exists in Parse Table
Rule no to use in grammar.txt: 52 | X = optional | a-NTER = 17 

Pushing these on stack now: 
ASSIGNOP 
SQBC 
idList 
SQBO 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SQBO idList SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: SQBO | Input Token: SQBO | Input Token Lexeme: [
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: idList | Input Token: ID | Input Token Lexeme: r
Entry exists in Parse Table
Rule no to use in grammar.txt: 54 | X = idList | a-NTER = 5 

Pushing these on stack now: 
idList_again 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: r
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: COMMA | Input Token Lexeme: ,
Entry exists in Parse Table
Rule no to use in grammar.txt: 55 | X = idList_again | a-NTER = 6 

Pushing these on stack now: 
idList_again 
ID 
COMMA 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COMMA ID idList_again SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: COMMA | Input Token: COMMA | Input Token Lexeme: ,
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: m
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: SQBC | Input Token Lexeme: ]
Entry exists in Parse Table
Rule no to use in grammar.txt: 56 | X = idList_again | a-NTER = 47 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SQBC ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: SQBC | Input Token: SQBC | Input Token Lexeme: ]
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ASSIGNOP USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: ASSIGNOP | Input Token: ASSIGNOP | Input Token Lexeme: :=
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
USE MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: USE | Input Token: USE | Input Token Lexeme: use
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
MODULE ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: MODULE | Input Token: MODULE | Input Token Lexeme: module
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: mod1
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
WITH PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: WITH | Input Token: WITH | Input Token Lexeme: with
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
PARAMETERS idList SEMICOL statements END otherModules $ 

Top of stack: PARAMETERS | Input Token: PARAMETERS | Input Token Lexeme: parameters
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList SEMICOL statements END otherModules $ 

Top of stack: idList | Input Token: ID | Input Token Lexeme: v
Entry exists in Parse Table
Rule no to use in grammar.txt: 54 | X = idList | a-NTER = 5 

Pushing these on stack now: 
idList_again 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: v
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: COMMA | Input Token Lexeme: ,
Entry exists in Parse Table
Rule no to use in grammar.txt: 55 | X = idList_again | a-NTER = 6 

Pushing these on stack now: 
idList_again 
ID 
COMMA 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COMMA ID idList_again SEMICOL statements END otherModules $ 

Top of stack: COMMA | Input Token: COMMA | Input Token Lexeme: ,
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID idList_again SEMICOL statements END otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: w
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
idList_again SEMICOL statements END otherModules $ 

Top of stack: idList_again | Input Token: SEMICOL | Input Token Lexeme: ;
Entry exists in Parse Table
Rule no to use in grammar.txt: 56 | X = idList_again | a-NTER = 40 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL statements END otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statements END otherModules $ 

Top of stack: statements | Input Token: END | Input Token Lexeme: end
Entry exists in Parse Table
Rule no to use in grammar.txt: 27 | X = statements | a-NTER = 50 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
END otherModules $ 

Top of stack: END | Input Token: END | Input Token Lexeme: end
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
otherModules $ 

Top of stack: otherModules | Input Token: DEF | Input Token Lexeme: <<
Entry exists in Parse Table
Rule no to use in grammar.txt: 5 | X = otherModules | a-NTER = 1 

Pushing these on stack now: 
otherModules 
module 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
module otherModules $ 

Top of stack: module | Input Token: DEF | Input Token Lexeme: <<
Entry exists in Parse Table
Rule no to use in grammar.txt: 8 | X = module | a-NTER = 1 

Pushing these on stack now: 
moduleDef 
ret 
SEMICOL 
SQBC 
input_plist 
SQBO 
INPUT 
TAKES 
ENDDEF 
ID 
MODULE 
DEF 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: DEF | Input Token: DEF | Input Token Lexeme: <<
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: MODULE | Input Token: MODULE | Input Token Lexeme: module
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: mod1
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: ENDDEF | Input Token: ENDDEF | Input Token Lexeme: >>
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: TAKES | Input Token: TAKES | Input Token Lexeme: takes
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
INPUT SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: INPUT | Input Token: INPUT | Input Token Lexeme: input
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SQBO input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: SQBO | Input Token: SQBO | Input Token Lexeme: [
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
input_plist SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: input_plist | Input Token: ID | Input Token Lexeme: a
Entry exists in Parse Table
Rule no to use in grammar.txt: 11 | X = input_plist | a-NTER = 5 

Pushing these on stack now: 
input_plist_again 
dataType 
COLON 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID COLON dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: a
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: dataType | Input Token: INTEGER | Input Token Lexeme: integer
Entry exists in Parse Table
Rule no to use in grammar.txt: 17 | X = dataType | a-NTER = 7 

Pushing these on stack now: 
INTEGER 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
INTEGER input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: INTEGER | Input Token: INTEGER | Input Token Lexeme: integer
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: input_plist_again | Input Token: COMMA | Input Token Lexeme: ,
Entry exists in Parse Table
Rule no to use in grammar.txt: 12 | X = input_plist_again | a-NTER = 6 

Pushing these on stack now: 
input_plist_again 
dataType 
COLON 
ID 
COMMA 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COMMA ID COLON dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: COMMA | Input Token: COMMA | Input Token Lexeme: ,
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID COLON dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: b
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
dataType input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: dataType | Input Token: INTEGER | Input Token Lexeme: integer
Entry exists in Parse Table
Rule no to use in grammar.txt: 17 | X = dataType | a-NTER = 7 

Pushing these on stack now: 
INTEGER 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
INTEGER input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: INTEGER | Input Token: INTEGER | Input Token Lexeme: integer
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
input_plist_again SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: input_plist_again | Input Token: SQBC | Input Token Lexeme: ]
Entry exists in Parse Table
Rule no to use in grammar.txt: 13 | X = input_plist_again | a-NTER = 47 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SQBC SEMICOL ret moduleDef otherModules $ 

Top of stack: SQBC | Input Token: SQBC | Input Token Lexeme: ]
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL ret moduleDef otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ret moduleDef otherModules $ 

Top of stack: ret | Input Token: RETURNS | Input Token Lexeme: returns
Entry exists in Parse Table
Rule no to use in grammar.txt: 9 | X = ret | a-NTER = 4 

Pushing these on stack now: 
SEMICOL 
SQBC 
output_plist 
SQBO 
RETURNS 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
RETURNS SQBO output_plist SQBC SEMICOL moduleDef otherModules $ 

Top of stack: RETURNS | Input Token: RETURNS | Input Token Lexeme: returns
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SQBO output_plist SQBC SEMICOL moduleDef otherModules $ 

Top of stack: SQBO | Input Token: SQBO | Input Token Lexeme: [
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
output_plist SQBC SEMICOL moduleDef otherModules $ 

Top of stack: output_plist | Input Token: ID | Input Token Lexeme: x
Entry exists in Parse Table
Rule no to use in grammar.txt: 14 | X = output_plist | a-NTER = 5 

Pushing these on stack now: 
output_plist_again 
type 
COLON 
ID 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID COLON type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: x
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: type | Input Token: INTEGER | Input Token Lexeme: integer
Entry exists in Parse Table
Rule no to use in grammar.txt: 22 | X = type | a-NTER = 7 

Pushing these on stack now: 
INTEGER 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
INTEGER output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: INTEGER | Input Token: INTEGER | Input Token Lexeme: integer
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: output_plist_again | Input Token: COMMA | Input Token Lexeme: ,
Entry exists in Parse Table
Rule no to use in grammar.txt: 15 | X = output_plist_again | a-NTER = 6 

Pushing these on stack now: 
output_plist_again 
type 
COLON 
ID 
COMMA 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COMMA ID COLON type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: COMMA | Input Token: COMMA | Input Token Lexeme: ,
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
ID COLON type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: ID | Input Token: ID | Input Token Lexeme: abc
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
COLON type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: COLON | Input Token: COLON | Input Token Lexeme: :
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
type output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: type | Input Token: REAL | Input Token Lexeme: real
Entry exists in Parse Table
Rule no to use in grammar.txt: 23 | X = type | a-NTER = 8 

Pushing these on stack now: 
REAL 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
REAL output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: REAL | Input Token: REAL | Input Token Lexeme: real
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
output_plist_again SQBC SEMICOL moduleDef otherModules $ 

Top of stack: output_plist_again | Input Token: SQBC | Input Token Lexeme: ]
Entry exists in Parse Table
Rule no to use in grammar.txt: 16 | X = output_plist_again | a-NTER = 47 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SQBC SEMICOL moduleDef otherModules $ 

Top of stack: SQBC | Input Token: SQBC | Input Token Lexeme: ]
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
SEMICOL moduleDef otherModules $ 

Top of stack: SEMICOL | Input Token: SEMICOL | Input Token Lexeme: ;
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
moduleDef otherModules $ 

Top of stack: moduleDef | Input Token: START | Input Token Lexeme: start
Entry exists in Parse Table
Rule no to use in grammar.txt: 25 | X = moduleDef | a-NTER = 11 

Pushing these on stack now: 
END 
statements 
START 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
START statements END otherModules $ 

Top of stack: START | Input Token: START | Input Token Lexeme: start
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
statements END otherModules $ 

Top of stack: statements | Input Token: END | Input Token Lexeme: end
Entry exists in Parse Table
Rule no to use in grammar.txt: 27 | X = statements | a-NTER = 50 

Pushing these on stack now: 


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
END otherModules $ 

Top of stack: END | Input Token: END | Input Token Lexeme: end
ACTION: Popping top of stack because same terminal found at input


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
otherModules $ 


otherModules not used hence popping it!


Stack (TOP OF STACK IS LEFT MOST ELEMENT: 
$ 

	Parsing successfully for input file....!