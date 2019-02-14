
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

"//".*
"/*"	BEGIN(BLOCK_COMMENT);
<BLOCK_COMMENT>"*/"	BEGIN(INITIAL);
<BLOCK_COMMENT>[^*\n]+
<BLOCK_COMMENT>"*"
<BLOCK_COMMENT>\n	yylineno++;


[\r\n]+ {
    if(g_tokens && NEED_SEMI_CONLON){
        printf("tSEMICOLON\n");
        return tSEMICOLON;
    }
}
[ \t]+

break       {if (g_tokens) printf("tBREAK\n"); NEED_SEMI_CONLON = 1; return tBREAK; }
case       {if (g_tokens) printf("tCASE\n"); return tCASE; }
chan       {if (g_tokens) printf("tCHAN\n"); return tCHAN; }
const      {if (g_tokens) printf("tCONST\n"); return tCONST; }
continue   {if (g_tokens) printf("tCONTINUE\n"); NEED_SEMI_CONLON = 1; return tCONTINUE; }
default    {if (g_tokens) printf("tDEFAULT\n"); return tDEFAULT; }
defer      {if (g_tokens) printf("tDEFER\n"); return tDEFER; }
fallthrough {if (g_tokens) printf("tFALLTHROUGH\n"); NEED_SEMI_CONLON = 1; return tFALLTHROUGH;}
for         {if (g_tokens) printf("tFOR\n"); return tFOR; }
go          {if (g_tokens) printf("tGO\n"); return tGO; }
goto        {if (g_tokens) printf("tGOTO\n"); return tGOTO; }
import      {if (g_tokens) printf("tIMPORT\n"); return tIMPORT; }
interface   {if (g_tokens) printf("tINTERFACE\n"); return tINTERFACE;}
map         {if (g_tokens) printf("tMAP\n"); return tMAP; }
package     {if (g_tokens) printf("tPACKAGE\n"); return tPACKAGE; }
range       {if (g_tokens) printf("tRANGE\n"); return tRANGE;}
return      {if (g_tokens) printf("tRETURN\n"); NEED_SEMI_CONLON = 1; return tRETURN; }
select      {if (g_tokens) printf("tSELECT\n"); return tSELECT; }
struct      {if (g_tokens) printf("tSTRUCT\n"); return tSTRUCT; }
switch      {if (g_tokens) printf("tSWITCH\n"); return tSWITCH; }
type        {if (g_tokens) printf("tTYPE\n"); return tTYPE;}
println      {if (g_tokens) printf("tPRINTLN\n"); return tPRINTLN;}
append       {if (g_tokens) printf("tAPPEND\n"); return tAPPEND;}
len          {if (g_tokens) printf("tLEN\n"); return tLEN;}
cap          {if (g_tokens) printf("tCAP\n"); return tCAP;}

"%"         {if (g_tokens) printf("tMOD\n");return tMOD;}
"&"         {if (g_tokens) printf("tBITWISEAND\n");return tBITWISEAND;}
"|"         {if (g_tokens) printf("tBITWISEOR\n");return tBITWISEOR;}
"^"         {if (g_tokens) printf("tBITWISEXOR\n");return tBITWISEXOR;}
"&^"         {if (g_tokens) printf("tBITCLEAR\n");return tBITCLEAR;}

"<<"         {if (g_tokens) printf("tLEFTSHIFT\n");return tLEFTSHIFT;}
">>"         {if (g_tokens) printf("tRIGHTSHIFT\n");return tRIGHTSHIFT;}

"+="         {if (g_tokens) printf("tPLUSEQUAL\n");return tPLUSEQUAL;}
"-="         {if (g_tokens) printf("tMINUSEQUAL\n");return tMINUSEQUAL;}
"*="         {if (g_tokens) printf("tTIMESEQUAL\n");return tTIMESEQUAL;}
"/="         {if (g_tokens) printf("tDIVEQUAL\n");return tDIVEQUAL;}
"%="         {if (g_tokens) printf("tMODEQUAL\n");return tMODEQUAL;}

"++"         {if (g_tokens) printf("tPLUSPLUS\n");NEED_SEMI_CONLON = 1;
return tPLUSPLUS;}
"--"         {if (g_tokens) printf("tMINUSMINUS\n");NEED_SEMI_CONLON = 1;
return tMINUSMINUS;}

"&="         {if (g_tokens) printf("tANDEQUAL\n");return tANDEQUAL;}
"|="         {if (g_tokens) printf("tOREQUAL\n");return tOREQUAL;}
"^="         {if (g_tokens) printf("tXOREQUAL\n");return tXOREQUAL;}
"<<="         {if (g_tokens) printf("tLEFTSHIFTEQUAL\n");return tLEFTSHIFTEQUAL;}
">>="         {if (g_tokens) printf("tRIGHTSHIFTEQUAL\n");return tRIGHTSHIFTEQUAL;}
"&^="         {if (g_tokens) printf("tBITCLEAREQUAL\n");return tBITCLEAREQUAL;}

":="         {if (g_tokens) printf("tCOLONEQUAL\n");return tCOLONEQUAL;}
"..."         {if (g_tokens) printf("tDOTDOTDOT\n");return tDOTDOTDOT;}
","         {if (g_tokens) printf("tCOMMA\n");return tCOMMA;}
"."         {if (g_tokens) printf("tDOT\n");return tDOT;}

var         {if (g_tokens) printf("tVAR\n");return tVAR;}
float       {yylval.type = stingToTYPE("float"); if (g_tokens) printf("tFLOAT\n");return tFLOAT;}
int         {yylval.type = stingToTYPE("int"); if (g_tokens) printf("tINT\n");return tINT;}
string      {yylval.type = stingToTYPE("string"); if (g_tokens) printf("tSTRING\n");return tSTRING;}
boolean     {yylval.type = stingToTYPE("boolean"); if (g_tokens) printf("tBOOLEAN\n");return tBOOLEAN;}
if          {if (g_tokens) printf("tIF\n");return tIF;}
else        {if (g_tokens) printf("tELSE\n");return tELSE;}
while       {if (g_tokens) printf("tWHILE\n");return tWHILE;}
read        {if (g_tokens) printf("tREAD\n");return tREAD;}
print       {if (g_tokens) printf("tPRINT\n");return tPRINT;}
true        {if (g_tokens) printf("tTRUE\n");return tTRUE;}
false       {if (g_tokens) printf("tFALSE\n");return tFALSE;}
:           {if (g_tokens) printf("tCOLON\n");return tCOLON;}
=           {if (g_tokens) printf("tASSIGN\n");return tASSIGN;}
;           {if (g_tokens) printf("tSEMICOLON\n"); NEED_SEMI_CONLON = 0; return tSEMICOLON;}

"+"         {if (g_tokens) printf("tPLUS\n");return tPLUS;}
"-"         {if (g_tokens) printf("tMINUS\n");return tMINUS;}
"*"         {if (g_tokens) printf("tTIMES\n");return tTIMES;}
"/"         {if (g_tokens) printf("tDIV\n");return tDIV;}

"=="        {if (g_tokens) printf("tEQUALS\n");return tEQUALS;}
"!="        {if (g_tokens) printf("tNOTEQUALS\n");return tNOTEQUALS;}
">="        {if (g_tokens) printf("tGREATEREQUALS\n");return tGREATEREQUALS;}
"<="        {if (g_tokens) printf("tLESSEQUALS\n");return tLESSEQUALS;}
">"         {if (g_tokens) printf("tGREATER\n");return tGREATER;}
"<"         {if (g_tokens) printf("tLESS\n");return tLESS;}
"&&"        {if (g_tokens) printf("tAND\n");return tAND;}
"||"        {if (g_tokens) printf("tOR\n");return tOR;}

"("         {if (g_tokens) printf("tLEFTPAREN\n");return tLEFTPAREN;}
")"         {if (g_tokens) printf("tRIGHTPAREN\n"); NEED_SEMI_CONLON = 1; return tRIGHTPAREN;}
"["         {if (g_tokens) printf("tLEFTSQUAREBRACKET\n");return tLEFTSQUAREBRACKET;}
"]"         {if (g_tokens) printf("tRIGHTSQUAREBRACKET\n"); NEED_SEMI_CONLON = 1; return tRIGHTSQUAREBRACKET;}
"{"         {if (g_tokens) printf("tLEFTBRACE\n");return tLEFTBRACE;}
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
    return tBANG;
}



.       { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%