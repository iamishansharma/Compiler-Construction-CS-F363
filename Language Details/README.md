# *ER*adicate *PLAG*iarism

The language ERPLAG is a strongly typed language designed for the course Compiler Construction CS F363 and the name of the language is motivated by the drive to ERadicate PLAGiarism.
<br />The language has been evolving to provide a minimal feature set for the project in Compiler Construction course.

## Datatypes

### Primitive

- `Interger`
- `Float`
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

### > Assignment

Syntax: `<left_hand_value> := <right_hand_expression>;`

Eg. `A[i] := 3;` OR `b := c * d + 4.5;`

- A left value can be a simple identifier or a constructed expression for accessing an array element.
- The right hand side can be any arithematic or boolen expression.

### > Input/Output

#### get_value({identifier})

The input statement `get_value(v);` intends to read value from the keyboard and associate with the variable v. 

#### print({identifier})

The statement `print(v);` intends to write the value of variable v on the monitor.

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

### > Iterative



### > Function Call


