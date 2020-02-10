%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  const char *name;
  struct ast_node *node;
}

%union {
  float red;
  float green;
  float blue;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_LEFT     "left"
%token            KW_RIGHT    "right"
%token            KW_COLOR    "color"
%token            KW_UP       "up"
%token            KW_DOWN     "down"
%token            KW_PRINT    "print"
%token            KW_HEADING  "heading"
%token            KW_POSITION "position"
%token            KW_HOME     "home"
%token            KW_REPEAT   "repeat"
%token            KW_PROC     "proc"
%token            KW_CALL     "call"
%token            KW_SET      "set"
%token            RED         "red"
%token            BLUE        "blue"
%token            YELLOW      "yellow"
%token            CYAN        "cyan"
%token            GRAY        "gray"
%token            WHITE       "white"
%token            BLACK       "black"
%token            MAGENTA     "magenta"
%token            GREEN       "green"
/* TODO: add other tokens */

%type <node> unit cmds cmd expr color


%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;



cmd:
    KW_FORWARD    expr    {$$ = make_cmd_forward($2);    }  
  | KW_BACKWARD   expr    {$$ = make_cmd_backward($2);   }
  | KW_LEFT       expr    {$$ = make_cmd_left($2);       }
  | KW_RIGHT      expr    {$$ = make_cmd_right($2);      }
  | KW_UP                 {$$ = make_cmd_up();           }
  | KW_DOWN               {$$ = make_cmd_down();         }
  | KW_PROC       expr    {$$ = make_cmd_proc($2);       }
  | KW_CALL       expr    {$$ = make_cmd_call($2);       }
  | KW_SET      expr expr {$$ = make_cmd_set($2,$3);     }
  | KW_POSITION expr expr {$$ = make_cmd_position($2,$3);}
  | KW_COLOR      color   {$$ = make_cmd_color($2);     }
  | KW_COLOR  VALUE VALUE VALUE    {$$ = make_cmd_color();     }
  | KW_HEADING    expr    {$$ = make_cmd_heading($2);    }
  | KW_HOME               {$$ = make_cmd_home();         }
  | KW_REPEAT expr expr   {$$ = make_cmd_repeat($2,$3);  }
;

color:
    RED               { $$ = make_color_value(0);}
;

expr:
    VALUE             { $$ = make_expr_value($1); }
  | NAME              { $$ = make_expr_name($1);  }
  | "-" expr          { $$ = make_expr_unop($2);  }
  | expr "-" expr     { $$ = make_expr_binop('-',$1,$3);}
  | expr "+" expr     { $$ = make_expr_binop('+',$1,$3);}


;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
