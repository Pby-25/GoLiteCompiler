
%{
#include <stdio.h>
#include "mini.tab.h"
#include "main.h"
#include <string.h>
#include "tree.h"

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
int NEED_SEMI_CONLON=0;
%}


DIGIT [0-9]
INT_DECIMAL 0|([1-9]{DIGIT}*)
INT_OCTAL 0[0-7]*
INT_HEX 0x[0-9a-fA-F]*
INT ({INT_DECIMAL}|{INT_OCTAL}|{INT_HEX})
FLOAT {INT_DECIMAL}?\.{DIGIT}*
RUNE '(.|\\a|\\b|\\f|\\n|\\r|\\t|\\v|\\\\|\\')'
STRING_ITP \"([a-zA-Z0-9 ~!@#$%^&*\-+\/`<>=_|';:.,?{}\[\]\(\)]*([\\]["'abfnrtv\\])*)*\"
STRING_RAW '[^']*'


%option yylineno
%x BLOCK_COMMENT

/* Note the use of 3 keywords:
*    - yyleng: Length of the scanned token
*    - yytext: Matched text
*    - yylineno: Convenience variable for the line number provided by %option yylineno
*/

%%

"//".* {
    if(NEED_SEMI_CONLON){
        if(g_tokens){
            printf("tSEMICOLON\n");
        }
        NEED_SEMI_CONLON = 0;
        return tSEMICOLON;
    }
}
"/*"	BEGIN(BLOCK_COMMENT);
<BLOCK_COMMENT>"*/"	BEGIN(INITIAL);
<BLOCK_COMMENT>[^*\n]+
<BLOCK_COMMENT>"*"
<BLOCK_COMMENT>\n	{ 
        yylineno++;
        NEED_SEMI_CONLON = 0;
        return tSEMICOLON;
    }
<BLOCK_COMMENT><<EOF>> {fprintf (stderr, "Error: (line %d) block comment not closed\n", yylineno); exit(1);}

[\r\n]+ {
    if(NEED_SEMI_CONLON){
        if(g_tokens){
            printf("tSEMICOLON\n");
        }
        NEED_SEMI_CONLON = 0;
        return tSEMICOLON;
    }
}

<<EOF>>  {
    if(NEED_SEMI_CONLON){
        if(g_tokens){
            printf("tSEMICOLON\n");
        }
        NEED_SEMI_CONLON = 0;
        return tSEMICOLON;
    } else {
        yyterminate();
    }
}

[ \t]+ {}

break       {if (g_tokens) printf("tBREAK\n"); NEED_SEMI_CONLON = 1; return tBREAK; }
case       {if (g_tokens) printf("tCASE\n"); NEED_SEMI_CONLON = 0; return tCASE; }
chan       {if (g_tokens) printf("tCHAN\n"); NEED_SEMI_CONLON = 0;return tCHAN; }
const      {if (g_tokens) printf("tCONST\n"); NEED_SEMI_CONLON = 0;return tCONST; }
continue   {if (g_tokens) printf("tCONTINUE\n"); NEED_SEMI_CONLON = 1; return tCONTINUE; }
default    {if (g_tokens) printf("tDEFAULT\n"); NEED_SEMI_CONLON = 0;return tDEFAULT; }
defer      {if (g_tokens) printf("tDEFER\n"); NEED_SEMI_CONLON = 0;return tDEFER; }
fallthrough {if (g_tokens) printf("tFALLTHROUGH\n"); NEED_SEMI_CONLON = 1; return tFALLTHROUGH;}
for         {if (g_tokens) printf("tFOR\n"); NEED_SEMI_CONLON = 0;return tFOR; }
go          {if (g_tokens) printf("tGO\n"); NEED_SEMI_CONLON = 0;return tGO; }
goto        {if (g_tokens) printf("tGOTO\n"); NEED_SEMI_CONLON = 0;return tGOTO; }
import      {if (g_tokens) printf("tIMPORT\n"); NEED_SEMI_CONLON = 0;return tIMPORT; }
interface   {if (g_tokens) printf("tINTERFACE\n"); NEED_SEMI_CONLON = 0;return tINTERFACE;}
map         {if (g_tokens) printf("tMAP\n"); NEED_SEMI_CONLON = 0;return tMAP; }
package     {if (g_tokens) printf("tPACKAGE\n"); NEED_SEMI_CONLON = 0;return tPACKAGE; }
range       {if (g_tokens) printf("tRANGE\n"); NEED_SEMI_CONLON = 0;return tRANGE;}
return      {if (g_tokens) printf("tRETURN\n"); NEED_SEMI_CONLON = 1; return tRETURN; }
select      {if (g_tokens) printf("tSELECT\n"); NEED_SEMI_CONLON = 0;return tSELECT; }
struct      {if (g_tokens) printf("tSTRUCT\n"); NEED_SEMI_CONLON = 0;return tSTRUCT; }
switch      {if (g_tokens) printf("tSWITCH\n"); NEED_SEMI_CONLON = 0;return tSWITCH; }
type        {if (g_tokens) printf("tTYPE\n"); NEED_SEMI_CONLON = 0;return tTYPE;}
println      {if (g_tokens) printf("tPRINTLN\n"); NEED_SEMI_CONLON = 0;return tPRINTLN;}
append       {if (g_tokens) printf("tAPPEND\n"); NEED_SEMI_CONLON = 0;return tAPPEND;}
len          {if (g_tokens) printf("tLEN\n"); NEED_SEMI_CONLON = 0;return tLEN;}
cap          {if (g_tokens) printf("tCAP\n"); NEED_SEMI_CONLON = 0;return tCAP;}

"%"         {if (g_tokens) printf("tMOD\n");NEED_SEMI_CONLON = 0;return tMOD;}
"&"         {if (g_tokens) printf("tBITWISEAND\n");NEED_SEMI_CONLON = 0;return tBITWISEAND;}
"|"         {if (g_tokens) printf("tBITWISEOR\n");NEED_SEMI_CONLON = 0;return tBITWISEOR;}
"^"         {if (g_tokens) printf("tBITWISEXOR\n");NEED_SEMI_CONLON = 0;return tBITWISEXOR;}
"&^"         {if (g_tokens) printf("tBITCLEAR\n");NEED_SEMI_CONLON = 0;return tBITCLEAR;}

"<<"         {if (g_tokens) printf("tLEFTSHIFT\n");NEED_SEMI_CONLON = 0;return tLEFTSHIFT;}
">>"         {if (g_tokens) printf("tRIGHTSHIFT\n");NEED_SEMI_CONLON = 0;return tRIGHTSHIFT;}

"+="         {if (g_tokens) printf("tPLUSEQUAL\n");NEED_SEMI_CONLON = 0;return tPLUSEQUAL;}
"-="         {if (g_tokens) printf("tMINUSEQUAL\n");NEED_SEMI_CONLON = 0;return tMINUSEQUAL;}
"*="         {if (g_tokens) printf("tTIMESEQUAL\n");NEED_SEMI_CONLON = 0;return tTIMESEQUAL;}
"/="         {if (g_tokens) printf("tDIVEQUAL\n");NEED_SEMI_CONLON = 0;return tDIVEQUAL;}
"%="         {if (g_tokens) printf("tMODEQUAL\n");NEED_SEMI_CONLON = 0;return tMODEQUAL;}

"++"         {if (g_tokens) printf("tPLUSPLUS\n");NEED_SEMI_CONLON = 1;return tPLUSPLUS;}
"--"         {if (g_tokens) printf("tMINUSMINUS\n");NEED_SEMI_CONLON = 1;return tMINUSMINUS;}

"&="         {if (g_tokens) printf("tANDEQUAL\n");NEED_SEMI_CONLON = 0;return tANDEQUAL;}
"|="         {if (g_tokens) printf("tOREQUAL\n");NEED_SEMI_CONLON = 0;return tOREQUAL;}
"^="         {if (g_tokens) printf("tXOREQUAL\n");NEED_SEMI_CONLON = 0;return tXOREQUAL;}
"<<="         {if (g_tokens) printf("tLEFTSHIFTEQUAL\n");NEED_SEMI_CONLON = 0;return tLEFTSHIFTEQUAL;}
">>="         {if (g_tokens) printf("tRIGHTSHIFTEQUAL\n");NEED_SEMI_CONLON = 0;return tRIGHTSHIFTEQUAL;}
"&^="         {if (g_tokens) printf("tBITCLEAREQUAL\n");NEED_SEMI_CONLON = 0;return tBITCLEAREQUAL;}

":="         {if (g_tokens) printf("tCOLONEQUAL\n");NEED_SEMI_CONLON = 0;return tCOLONEQUAL;}
"..."         {if (g_tokens) printf("tDOTDOTDOT\n");NEED_SEMI_CONLON = 0;return tDOTDOTDOT;}
","         {if (g_tokens) printf("tCOMMA\n");NEED_SEMI_CONLON = 0;return tCOMMA;}
"."         {if (g_tokens) printf("tDOT\n");NEED_SEMI_CONLON = 0;return tDOT;}

func        {if (g_tokens) printf("tFUNC\n"); NEED_SEMI_CONLON = 0;return tFUNC;}
var         {if (g_tokens) printf("tVAR\n");NEED_SEMI_CONLON = 0;return tVAR;}
if          {if (g_tokens) printf("tIF\n");NEED_SEMI_CONLON = 0;return tIF;}
else        {if (g_tokens) printf("tELSE\n");NEED_SEMI_CONLON = 0;return tELSE;}
while       {if (g_tokens) printf("tWHILE\n");NEED_SEMI_CONLON = 0;return tWHILE;}
read        {if (g_tokens) printf("tREAD\n");NEED_SEMI_CONLON = 0;return tREAD;}
print       {if (g_tokens) printf("tPRINT\n");NEED_SEMI_CONLON = 0;return tPRINT;}
true        {if (g_tokens) printf("tTRUE\n");NEED_SEMI_CONLON = 0;return tTRUE;}
false       {if (g_tokens) printf("tFALSE\n");NEED_SEMI_CONLON = 0;return tFALSE;}
:           {if (g_tokens) printf("tCOLON\n");NEED_SEMI_CONLON = 0;return tCOLON;}
=           {if (g_tokens) printf("tASSIGN\n");NEED_SEMI_CONLON = 0;return tASSIGN;}
;           {if (g_tokens) printf("tSEMICOLON\n"); NEED_SEMI_CONLON = 0; return tSEMICOLON;}

"+"         {if (g_tokens) printf("tPLUS\n");NEED_SEMI_CONLON = 0;return tPLUS;}
"-"         {if (g_tokens) printf("tMINUS\n");NEED_SEMI_CONLON = 0;return tMINUS;}
"*"         {if (g_tokens) printf("tTIMES\n");NEED_SEMI_CONLON = 0;return tTIMES;}
"/"         {if (g_tokens) printf("tDIV\n");NEED_SEMI_CONLON = 0;return tDIV;}

"=="        {if (g_tokens) printf("tEQUALS\n");NEED_SEMI_CONLON = 0;return tEQUALS;}
"!="        {if (g_tokens) printf("tNOTEQUALS\n");NEED_SEMI_CONLON = 0;return tNOTEQUALS;}
">="        {if (g_tokens) printf("tGREATEREQUALS\n");NEED_SEMI_CONLON = 0;return tGREATEREQUALS;}
"<="        {if (g_tokens) printf("tLESSEQUALS\n");NEED_SEMI_CONLON = 0;return tLESSEQUALS;}
">"         {if (g_tokens) printf("tGREATER\n");NEED_SEMI_CONLON = 0;return tGREATER;}
"<"         {if (g_tokens) printf("tLESS\n");NEED_SEMI_CONLON = 0;return tLESS;}
"&&"        {if (g_tokens) printf("tAND\n");NEED_SEMI_CONLON = 0;return tAND;}
"||"        {if (g_tokens) printf("tOR\n");NEED_SEMI_CONLON = 0;return tOR;}

"("         {if (g_tokens) printf("tLEFTPAREN\n");NEED_SEMI_CONLON = 0;return tLEFTPAREN;}
")"         {if (g_tokens) printf("tRIGHTPAREN\n"); NEED_SEMI_CONLON = 1; return tRIGHTPAREN;}
"["         {if (g_tokens) printf("tLEFTSQUAREBRACKET\n");NEED_SEMI_CONLON = 0;return tLEFTSQUAREBRACKET;}
"]"         {if (g_tokens) printf("tRIGHTSQUAREBRACKET\n"); NEED_SEMI_CONLON = 1; return tRIGHTSQUAREBRACKET;}
"{"         {if (g_tokens) printf("tLEFTBRACE\n");NEED_SEMI_CONLON = 0; return tLEFTBRACE;}
"}"         {if (g_tokens) printf("tRIGHTBRACE\n"); NEED_SEMI_CONLON = 1; return tRIGHTBRACE;}


{FLOAT} {
        if(yytext[0]=='0' && strlen(yytext)>=2 && yytext[1]!='.'){
            fprintf (stderr, "Error: (line %d) invalid float '%s'\n", yylineno, yytext);
            exit(1);
        }else{
            yylval.floatval = atof(yytext);
            if (g_tokens) printf ("tFOLATVAL(%s)\n", yytext);
            NEED_SEMI_CONLON = 1;
           return tFLOATVAL;
        }
}

{INT} {
        if(yytext[0]=='0' && strlen(yytext)!=1){
            fprintf (stderr, "Error: (line %d) invalid integer '%s'\n", yylineno, yytext);
            exit(1);
        }else{
            if (g_tokens) printf ("tINTVAL(%s)\n", yytext);
            yylval.intval = atoi(yytext);
            NEED_SEMI_CONLON = 1;
            return tINTVAL;
        }

}

_|([a-zA-Z_][a-zA-Z0-9_]*) {
        yylval.stringval = strdup(yytext);
 	   if (g_tokens) printf ("tIDENTIFIER(%s)\n", yylval.stringval);
         NEED_SEMI_CONLON = 1;
        return tIDENTIFIER;
}

{RUNE}	{
        yylval.stringval = strdup(yytext);
        if (g_tokens) printf("tRUNEVAL(%s)\n",yylval.stringval);
         NEED_SEMI_CONLON = 1;
        return tRUNEVAL;
}


{STRING_ITP} {
        yylval.stringval = strdup(yytext);
        if (g_tokens) printf("tSTRINGITPVAL(%s)\n",yylval.stringval);
         NEED_SEMI_CONLON = 1;
        return tSTRINGITPVAL;
}

{STRING_RAW} {
        yylval.stringval = strdup(yytext);
        if (g_tokens) printf("tSTRINGRAWVAL(%s)\n",yylval.stringval);
         NEED_SEMI_CONLON = 1;
        return tSTRINGRAWVAL;
}

! {
    if (g_tokens) printf("tBANG");
    NEED_SEMI_CONLON = 0;
    return tBANG;
}



.       { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%