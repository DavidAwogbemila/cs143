
/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>
#include <string.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;
char *curr_string_error_msg = "";
bool string_is_bad = false;
short int comment_balance = 0;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
%}

%x MULTILINE_COMMENT SINGLE_LINE_COMMENT IN_STRING

/*
 * Define names for regular expressions here.
 */
ENDL		"\n"

MULTILINE_COMMENT_START	\(\*
MULTILINE_COMMENT_END	\*\)
SINGLE_LINE_COMMENT_START --

DARROW          =>
CLASS		[cC][lL][aA][sS][sS]
ELSE		[eE][lL][sS][eE]
IF		[iI][fF]
FI		[fF][iI]
IN		[iI][nN]
INHERITS	[iI][nN][hH][eE][rR][iI][tT][sS]
LET		[lL][eE][tT]
LOOP		[lL][oO][oO][pP]
POOL		[pP][oO][oO][lL]
THEN		[tT][hH][eE][nN]
WHILE		[wW][hH][iI][lL][eE]
CASE		[cC][aA][sS][eE]
ESAC		[eE][sS][aA][cC]
OF		[oO][fF]
NEW		[nN][eE][wW]
ISVOID		[iI][sS][vV][oO][iI][dD]
NOT 		[nN][oO][tT]
STR_CONST	\"
INT_CONST	[0-9]+
BOOL_CONST	t+[rR][uU][eE]|f[aA][lL][sS][eE]
TYPEID		[A-Z][a-zA-Z0-9_]*
OBJECTID	[a-z][a-zA-Z0-9_]*
ASSIGN		<-
SINGLE_CHARS [;,{}:().\-*<=~@/+]
LE "<="
BLANK_SPACE [\f\r\t\v\ ]+
noway .


%%

 /*
  *  Nested comments
  */
 /*
  *  The multiple-character operators.
  */
{SINGLE_LINE_COMMENT_START} {
			BEGIN SINGLE_LINE_COMMENT;
			}

<SINGLE_LINE_COMMENT>[\40-\176] { 

		}

<SINGLE_LINE_COMMENT><<EOF>> {
			BEGIN(INITIAL);
			}

<SINGLE_LINE_COMMENT>"\n" {
			curr_lineno++;
			BEGIN(INITIAL);
		}

{MULTILINE_COMMENT_START} {
			BEGIN MULTILINE_COMMENT;
			comment_balance++;
		}
<MULTILINE_COMMENT>{MULTILINE_COMMENT_START} { comment_balance++; }

<MULTILINE_COMMENT>[^*\n] {
}

<MULTILINE_COMMENT><<EOF>> {
	BEGIN(INITIAL);
	cool_yylval.error_msg = "EOF in comment";
	return (ERROR);
}

<MULTILINE_COMMENT>"*"+[^*)\n] {
}
<MULTILINE_COMMENT>"\n" {
		curr_lineno++;
}
<MULTILINE_COMMENT>"*)" {
		comment_balance--;
		if (comment_balance == 0) BEGIN(INITIAL);
}

<MULTILINE_COMMENT>[*] {
}

<IN_STRING><<EOF>> {
			cool_yylval.error_msg = "EOF in string constant";
			curr_string_error_msg = "EOF in string constant";
			BEGIN (INITIAL);
			return (ERROR);
		}
<IN_STRING>\0 {
			cool_yylval.error_msg = "String contains null character";
			curr_string_error_msg = "String contains null character";
			string_is_bad = true;
			//BEGIN (INITIAL);
			//return (ERROR);
		}

<IN_STRING>\n {			
			cool_yylval.symbol = stringtable.add_string(string_buf);
			cool_yylval.error_msg = "Unterminated string";
			curr_string_error_msg = "Unterminated string";
			string_buf_ptr = string_buf;
			memset(string_buf, 0, strlen(string_buf));
			BEGIN(INITIAL);
			curr_lineno++;
			return (ERROR);
			}

<IN_STRING>[^"\\\n\0]* { 
			int str_length = strlen(string_buf);
			if (str_length >= 1025) {	
				cool_yylval.symbol = stringtable.add_string(string_buf);
				cool_yylval.error_msg = "String constant too long";
				curr_string_error_msg = "String constant too long";
				return (ERROR);
			}
			memcpy(string_buf_ptr, yytext, strlen(yytext));
				cool_yylval.symbol = stringtable.add_string(string_buf);
			string_buf_ptr += strlen(yytext);
		}

<IN_STRING>[\\][\n] {
		*string_buf_ptr = '\n';
		string_buf_ptr++;
		curr_lineno ++;
}

<IN_STRING>[\\][^\n]  {
			if (strlen(string_buf) == 1024) { 	
				cool_yylval.symbol = stringtable.add_string(string_buf);
				cool_yylval.error_msg = "String constant too long";
				curr_string_error_msg = "String constant too long";
				//printf("no mas no mas\n");
				string_is_bad = true;
				//return (ERROR);
			}

			switch(yytext[1]) {
			case 'b':{
				*string_buf_ptr = '\b';
				break;
			}
			case 't':{
				*string_buf_ptr = '\t'; 
				break;
			}
			case 'n':{
				*string_buf_ptr = '\n';
				break;
			}
			case 'f':{
				*string_buf_ptr = '\f';
				break;
			}
			case '\\':{
				//printf("yytext=[%s]\n", yytext);
				*string_buf_ptr = '\\';
				break;
			}
			case 0: {
				cool_yylval.symbol = stringtable.add_string(string_buf);
				string_buf_ptr = string_buf;
				cool_yylval.error_msg = "String contains escaped null character";
				curr_string_error_msg = "String contains escaped null character";
				string_is_bad = true;
				break;
			}
			default: {
				*string_buf_ptr = yytext[1];
			}
		}
		string_buf_ptr++;
	}


<IN_STRING>\"	{
			BEGIN(INITIAL);
			cool_yylval.symbol = stringtable.add_string(string_buf);
			if (strlen(string_buf) > 1024) {
				cool_yylval.error_msg = "String constant too long";
				string_is_bad = false;
				memset(string_buf, 0, strlen(string_buf));
				string_buf_ptr = string_buf;
				return (ERROR);
			}
			memset(string_buf, 0, strlen(string_buf));
			string_buf_ptr = string_buf;
			if (string_is_bad) {
				cool_yylval.error_msg = curr_string_error_msg;
				string_is_bad = false;
				return ERROR;
			}
			return STR_CONST;
		}

{DARROW}	{	return (DARROW);	}
{CLASS}		{	return (CLASS);	}
{ELSE}		{	return (ELSE);		}
{FI}		{	return (FI);		}
{IF}		{	return (IF);		}
{IN}		{	return (IN);		}
{INHERITS}	{	return (INHERITS);	}
{LET}		{	return (LET);		}
{LOOP}		{	return (LOOP);		}
{POOL}		{	return (POOL);		}
{THEN}		{	return (THEN);		}
{WHILE}		{	return (WHILE);		}
{CASE}		{	return (CASE);		}
{ESAC}		{	return (ESAC);		}
{OF}		{	return (OF);		}
{NEW}		{	return (NEW);		}
{ISVOID}	{ 	return (ISVOID);	}
{NOT}		{	return (NOT);		}

{SINGLE_CHARS} {	return yytext[0];	}
{LE} 		   {	return LE;	}
{BLANK_SPACE}  {					}

{STR_CONST}	{
			string_buf_ptr = string_buf;
			BEGIN(IN_STRING);
		}
{INT_CONST} {
			cool_yylval.symbol = inttable.add_string(yytext);
			return (INT_CONST); 
		}
{BOOL_CONST} { 
			if (yytext[0] == 't' || yytext[0] == 'T') {
				cool_yylval.boolean = true;
			} else {
				cool_yylval.boolean = false;
			}
			return (BOOL_CONST);
		}
{TYPEID}	{
			cool_yylval.symbol = stringtable.add_string(yytext);
			return (TYPEID);
		}
{OBJECTID}	{	
			cool_yylval.symbol = stringtable.add_string(yytext);
			return (OBJECTID);
		}
{ASSIGN}	{	
			return (ASSIGN);
		}
{ENDL}		{
			curr_lineno++;
		}

{MULTILINE_COMMENT_END} {
			cool_yylval.error_msg = "Unmatched *)";
			return ERROR;
		}
{noway} 	{
			cool_yylval.error_msg = yytext; return ERROR;
			}
 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */


%%
