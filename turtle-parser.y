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

/* TODO: add other tokens */

%type <node> unit cmds cmd expr


%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr   { }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
