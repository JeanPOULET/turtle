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
  char *name;
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
%token            KW_SIN      "sin"
%token            KW_COS      "cos"
%token            KW_TAN      "tan"
%token            KW_SQRT     "sqrt"
%token            KW_RANDOM   "random"

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
%left '+' '-'
%left '*' '/'

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;



cmd:
    KW_FORWARD      expr                  {$$ = make_cmd_forward($2);    }  
  | KW_BACKWARD     expr                  {$$ = make_cmd_backward($2);   }
  | KW_LEFT         expr                  {$$ = make_cmd_left($2);       }
  | KW_RIGHT        expr                  {$$ = make_cmd_right($2);      }
  | KW_UP                                 {$$ = make_cmd_up();           }
  | KW_DOWN                               {$$ = make_cmd_down();         }
  | KW_POSITION expr ',' expr             {$$ = make_cmd_position($2,$4);}
  | KW_COLOR      color                   {$$ = make_cmd_color($2);      }
  | KW_COLOR  expr ',' expr ',' expr      {$$ = make_cmd_color_triple($2,$4,$6);     }
  | KW_HEADING      expr                  {$$ = make_cmd_heading($2);    }
  | KW_HOME                               {$$ = make_cmd_home();         }
  | KW_PRINT        expr                  {$$ = make_cmd_print($2);      }
  | KW_REPEAT       expr cmd              {$$ = make_cmd_repeat($2,$3);  }
  | KW_PROC         NAME cmd              {$$ = make_cmd_proc($2, $3);   }
  | KW_CALL         expr                  {$$ = make_cmd_call($2);       }
  | KW_SET          NAME expr             {$$ = make_cmd_set($2,$3);     }
  | '{' cmds '}'                          {$$ = make_cmd_block($2);      }
;

color:
    RED               {$$ = make_color_value(0);}
  | GREEN             {$$ = make_color_value(1);}
  | BLUE              {$$ = make_color_value(2);}
  | CYAN              {$$ = make_color_value(3);}
  | YELLOW            {$$ = make_color_value(4);}
  | MAGENTA           {$$ = make_color_value(5);}
  | BLACK             {$$ = make_color_value(6);}
  | GRAY              {$$ = make_color_value(7);}
  | WHITE             {$$ = make_color_value(8);}
;

expr:
    VALUE                             {$$ = make_expr_value($1);       }
  | NAME                              {$$ = make_expr_name($1);        }
  | '-'  expr                         {$$ = make_expr_unop($2);        }
  | expr  '*'  expr                   {$$ = make_expr_binop('*',$1,$3);}
  | expr  '/'  expr                   {$$ = make_expr_binop('/',$1,$3);}
  | expr  '-'  expr                   {$$ = make_expr_binop('-',$1,$3);}
  | expr  '+'  expr                   {$$ = make_expr_binop('+',$1,$3);} 
  | expr  '^'  expr                   {$$ = make_expr_binop('^',$1,$3);}
  | KW_SIN     expr                   {$$ = make_cmd_sin($2);          }
  | KW_COS     expr                   {$$ = make_cmd_cos($2);          }
  | KW_TAN     expr                   {$$ = make_cmd_tan($2);          }
  | KW_SQRT    expr                   {$$ = make_cmd_sqrt($2);         }
  | KW_RANDOM  '(' expr ',' expr ')'  {$$ = make_cmd_random($3,$5);    }
  | '(' expr ')'                      {$$ = make_expr_block($2);       }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
