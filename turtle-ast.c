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

struct ast_node *make_cmd_forward(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  node->u.value = expr->u.value;
  return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  node->u.value = expr->u.value;
  return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  node->u.value = expr->u.value;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  node->u.value = expr->u.value;
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
  node->u.value = expr->u.value;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr){
  printf("Param : %s",expr->u.name);
  
}

struct ast_node *make_cmd_color(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
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

void ast_print(const struct ast *self) {

}
