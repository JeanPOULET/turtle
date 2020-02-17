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
NAME [A-z]*

%%
{COMM}+               { printf("Commentaire");                             }
{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
"print"               { return KW_PRINT;                                   }
"forward"             { return KW_FORWARD;                                 }
"fw"                  { return KW_FORWARD;                                 }
"backward"            { return KW_BACKWARD;                                }
"bw"                  { return KW_BACKWARD;                                }
"proc"                { return KW_PROC;                                    }
"call"                { return KW_CALL;                                    }
"left"                { return KW_LEFT;                                    }
"right"               { return KW_RIGHT;                                   }
"up"                  { return KW_UP;                                      }
"down"                { return KW_DOWN;                                    }
"heading"             { return KW_HEADING;                                 } 
"position"            { return KW_POSITION;                                }
"color"               { return KW_COLOR;                                   }
"home"                { return KW_HOME;                                    }
"repeat"              { return KW_REPEAT;                                  }
"set"                 { return KW_SET;                                     }
"red"                 { return RED;                                        }
"green"               { return GREEN;                                      }
"blue"                { return BLUE;                                       }
"cyan"                { return CYAN;                                       }
"yellow"              { return YELLOW;                                     }
"magenta"             { return MAGENTA;                                    }
"black"               { return BLACK;                                      }
"gray"                { return GRAY;                                       }
"white"               { return WHITE;                                      }
{NAME}+               { yylval.name = strdup(yytext); return NAME;         }
"-"                   { return '-';                                        }
"+"                   { return '+';                                        }
"*"                   { return '*';                                        }
"/"                   { return '/';                                        }
"^"                   { return '^';                                        }
"("                   { return '(';                                        }
")"                   { return ')';                                        }
"{"                   { return '{';                                        }
"}"                   { return '}';                                        }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
