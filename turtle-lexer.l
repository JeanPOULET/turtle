%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
COMM  #{1}[^\n]*
%%
{COMM}+               { printf("Commentaire");}
{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
"print"               { return KW_PRINT;                                   }

"forward"             { return KW_FORWARD;                                 }
"backward"            { return KW_BACKWARD;                                }
"left"                { return KW_LEFT;                                    }
"right"               { return KW_RIGHT;                                   }
"up"                  { return KW_UP;                                      }
"down"                { return KW_DOWN;                                    }
"heading"             { return KW_HEADING;                                 } 
"position"            { return KW_POSITION;                                }
"color"               { return KW_COLOR;                                   }
"home"                { return KW_HOME;                                    }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
