# *ER*adicate *PLAG*iarism

The language ERPLAG is a strongly typed language designed for the course Compiler Construction CS F363 and the name of the language is motivated by the drive to ERadicate PLAGiarism.
<br />The language has been evolving to provide a minimal feature set for the project in Compiler Construction course.

## Lexical Structure

### Identifiers

- Regular expression for an identifier is [a-z|A-Z][az|A-Z|0-9|_]*. 
- Identifiers can be at most 20 characters long. 
- The language is case sensitive.
- Identifiers are separated from keywords through a white space.

### White Spaces, Separator and Comments

- The white spaces are blanks, tabs and new line characters. 
- These are used to separate the tokens. 
- Any number of white spaces is ignored and need not be tokenized.
- A semicolon ```;``` separates the statements from each other. 
- A comment starts with ** and ends with **.

### Numbers

#### Integer

- An integer number is a sequence of digits.
- The numbers 234, 1,45, 90123 etc. represent integers and are tokenised as NUM. 
- The type of the integer numbers is integer.

#### Real (Float)

- A floating point number can be either a sequence of digits followed by a decimal point, followed by the fraction part of it again as a continuous sequence of digits.
- For example, numbers 23.89, 908.567 and 25.0 are valid floating point numbers, but 26. is not because there is no digit after the decimal point. 
- These numbers can also be represented in mantissa and exponent form, for example, 123.2E+6, 124.2E-1, 124.2e-1 etc. E can be both in upper case and lower case.
- Signs are optional and if no sign is used with E, the exponent value should be assumed as positive. 
- The floating point number will not start with a decimal point, for example, .124E+2 is not valid while 1.24E+1 is a valid lexeme. 
- A floating point number is of data type real and is tokenised as RNUM

### Operators

- The arithmetic operations are recognized by the lexemes +, -, *, / in their usual meaning.
- The relational operators are simply <, <=, >, >=, == and !=, known in their usual meaning.
- The logical and and or operations are permissible and the lexemes ```AND``` and ```OR``` (only in uppercase letters) are valid to be recognized as these two operations.
- A special operator .. (dot dot) represents the range in defining the array range and for loop ranges.
- Eg. ```declare C:array[1..10] of integer;``` OR ```for(k in 2..8)```
- The assignment operator is := and is tokenised as ASSIGNOP.

### Keywords Table

| Pattern | Token |
| :-------------: |:-------------:|
| integer | INTEGER |
| real | REAL |
| boolean | BOOLEAN |
| of | OF |
| array | ARRAY |
| start | START |
| end | END |
| declare | DECLARE |
| module | MODULE |
| driver | DRIVER |
| program | PROGRAM |
| get_value | GET_VALUE |
| print | PRINT |
| use | USE |
| with | WITH |
| parameters | PARAMETERS |
| true | TRUE |
| false | FALSE |
| takes | TAKES |
| input | INPUT |
| returns | RETURNS |
| AND | AND |
| OR | OR |
| for | FOR |
| in | IN |
| switch | SWITCH |
| case | CASE |
| break | BREAK |
| default | DEFAULT |
| while | WHILE |

### Symbols/Operators Table

| Pattern | Token |
| :-------------: | :-------------: |
 |+ | PLUS |
 |- | MINUS |
 |* | MUL |
 |/ | DIV |
 |< | LT |
 |<= | LE |
 |>= | GE |
 |> | GT |
 |== | EQ |
 |!= | NE |
 |<< | DEF |
 |>> | ENDDEF |
 |<<< | DRIVERDEF |
 |>>> | DRIVERENDDEF |
 |: | COLON |
 |.. | RANGEOP |
 |; | SEMICOL |
 |, | COMMA |
 |:= | ASSIGNOP |
 |[ | SQBO |
 |] | SQBC |
 |( | BO |
 |) | BC |
 |** | COMMENTMARK |

## Datatypes

### Primitive

- `Interger`
- `Real (Float)`
- `Boolean`
- `Single Dimensional Array` of any primitive datatypes (Static and Dynamic bound allocation)

## Types of Statements Supported

### > Declarative

Syntax: `declare {identifier_list} : primitive_data_type;`

Eg. `declare a, b, c:integer;` declares the identifiers a, b and c to be of type integer.

#### Properties

- A declaration statement can appear anywhere in the program and is valid for any use thereafter with in its scope. 
- An identifier cannot be declared multiple times in the same scope. 
- Also, an identifier must be declared before its use.

------
### > Assignment


Syntax: `<left_hand_value> := <right_hand_expression>;`

Eg. `A[i] := 3;` OR `b := c * d + 4.5;`

- A left value can be a simple identifier or a constructed expression for accessing an array element.
- The right hand side can be any arithematic or boolen expression.

------
### > Input/Output


#### * get_value({identifier})

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The input statement `get_value(v);` intends to read value from the keyboard and associate with the variable v. 

#### * print({identifier})

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The statement `print(v);` intends to write the value of variable v on the monitor.

------
### > Conditional


Syntax: 

`switch({identifier})`<br />
`start`<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`case {value} : <statements S1>;`<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`break;`<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`case {value} : <statements S2>;`<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`break;`<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`default : <statements S3>;`<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`break;`<br />
`end`

#### Properties

- The only conditional statement supported by this language is the C-like switch-case statement. 
- There is no statement of C-like if.
- The switch statement with a boolean identifier must have cases with values TRUE and FALSE. 
- There is no default value associated with a switch statement with a boolean identifier. 
- A switch statement with an integer value can have any number of case statements and a default statement must follow these case statements. 
- The case statements are separated by a break.

------
### > Iterative

#### * for

Syntax: 

```for({identifier} in {low_range}..{high_range})```<br />
```start```<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```<statements>```<br />
```end```<br />
<br />
Eg.<br />
<br />
```for(k in 2..8)```<br />
```start```<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```x := x + 2*k;```<br />
```end```<br />

#### Properties



#### * while

Syntax:<br />
<br />
```while({boolean expression})```<br />
```start```<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```<statements>```<br />
```end```<br />
<br />
Eg.<br />
<br />
```while(i<=k)```<br />
```start```<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```i := i+1;```<br />
```end```<br />

#### Properties



------
### > Function Call

Syntax:<br />
<br />
Non Returning: ```use {function_name} with parameters {parameter_list};```<br />
Returning: ```[return_list] := use {function_name} with parameters {parameter_list};```<br />
<br />
Eg.<br />
<br />
```[r,m] := use mod1 with parameters v, w;```<br />
```use mod2 with parameters a, b;```<br />
