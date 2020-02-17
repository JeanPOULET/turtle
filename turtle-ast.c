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
	#define MAX_VARIABLES 256

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
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_FORWARD;
	node->children_count = 1;
	node->children[0] = expr;
	
	return node;
	}

	struct ast_node *make_cmd_backward(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
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
	return node;
	}

	struct ast_node *make_cmd_color(struct rgb *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	return node;
	}

	struct ast_node *make_cmd_color_triple(double r, double g, double b){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));

	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	return node;
	}

	struct rgb *make_color_value(int num_color){
		struct rgb *color = calloc(1, sizeof(struct rgb));
		double red;
		double green;
		double blue;
		switch(num_color){
			case 0 : //red
				red = 1.0;
				green = 0.0;
				blue = 0.0;
			break;
		case 1 : //green
				red = 0.0;
				green = 1.0;
				blue = 0.0;
			break;
		case 2 : //blue
				red = 0.0;
				green = 0.0;
				blue = 1.0;
			break;
		case 3 : //cyan
				red = 0.0;
				green = 1.0;
				blue = 1.0;
			break;
		case 4 : //yellow
				red = 1.0;
				green = 0.0;
				blue = 1.0;
			break;
		case 5 : //magenta
				red = 1.0;
				green = 1.0;
				blue = 0.0;
			break;
		case 6 : //black
				red = 0.0;
				green = 0.0;
				blue = 0.0;
			break;
		case 7 : //gray
				red = 0.5;
				green = 0.5;
				blue = 0.5;
			break;
		case 8 : //white
				red = 1.0;
				green = 1.0;
				blue = 1.0;
			break;
		default:
				red = -666;
				green = -666;
				blue = -666;
		break;

		}
		color->r = red;
		color->g = green;
		color->b = blue;
		return color;
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

	struct ast_node *make_expr_unop(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_UNOP;
	node->children_count =1;
	node->children[0] = expr;
	return node;
	}

	struct ast_node *make_cmd_proc(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_PROC;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
	}

	struct ast_node *make_cmd_call(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_CALL;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
	}

	struct ast_node *make_cmd_set(struct ast_node *expr, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SET;
	node->children_count = 2;
	node->children[0] = expr;
	node->children[1] = expr2;
	return node;
	}

	void ast_destroy(struct ast *self) {

	}

	/*
	* context
	*/

	void context_create(struct context *self) {
	self->angle = 0;
	self->x = 0;
	self->y = 0;
	self->up = false;
	}

	/*
	* eval
	*/

	void ast_eval_node(const struct ast_node *self, struct context *ctx) {
		

	}

	void ast_eval(const struct ast *self, struct context *ctx) {
		ast_eval_node(self->unit,ctx);	
	}

	/*
	* print
	*/

	void ast_print_node(struct ast_node *self){
		switch(self->kind){
			case KIND_CMD_SIMPLE :
				switch(self->u.cmd){
					case CMD_BACKWARD :
						printf("Cmd : BACKWARD\n");
					break;
					case CMD_FORWARD :
						printf("Cmd : FORWARD\n");
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
						printf("Cmd : LEFT \n");
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
			case KIND_EXPR_FUNC :
				printf("Expr : FUNC\n");
			break;
			case KIND_EXPR_VALUE:
				printf("Expr : VALUE - %lf\n", self->u.value);
			break;
			case KIND_EXPR_NAME :
				printf("Expr : NAME - %s\n", self->u.name);
			break;
			case KIND_EXPR_BINOP :
				printf("Expr : BINOP\n");
			break;
			case KIND_EXPR_UNOP :
				printf("Expr : UNOP\n");
			break;
			case KIND_EXPR_BLOCK :
				printf("Expr : BLOCK\n");
			break;
		}
		
		for(size_t i = 0; i < self->children_count; i++){
			if(self->next != NULL){
				ast_print_node(self->next);
			}
		}
	}

	void ast_print(const struct ast *self){
		printf("%ld\n", self->unit->children_count);
		ast_print_node(self->unit);

	}




