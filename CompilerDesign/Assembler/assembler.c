#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int i = 1;
#define is_bigendian() ((*(char *)&i) == 0)

typedef enum {
	HALT,
	PUSH,
	RVALUE,
	LVALUE,
	POP,
	STO,
	COPY,
	ADD,
	SUB,
	MPY,
	DIV,
	MOD,
	NEG,
	NOT,
	OR,
	AND,
	EQ,
	NE,
	GT,
	GE,
	LT,
	LE,
	LABEL,
	GOTO,
	GOFALSE,
	GOTRUE,
	PRINT,
	READ,
	GOSUB,
	RET
} OpCodes;

typedef struct
{
	char lexeme[12];
	char type[12];
	int address;
} Symbol;

Symbol symbolTable[100];
int symCount = 0;
char *instructions[] = {"HALT", "PUSH", "RVALUE", "LVALUE", "POP", "STO", "COPY",
						"ADD", "SUB", "MPY", "DIV", "MOD", "NEG", "NOT", "OR",
						"AND", "EQ", "NE", "GT", "GE", "LT", "LE", "LABEL", "GOTO",
						"GOFALSE", "GOTRUE", "PRINT", "READ", "GOSUB", "RET"};

void open_in_file(int argc, char *argv[]);
void open_out_file(int argc, char *argv[]);
void build_symbol_table();
void generate_code();
void insert_into_sym_tab(char *_lex, char *_typ, int _addr);
void print_symbol_table(void);
int lookup_opcode(char *lexeme);
int lookup_symbol_address(char *lexeme);
void insert_code(int loc, int opcode, int operand);
int reverseInt(int i);

FILE *infile;
FILE *outfile;
char buffer[256] = "";
const char *delim = " \t\r\n";

int main(int argc, char *argv[])
{
	open_in_file(argc, argv);
	open_out_file(argc, argv);

	build_symbol_table();
	print_symbol_table();

	fseek(infile, 0, SEEK_SET);

	generate_code();

	fclose(infile);
	fclose(outfile);

	fprintf(stderr, "Assembly complete...\n");
}

void open_in_file(int argc, char *argv[])
{
	char fileName[50];

	infile = NULL;
	if (argc > 1)
	{
		strcpy(fileName, argv[1]);
	}
	else
	{
		fprintf(stderr, "Enter an input file name: ");
		scanf("%s", fileName);
	}

	if ((infile = fopen(fileName, "r")) == NULL)
	{
		fprintf(stderr, ">> Error opening input file: \"%s\"\n", fileName);
		exit(-1);
	}
}
void open_out_file(int argc, char *argv[])
{
	char fileName[50];

	outfile = NULL;
	if (argc > 2)
	{
		strcpy(fileName, argv[2]);
	}
	else
	{
		fprintf(stderr, "Enter an output file name: ");
		scanf("%s", fileName);
	}

	if ((outfile = fopen(fileName, "wb")) == NULL)
	{
		fprintf(stderr, ">> Error opening output file: \"%s\"\n", fileName);
		exit(-1);
	}
}

void build_symbol_table()
{
	int loc = 0;
	char line[1000] = "";
	char *input = "";
	char *lexeme = "";
	char *type = "";
	// process data section
	do
	{
		fgets(line, 1000, infile);
	} while (strcmp((input = strtok(line, " ")), "Section") != 0);
	if (strcmp((input = strtok(NULL, " ")), ".data") == 0)
	{
		fprintf(stderr, ">> Error: Missing \"Section .data\"\n");
	}
	else
	{
		fprintf(stderr, "Parsing data section, pass 1\n");
	}

	// build symbol table
	fgets(line, 1000, infile);
	lexeme = strtok(line, delim);

	while (strcmp(lexeme, "Section") != 0)
	{
		if (strstr(lexeme, ":"))
		{
			int len = strlen(lexeme);
			lexeme[len - 1] = '\0';

			type = strtok(NULL, delim);

			insert_into_sym_tab(lexeme, type, loc++);
		}
		else
		{
			fprintf(stderr, ">> Error parsing: \"%s\"\n", line);
		}

		fgets(line, 1000, infile);
		lexeme = strtok(line, delim);
	}

	fprintf(stderr, "Parsing code section, pass 1\n");
	loc = 0;

	while (fgets(line, 1000, infile) != NULL)
	{
		lexeme = strtok(line, delim);

		if (strcmp(lexeme, "LABEL") == 0)
		{
			lexeme = strtok(NULL, delim);
			insert_into_sym_tab(lexeme, "code", loc);
		}
		loc++;
	}
}

void generate_code()
{
	int loc = 0;
	int symTabPtr = 0;
	char line[1000] = "";
	char *input = "";
	char *lexeme = "";
	int operand = 0;
	Symbol entry;

	do
	{
		fgets(line, 1000, infile);
	} while (strcmp((input = strtok(line, " ")), "Section") != 0);
	if (strcmp((input = strtok(NULL, " ")), ".data") == 0)
	{
		fprintf(stderr, ">> Error: Missing \"Section .data\"\n");
	}
	else
	{
		fprintf(stderr, "Parsing data section, pass 2\n");
	}

	// build symbol table
	fgets(line, 1000, infile);
	lexeme = strtok(line, delim);

	// pass over data section
	while (strcmp(lexeme, "Section") != 0)
	{
		fgets(line, 1000, infile);
		lexeme = strtok(line, delim);
	}

	// process code section
	fprintf(stderr, "Parsing code section, pass 2\n");
	loc = 0;

	while (fgets(line, 1000, infile) != NULL)
	{
		lexeme = strtok(line, delim);

		OpCodes opcode = lookup_opcode(lexeme);

		switch (opcode)
		{
		case HALT:
		case POP:
		case STO:
		case COPY:
		case ADD:
		case SUB:
		case MPY:
		case DIV:
		case MOD:
		case NEG:
		case NOT:
		case OR:
		case AND:
		case EQ:
		case NE:
		case GT:
		case GE:
		case LT:
		case LE:
		case LABEL:
		case PRINT:
		case READ:
		case RET:
			// "opcode" will corrospond to the current case
			// since no special actions are needed, just output opcode
			insert_code(loc, opcode, 0);
			break;
		case PUSH:
			lexeme = strtok(NULL, delim);
			operand = atoi(lexeme);
			insert_code(loc, opcode, operand);
			break;
		case RVALUE:
		case LVALUE:
		case GOTO:
		case GOFALSE:
		case GOTRUE:
		case GOSUB:
			lexeme = strtok(NULL, delim);
			symTabPtr = lookup_symbol_address(lexeme);
			insert_code(loc, opcode, symTabPtr);
			break;
		default:
			fprintf(stderr, ">> Error: Unimplemented opcode \"%d\"\n", opcode);
			exit(opcode);
			break;
		}

		loc++;
	}
}

void insert_into_sym_tab(char *_lex, char *_typ, int _addr)
{
	strcpy(symbolTable[symCount].lexeme, _lex);
	strcpy(symbolTable[symCount].type, _typ);
	symbolTable[symCount].address = _addr;
	symCount++;
}

void print_symbol_table()
{
	fprintf(stderr, "%-15s%-7s%-12s\n", "Lexeme", "Type", "Address");
	for (int i = 0; i < symCount; i++)
	{
		fprintf(stderr, "%-15s%-7s%-12d\n", symbolTable[i].lexeme, symbolTable[i].type, symbolTable[i].address);
	}
}

int lookup_opcode(char *opcode)
{
	int len = sizeof(instructions) / sizeof(instructions[0]);
	for (int i = 0; i < len; i++)
	{
		if (strcmp(instructions[i], opcode) == 0)
		{
			return i;
		}
	}
	fprintf(stderr, ">> Error: Invalid opcode \"%s\"\n", opcode);
	return -1;
}

int lookup_symbol_address(char *lexeme)
{
	for (int i = 0; i < symCount; i++)
	{
		if (strcmp(symbolTable[i].lexeme, lexeme) == 0)
		{
			return symbolTable[i].address;
		}
	}
	fprintf(stderr, ">> Error: Invalid symbol \"%s\"\n", lexeme);
	return -1;
}

void insert_code(int loc, int opcode, int operand)
{
	unsigned int num = ((reverseInt(opcode) >> 16) | reverseInt(operand));

	printf("%d\t%d\n", opcode, operand);

	fwrite((const void *)&num, sizeof(int), 1, outfile);
}

int reverseInt(int i)
{
	unsigned char c1, c2, c3, c4;

	if (is_bigendian())
	{
		return i;
	}
	else
	{
		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;

		return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
	}
}