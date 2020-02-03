%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
STR   [A-z]*
%%

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
"forward"             { return KW_FORWARD;                                 }
"backward"            { return KW_BACKWARD;                                }
"left"                { return KW_LEFT;                                    }
"right"               { return KW_RIGHT;                                   }
"up"                  { return KW_UP;                                      }
"down"                { return KW_DOWN;                                    }
"heading"             { return KW_HEADING;                                } 

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
