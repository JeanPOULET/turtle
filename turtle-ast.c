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

struct ast_node *make_expr_name(char *name) {
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
	struct ast_node *colorR = calloc(1, sizeof(struct ast_node));
	struct ast_node *colorG = calloc(1, sizeof(struct ast_node));
	struct ast_node *colorB = calloc(1, sizeof(struct ast_node));
	colorR->kind = KIND_EXPR_VALUE;
	colorG->kind = KIND_EXPR_VALUE;
	colorB->kind = KIND_EXPR_VALUE;
	

	colorR->u.value = expr->r;
	colorG->u.value = expr->g;
	colorB->u.value = expr->b;
	

	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;
	node->children[0] = colorR;
	node->children[1] = colorG;
	node->children[2] = colorB;
	return node;
}

struct ast_node *make_cmd_color_triple(struct ast_node *expr, struct ast_node *expr2, struct ast_node *expr3){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));

	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;
	node->children[0] = expr;
	node->children[1] = expr2;
	node->children[2] = expr3;
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
		default : //white
			red = 1.0;
			green = 1.0;
			blue = 1.0;
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
	node->kind = KIND_CMD_REPEAT;
	node->children_count = 2;
	node->children[0] = expr;
	node->children[1] = expr2;
	return node;
}

struct ast_node *make_expr_binop(char op,struct ast_node *expr, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	
	node->kind = KIND_EXPR_BINOP;
	node->children_count = 2;
	node->children[0] = expr;
	node->children[1] = expr2;
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


struct ast_node *make_cmd_proc(char *name, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_PROC;
	node->children_count = 1;
	node->children[0] = expr2;
	node->u.name=name;
	return node;
}

struct ast_node *make_cmd_call(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_CALL;
	node->u.name = expr->u.name;
	return node;
}

struct ast_node *make_cmd_set(char *name, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SET;
	node->children_count = 1;
	node->children[0] = expr2;
	node->u.name = name;
	return node;
}

struct ast_node *make_cmd_block(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_BLOCK;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_sin(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SIN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_cos(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_COS;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_tan(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_TAN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_sqrt(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SQRT;
	node->children_count = 1;	
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_random(struct ast_node *expr,struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_RANDOM;
	node->children_count = 2;
	node->children[0] = expr;
	node->children[1] = expr2;
	return node;
}

struct ast_node *make_expr_block(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BLOCK;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

void ast_node_destroy(struct ast_node *self){
	if(self->next != NULL){
		ast_node_destroy(self->next);
	}

	for(int i=0;i<self->children_count;i++){
		if(self->children[i]!=NULL){
			ast_node_destroy(self->children[i]);
		}
	}

	if(self!=NULL){
		free(self);
	}
}

void ast_destroy(struct ast *self) {
	ast_node_destroy(self->unit);
	
	
}

void ctx_destroy(struct context *self){
	for(int i=0;i<self->currentFunc;i++){
		free(self->func_names[i].name);
	}
	for(int i=0;i<self->currentVar;i++){
		free(self->variables[i].name);
	}
	
	free(self->variables);
	free(self->func_names);
}

/*
* context
*/

void context_create(struct context *self) {
	self->angle = 0;
	self->x = 0;
	self->y = 0;
	self->up = false;
	self->color.r = 0.0;
	self->color.g = 0.0;
	self->color.b = 0.0;
	self->func_names = calloc(MAX_VARIABLES, sizeof(struct func));
	self->variables = calloc(MAX_VARIABLES, sizeof(struct var));

	char *_pi = "PI";
	self->variables[0].name = calloc(strlen(_pi)+1,sizeof(char));
	strcpy(self->variables[0].name,_pi);
	self->variables[0].value = PI;

	char *_SQRT2 = "SQRT2";
	self->variables[1].name = calloc(strlen(_SQRT2)+1,sizeof(char));
	strcpy(self->variables[1].name,_SQRT2);
	self->variables[1].value = SQRT2;

	char *_SQRT3 = "SQRT3";
	self->variables[2].name = calloc(strlen(_SQRT3)+1,sizeof(char));
	strcpy(self->variables[2].name,_SQRT3);
	self->variables[2].value = SQRT3;
	
	self->currentFunc=0;
	self->currentVar=3;
}

/*
* eval
*/

double ast_eval_node(const struct ast_node *self, struct context *ctx) {
	double x;
	double y;
	
	double value;
	double value2;
    struct ast_node *current;

	int nbRepeat;

	switch(self->kind){
		case KIND_CMD_SIMPLE :
			switch(self->u.cmd){
				case CMD_BACKWARD :
					x=0.0;
					y=0.0;
					value = ast_eval_node(self->children[0],ctx);
					x =  ctx->x + value*sin(ctx->angle*PI/180);
					y =  ctx->y + value*cos(ctx->angle*PI/180);
					ctx->x = x;
					ctx->y = y;
					if(ctx->up){
						printf("MoveTo %f %f \n",x,y);
					}else{
						printf("LineTo %f %f \n",x,y);
					}
					
				break;
				case CMD_FORWARD :
					x=0.0;
					y=0.0;
					
					value = ast_eval_node(self->children[0],ctx);
					x =  ctx->x - value*sin(ctx->angle*PI/180);
					y =  ctx->y - value*cos(ctx->angle*PI/180);
					ctx->x = x;
					ctx->y = y;
					if(ctx->up){
						printf("MoveTo %f %f \n",x,y);
					}else{
						printf("LineTo %f %f \n",x,y);
					}

				break;
				case CMD_HOME :
					ctx->up = false;
					ctx->x = 0.0;
					ctx->y = 0.0;
					ctx->color.r =0.0;
					ctx->color.g =0.0;
					ctx->color.b =0.0;
					ctx->angle = 0;
				break;      
				case CMD_UP :
					ctx->up = true;
				break; 
				case CMD_DOWN :
					ctx->up = false;
				break; 
				case CMD_RIGHT :
					value = ast_eval_node(self->children[0],ctx);
					ctx->angle -= value;
				break; 
				case CMD_LEFT :
					value = ast_eval_node(self->children[0],ctx);
					ctx->angle += value;
				break; 
				case CMD_HEADING :
					value = ast_eval_node(self->children[0],ctx);
					ctx->angle = -value;
				break; 
				case CMD_COLOR :
					printf("Color ");
					for(size_t i = 0; i < self->children_count; i++){
						value = ast_eval_node(self->children[i],ctx);
						printf(" %f",value);
					}
					printf("\n");
				break; 
				case CMD_POSITION :
					value  = ast_eval_node(self->children[0],ctx);
					value2 = ast_eval_node(self->children[1],ctx);
					if(ctx->up){
						printf("MoveTo %f %f \n",value,value2);
					}else{
						printf("LineTo %f %f \n",value,value2);
					}
					ctx->x = value;
					ctx->y = value2;
				break; 
				case CMD_PRINT :
					value =ast_eval_node(self->children[0],ctx);
					fprintf(stderr,"Print : %f\n",value);
					
				break;
			}
		break;
		case KIND_CMD_REPEAT :
			nbRepeat = ast_eval_node(self->children[0],ctx);
			for(size_t i=0;i<nbRepeat;++i){
				ast_eval_node(self->children[1],ctx);
			}
		break;
		case KIND_CMD_BLOCK :
			current = self->children[0];
			while(current != NULL){
				ast_eval_node(current,ctx);
				current = current->next;
			}
		break;
		case KIND_CMD_PROC :
			for(size_t i=0; i<ctx->currentFunc;i++){
				if(strcmp(ctx->func_names[i].name,self->u.name)==0){
					fprintf(stderr,"Erreur : fonction déjà crée\n");
					exit(EXIT_FAILURE);
				}
			}

			ctx->func_names[ctx->currentFunc].name = calloc(strlen(self->u.name),sizeof(char));
			strcpy(ctx->func_names[ctx->currentFunc].name, self->u.name);
			ctx->func_names[ctx->currentFunc].next = self->children[0];
			ctx->currentFunc++;
			
		break;
		case KIND_CMD_CALL :
			for(size_t i=0; i<ctx->currentFunc;i++){
				if(strcmp(ctx->func_names[i].name,self->u.name) ==0){
					ast_eval_node(ctx->func_names[i].next,ctx);
					return 0.0;
				}
			}
			fprintf(stderr,"Erreur : fonction non existante\n");
			exit(EXIT_FAILURE);

		break;
		case KIND_CMD_SET :
			for(size_t i=0; i<ctx->currentVar;i++){
				if(strcmp(ctx->variables[i].name,self->u.name)==0){
					fprintf(stderr,"Erreur : variable déjà crée\n");
					exit(EXIT_FAILURE);
				}
			}
			ctx->variables[ctx->currentVar].name = calloc(strlen(self->u.name),sizeof(char));
			strcpy(ctx->variables[ctx->currentVar].name, self->u.name);
			ctx->variables[ctx->currentVar].value = self->children[0]->u.value;
			ctx->currentVar++;

		break;
		case KIND_EXPR_FUNC :
			switch(self->u.func){
				case FUNC_SIN : 
					return sin(ast_eval_node(self->children[0],ctx));
				break;
				case FUNC_COS :
					return cos(ast_eval_node(self->children[0],ctx));
				break;
				case FUNC_TAN :
					return tan(ast_eval_node(self->children[0],ctx));
				case FUNC_SQRT :
					value =ast_eval_node(self->children[0],ctx);
					if(value<0.0){
						fprintf(stderr,"Erreur : nombre négatif dans une racine carrée\n");
						exit(EXIT_FAILURE);
					}
					return sqrt(value);
				break;
				case FUNC_RANDOM :
					
					value = ast_eval_node(self->children[0],ctx);  //borne inf
					value2 = ast_eval_node(self->children[1],ctx); //borne sup
					return rand()/(double)RAND_MAX*(value2-value);
				break;
			}
		break;
		case KIND_EXPR_BINOP :
			switch(self->u.op){
				case '+' :
					return (ast_eval_node(self->children[0],ctx) + ast_eval_node(self->children[1],ctx));
				break;
				case '-' : 
					return (ast_eval_node(self->children[0],ctx) - ast_eval_node(self->children[1],ctx));
				break;
				case '*' : 
					return (ast_eval_node(self->children[0],ctx) * ast_eval_node(self->children[1],ctx));
				break;
				case '/' : 
					return (ast_eval_node(self->children[0],ctx) / ast_eval_node(self->children[1],ctx));
				break;
				case '^' : 
					return (pow(ast_eval_node(self->children[0],ctx), ast_eval_node(self->children[1],ctx)));
				break;
			}
			
		break;
		case KIND_EXPR_UNOP :
			return -ast_eval_node(self->children[0],ctx);
		break;
		case KIND_EXPR_BLOCK :
			return ast_eval_node(self->children[0],ctx);
		break;
		case KIND_EXPR_NAME :
			for(size_t i=0; i<ctx->currentVar;i++){
				if(strcmp(ctx->variables[i].name,self->u.name)==0){
					return ctx->variables[i].value;
				}
			}
			fprintf(stderr,"Erreur : variable non existante\n");
			exit(EXIT_FAILURE);

		break;
		case KIND_EXPR_VALUE :
			return self->u.value;
		break;
	}
			
	return 0.0;
}

void ast_eval(const struct ast *self, struct context *ctx) {
	struct ast_node *current = self->unit;
	while(current !=NULL){
		ast_eval_node(current,ctx);
		current = current->next;	
	}
	
}

/*
* print
*/

void ast_print_node(struct ast_node *self){
	int nbRepeat;
	struct ast_node *current;
	switch(self->kind){
		case KIND_CMD_SIMPLE :
			switch(self->u.cmd){
				case CMD_BACKWARD :
					printf("BACKWARD");
					ast_print_node(self->children[0]);
					printf("\n");
				break;
				case CMD_FORWARD :
					printf("FORWARD");
					ast_print_node(self->children[0]);
					printf("\n");
				break;
				case CMD_HOME :
					printf("HOME\n");
				break;      
				case CMD_UP :
					printf("UP\n");
				break; 
				case CMD_DOWN :
					printf("DOWN\n");
				break; 
				case CMD_RIGHT :
					printf("RIGHT ");
					ast_print_node(self->children[0]);
					printf("\n");
				break; 
				case CMD_LEFT :
					printf("LEFT ");
					ast_print_node(self->children[0]);
					printf("\n");
				break; 
				case CMD_HEADING :
					printf("HEADING");
					ast_print_node(self->children[0]);
					printf("\n");
				break; 
				case CMD_COLOR :
					printf("COLOR");
					ast_print_node(self->children[0]);
					ast_print_node(self->children[1]);
					ast_print_node(self->children[2]);
					printf("\n");
				break; 
				case CMD_POSITION :
					printf("POSITION");
					ast_print_node(self->children[0]);
					ast_print_node(self->children[1]);
					printf("\n");
				break; 
				case CMD_PRINT :
					printf("PRINT : ");
					ast_print_node(self->children[0]);
					printf("\n");
				break;
			}
		break;
		case KIND_CMD_REPEAT :
			nbRepeat = self->children[0]->u.value;
			printf("Cmd : REPEAT(%d)\n\t",nbRepeat);
			
			for(size_t i=0;i<nbRepeat;++i){
				ast_print_node(self->children[1]);
			}
		break;
		case KIND_CMD_BLOCK :
			printf("\tCmd : BLOCK\n");
			current = self->children[0];
			while(current != NULL){
				printf("\t\t");
				ast_print_node(current);
				current = current->next;
			}

		break;
		case KIND_CMD_PROC :
			printf("Cmd : PROC : %s\n",self->u.name);
			ast_print_node(self->children[0]);
		break;
		case KIND_CMD_CALL :
			printf("Cmd : CALL : %s\n ",self->u.name);
		break;
		case KIND_CMD_SET :
			printf("Cmd : SET : %s\n",self->u.name);
		break;
		case KIND_EXPR_FUNC :
			switch(self->u.func){
				case FUNC_SIN : 
					printf("SIN(%f)",self->children[0]->u.value);
				break;
				case FUNC_COS :
					printf("COS(%f)\n",self->children[0]->u.value);
				break;
				case FUNC_TAN :
					printf("TAN(%f)\n",self->children[0]->u.value);
				case FUNC_SQRT :
					printf("SQRT(%f)\n",self->children[0]->u.value);
				break;
				case FUNC_RANDOM :
					printf("rand(%f,%f)\n",self->children[0]->u.value,self->children[1]->u.value);
				break;
			}
		break;
		case KIND_EXPR_BINOP :
			ast_print_node(self->children[0]);
			printf("%c",self->u.op);
			ast_print_node(self->children[1]);
		break;
		case KIND_EXPR_UNOP :
			ast_print_node(self->children[0]);
		break;
		case KIND_EXPR_BLOCK :
			printf(" (");
			ast_print_node(self->children[0]);
			printf(") ");
		break;
		case KIND_EXPR_NAME :
			printf(" %s ", self->u.name);
		break;
		case KIND_EXPR_VALUE :
			printf(" %f ", self->u.value);
		break;
	}

}

void ast_print(const struct ast *self){
	struct ast_node *current = self->unit;
	while(current !=NULL){
		ast_print_node(current);
		current = current->next;
	}
}




