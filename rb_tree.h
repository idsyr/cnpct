#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdlib.h>
#include <stdio.h>

struct rb_tree;
struct rb_tree* create_rb_tree();
void rb_insert(struct rb_tree *tree, int val);
void rb_delete(struct rb_tree *tree, int val);
int rb_find(struct rb_tree *tree, int val);
void rb_print_postorder(struct rb_tree *tree);


#endif 
