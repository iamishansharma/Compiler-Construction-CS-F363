/*  

	SymbolTableDef.h 
	
	Batch No: 14

	Members: 

	Ishan Sharma 2016B2A70773P
	Sarthak Sahu 2015B5A70749P
	Anirudh Garg 2017A7PS0142P
	Sanjeev Singla 2017A7PS0152P

*/

/* START COLOR DEFINE */

#ifndef RESET
#define RESET   "\033[0m"
#endif

#ifndef BOLDBLACK
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#endif

#ifndef BOLDRED
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#endif

#ifndef BOLDGREEN
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#endif

#ifndef BOLDYELLOW
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#endif

#ifndef BOLDBLUE
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#endif

#ifndef BOLDMAGENTA
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#endif

#ifndef BOLDCYAN
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#endif

#ifndef BOLDWHITE
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#endif

/* END COLOR DEFINE */

#ifndef ST_DEFH
#define ST_DEFH

struct index
{
	int isused;
	char id[30];
	int ifnumvalue;
	int isDynamic;
};

typedef struct index Index;

struct symbolnode
{
	char name[30];

	int usage;

	// 1: Variable
	// 2. Function Def
	// 3. Input Parameters
	// 4. Output Parameters
	// 5. Function Declaration
	// 6. Function Def and Dec

	char type[30];
	int isArray;
	Index *startindex;
	Index *endindex;
	int offset;
	int width;
	int lineno;
	struct symbolnode *next;
	struct symboltable *scope; // Gets which scope this node is in
	int isAss;
	int mrsreq; // used to have the value of latest line no if func decl is required. 
	int declno; // used to store declaration line no of function 
	int deflno; // used to store the defination line no of function
	int udv; // flag for UDV
	char temporary[5]; // Temporary Variable used for SymbolEntry in CodeGen
};

typedef struct symbolnode SymbolEntry;

struct symboltable
{
	char name[30];

	struct symboltable *parent;
	struct symboltable *child;
	struct symboltable *left;
	struct symboltable *right;
	struct symbolnode *nodehead;
	int startlno;
	int endlno;

	//int offsetper;
};

typedef struct symboltable SymbolTable;

#endif