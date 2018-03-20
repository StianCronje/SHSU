
/*
    PROGRAM     --> begin STMT_LIST end
    STMT        --> ID := EXPR | e
    STMT_LIST   --> STMT;STMT_LIST | STMT
    EXPR        --> TERM + EXPR | TERM - EXPR
    TERM        --> FCTR * TERM | FCTR div TERM | TERM mod FCTR | FCTR
    FCTR        --> PRIMARY ^ FACTOR | PRIMARY
    PRIMARY     --> ID | NUM | ( EXPR )


    PUSH		v	-- push v (an integer constant) on the stack
    RVALUE   	l	-- push the contents of variable l
    LVALUE  	l   -- push the address of the variable l (LVALUE alpha)
    POP			    -- throw away the top value on the stack
    STO			    -- the rvalue on top of the stack is place in the lvalue below it and both are popped
    COPY			-- push a copy of the top value on the stack
    ADD       		-- pop the top two values off the stack, add them, and push the result
    SUB     		-- pop the top two values off the stack, subtract them, and push the result
    MPY    			-- pop the top two values off the stack, multiply them, and push the result
    DIV       		-- pop the top two values off the stack, divide them, and push the result
    MOD     		-- pop the top two values off the stack, compute the modulus, and push the result
    POW       	    -- pop the top two values off the stack, compute the exponentiation operation, and push the result
    HALT			-- stop execution

	LVALUE alpha
	PUSH 20
	STO
	...
*/

#include <stdio.h>  // standard i/o prototypes
#include <string.h> // string function prototypes
#include <ctype.h>  // char function prototypes
#include <stdlib.h>

// constants
#define ASSIGNSYM ":="
#define PLUSSYM "+"
#define MINUSSYM "-"
#define MULTSYM "*"
#define DIVSYM "div"
#define MODSYM "mod"
#define FACTSYM "^"
#define OPENPAREN "("
#define CLOSEPAREN ")"
#define CLOSESTMT ";"
#define BLANK ' '
#define NULLSTRING ""

typedef int boolean;

// function prototypes
void open_data_file(int, char *[]);
void parse(void);
void program(void);
void stmt(void);
void stmt_list(void);
void expr(void);
void term(void);
void factor(void);
void primary(void);
void error(char *);
void console(char *);
void scan(void);

//necessary global variables
FILE *infile;
char lookahead[7];
char buffer[256];

int lineNum = 1;

int main(int argc, char *argv[])
{
	open_data_file(argc, argv);
	parse();
	console("End of Compilation...");
	fclose(infile);
}

void open_data_file(int argc, char *argv[])
{
	/* This function opens the data file containing the expression for this
	execution of the compiler. */
	char fileName[50];

	infile = NULL;
	if (argc > 1)
	{
		strcpy(fileName, argv[1]);
	}
	else
	{
		printf("Enter a file name: ");
		scanf("%s", fileName);
	}

	if ((infile = fopen(fileName, "r")) == NULL)
	{
		printf("Error opening input file: \"%s\"\n", fileName);
		exit(-1);
	}

} // end open_data_file

void emit(char *opcode)
{
	printf("%s\n", opcode);
} /* end emit() */

void error(char *errstr)
{
	fprintf(stderr, "ERROR (line %d): %s!\n", lineNum, errstr);
} // end error

void console(char *msg)
{
	fprintf(stderr,"%s\n", msg);
}

int reserved(char *token)
{
	// returns 0 if reserved
	// returns > 0 if need to push back
	// returns < 0 if not reserved
	char *contains;

	// check to see if token is reserved
	if (((contains = strstr(token, ASSIGNSYM)) != NULL) ||
		((contains = strstr(token, PLUSSYM)) != NULL) ||
		((contains = strstr(token, MINUSSYM)) != NULL) ||
		((contains = strstr(token, MULTSYM)) != NULL) ||
		((contains = strstr(token, DIVSYM)) != NULL) ||
		((contains = strstr(token, MODSYM)) != NULL) ||
		((contains = strstr(token, FACTSYM)) != NULL) ||
		((contains = strstr(token, OPENPAREN)) != NULL) ||
		((contains = strstr(token, CLOSEPAREN)) != NULL) ||
		((contains = strstr(token, CLOSESTMT)) != NULL))
	{
		// token is reserved word
		int rlen = 0;
		int tlen = 0;
		int diff = 0;

		while(contains[rlen] != '\0')
		{
			rlen++;
		}
		while(token[tlen] != '\0')
		{
			tlen++;
		}

		diff = tlen - rlen;
		if(diff > 0) diff = rlen;
		
		return diff;
	}
	else
	{
		// token is not reserved
		return -1;
	}
}

void scan(void)
{
	int ch;
	int i = 0;
	int backtrack = 0;

	// make sure lookahead is null when starting a new scan
	strcpy(lookahead, NULLSTRING);

	while ((ch = getc(infile)) != EOF) // while not end of file, read a char and save it in ch
	{
		if (isspace(ch)) // if it is any whitespace
		{
			if(ch == '\n') lineNum++;
			if (i > 0) // if lookahead has something in it abd then space. (found token)
				break;

			i = 0;
			continue; // if blank skip over
		}

		// add current character to lookahead
		lookahead[i++] = ch;
		// add null terminator to check reserved objects
		lookahead[i] = '\0';

		if ((backtrack = reserved(lookahead)) >= 0) // contains a reserved word?
		{
			// if it was picked up with an id or num,
			// push back until just one token is returned,
			// else this is only a reserved word

			// (this protects against reserved objects being read as ids or nums)

			for(int c = 1; c <= backtrack; c++){
				ungetc(lookahead[i - c], infile);
			}
			lookahead[i - backtrack] = '\0';
			break;
		}
	}
	// found lookahead
}

void match(char *token)
{
	if (strcmp(token, lookahead) == 0) // expected token matches next token in file
	{
		scan(); // move on to next token
	}
	else // else report "[token] expected, but [lookahead] received"
	{
		strcpy(buffer, "\"");
		strcat(buffer, token);
		strcat(buffer, "\" expected, but recieved: \"");
		strcat(buffer, lookahead);
		strcat(buffer, "\"");
		error(buffer);
	}
} /* end match() */

boolean identifier(char *token)
{
	/* checks for a valid identifier -- a sequence of nondelimiters starting
    with a letter  */
	return (((token[0] >= 'A') && (token[0] <= 'Z')) ||
			((token[0] >= 'a') && (token[0] <= 'z')));
} /* end identifier() */

void fctr()
{
	//FCTR        --> PRIMARY ^ FACTOR | PRIMARY

	char temp[20] = NULLSTRING;

	primary();

	while (strcmp(lookahead, FACTSYM) == 0)
	{
		strcpy(temp, lookahead);
		match(lookahead);
		fctr();
		emit("POW");
	} // end while

} /* end fctr() */

void term()
/*This procedure handles the assembly of terms */
{
	//TERM        --> FCTR * TERM | FCTR div TERM | TERM mod FCTR | FCTR

	char temp[20] = NULLSTRING;

	fctr(); /* A term must begin with a factor */
	/* Now, process any multiplying operator */
	while ((strcmp(lookahead, MULTSYM) == 0) || (strcmp(lookahead, DIVSYM) == 0) || (strcmp(lookahead, MODSYM) == 0))
	{
		strcpy(temp, lookahead);
		match(lookahead);
		fctr();
		if (strcmp(temp, MULTSYM) == 0)
			emit("MPY");
		else if (strcmp(temp, DIVSYM) == 0)
			emit("DIV");
		else
			emit("MOD");
	} // end while

} //  end term()

void expr()
{
	//EXPR        --> TERM + EXPR | TERM - EXPR | TERM
	/* This procedure handles the assembly of expressions */

	char temp[20] = NULLSTRING;

	term(); /* An expression must begin with a term */
	/* Now, process any adding operators */
	while ((strcmp(lookahead, PLUSSYM) == 0) || (strcmp(lookahead, MINUSSYM) == 0))
	{
		strcpy(temp, lookahead);
		match(lookahead);
		term();
		if (strcmp(temp, PLUSSYM) == 0)
			emit("ADD");
		else
			emit("SUB");
	} // end while
} // end expr()

void program(void)
{
	//printf("start program\n");
	//PROGRAM     --> begin STMT_LIST end
	match("begin");
	stmt_list();
	match("end");
	emit("HALT");
}

void stmt_list(void)
{
	//STMT_LIST   --> STMT;STMT_LIST | STMT
	stmt();
	if (strcmp(lookahead, CLOSESTMT) == 0)
	{
		match(CLOSESTMT);
		stmt_list();
	}
}

void stmt(void)
{
	//STMT        --> ID := EXPR | e
	
	if (identifier(lookahead) != 0)
	{
		//printf("try: %s = ...\n", lookahead);
		strcpy(buffer, "LVALUE ");
		strcat(buffer, lookahead);
		emit(buffer);
		match(lookahead);
		
		match(ASSIGNSYM);
		expr();
		emit("STO");
	}
}

void primary(void)
{
	//PRIMARY     --> ID | NUM | ( EXPR )

	if (strcmp(lookahead, OPENPAREN) == 0) // this is (expr)
	{
		match(OPENPAREN);
		expr();
		match(CLOSEPAREN);
	}
	else if (identifier(lookahead) != 0) // this is id
	{
		strcpy(buffer, "RVALUE ");
		strcat(buffer, lookahead);
		emit(buffer);

		match(lookahead);
	}
	else // this is a num
	{
		strcpy(buffer, "PUSH ");
		strcat(buffer, lookahead);
		emit(buffer);

		match(lookahead);
	}
}

void parse(void)
{
	//printf("start parse\n");
	scan();
	program();
} // end parse()
