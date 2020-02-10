#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_expr_name(const char *name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->u.name = name;
  return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->u.value = expr->u.value;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  
  return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->u.value = expr->u.value;
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;

  return node;
}

struct ast_node *make_cmd_up(){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  return node;
}

struct ast_node *make_cmd_down(){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr, struct ast_node *expr2){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = expr;
  printf("Param : %s\n",expr->u.name);
  return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
  node->children_count = 1;
  node->children[0] = expr;
  node->u.value = expr->u.value;
  return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  return node;
}

struct ast_node *make_cmd_home(){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *expr2){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  return node;
}

struct ast_node *make_expr_binop(char op,struct ast_node *expr, struct ast_node *expr2){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BINOP;
  node->children_count = 2;
  node->children[0] = expr;
  node->u.op = op;
  return node;
}

struct ast_node *make_cmd_proc(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_PROC;
  node->children_count = 1;
  node->children[0] = expr;
  
  return node;
}

void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {

}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */

void ast_print_node(struct ast_node *self){
	switch(self->kind){
		case KIND_CMD_SIMPLE :
			switch(self->u.cmd){
				case CMD_BACKWARD :
					printf("Cmd : BACKWARD, value :%lf\n", self->u.value);
				break;
				case CMD_FORWARD :
					printf("Cmd : FORWARD, value :%lf\n", self->u.value);
				break;
				case CMD_HOME :
					printf("Cmd : HOME\n");
				break;      
				case CMD_UP :
					printf("Cmd : UP\n");
				break; 
				case CMD_DOWN :
					printf("Cmd : DOWN\n");
				break; 
				case CMD_RIGHT :
					printf("Cmd : RIGHT\n");
				break; 
				case CMD_LEFT :
					printf("Cmd : LEFT\n");
				break; 
				case CMD_HEADING :
					printf("Cmd HEADING\n");
				break; 
				case CMD_COLOR :
					printf("Cmd : COLOR\n");
				break; 
				case CMD_POSITION :
					printf("Cmd : POSITION\n");
				break; 
				case CMD_PRINT :
					printf("Cmd : PRINT");
				break;
			}
		break;
		case KIND_CMD_REPEAT :
			printf("Cmd : REPEAT\n");
		break;
		case KIND_CMD_BLOCK :
			printf("Cmd : BLOCK\n");
		break;
		case KIND_CMD_PROC :
			printf("Cmd : PROC\n");
		break;
		case KIND_CMD_CALL :
			printf("Cmd : CALL\n");
		break;
		case KIND_CMD_SET :
			printf("Cmd : SET\n");
		break;
		case KIND_EXPR_VALUE :
			printf("Expr : VALUE\n");
		break;
		case KIND_EXPR_FUNC :
			printf("Expr : FUNC\n");
		break;
		case KIND_EXPR_BLOCK :
			printf("Expr : BLOCK\n");
		break;
		case KIND_EXPR_NAME :
			printf("Expr : NAME\n");
		break;
		case KIND_EXPR_BINOP :
			printf("Expr : BINOP\n");
		break;
		case KIND_EXPR_UNOP :
			printf("Expr : UNOP\n");
		break;
	}
	
	for(size_t i = 0; i < self->children_count; i++){
		ast_print_node(self->children[i]);
	}
}

void ast_print(const struct ast *self) {
	ast_print_node(self->unit);
}




