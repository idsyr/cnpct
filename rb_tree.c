#include "rb_tree.h"

typedef enum color {BLACK = 0, RED} color_t; 

typedef struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	color_t color;
	int val;
} node_t;


typedef struct rb_tree {
	node_t *nil;
	node_t *top;
} rb_tree_t;


static node_t* create_node(int val){
	node_t *node = malloc(sizeof(node_t));
	node->parent = NULL;
	node->left   = NULL;
	node->right  = NULL;
	node->color  = RED;
	node->val    = val;
	return node;
}


rb_tree_t *create_rb_tree(){
	rb_tree_t *rb_tree =  malloc(sizeof(rb_tree_t));
	rb_tree->nil = create_node(42);
	rb_tree->top = NULL;
	return rb_tree;
}


static void take_parent(rb_tree_t *tree, node_t *src_node, node_t *rcvd_node){
	if(src_node->parent == tree->nil) {
		tree->top = rcvd_node;
		tree->nil->left = rcvd_node;
		tree->nil->right = rcvd_node;
		rcvd_node->parent = tree->nil;}
	else if(src_node == src_node->parent->left)
		src_node->parent->left  = rcvd_node;
	else
		src_node->parent->right = rcvd_node;
	if(rcvd_node != NULL) rcvd_node->parent = src_node->parent;
}


static void set_right(node_t *src_node, node_t *rcvd_node){
	rcvd_node->right = src_node;
	if(src_node != NULL)
		rcvd_node->right->parent = rcvd_node;
}


static void set_left(node_t *src_node, node_t *rcvd_node){
	rcvd_node->left = src_node;
	if(src_node != NULL)
		rcvd_node->left->parent = rcvd_node;
}


static void left_rotate(rb_tree_t *tree, node_t *x){
	node_t *xr = x->right;
	if(x->parent == tree->nil) {tree->top = xr;}
	take_parent(tree, x, xr);
	set_right(xr->left, x);
	set_left(x, xr);
}


static void right_rotate(rb_tree_t *tree, node_t *x){
	node_t *xr = x->left;
	if(x->parent == tree->nil) tree->top = xr;
	take_parent(tree, x, xr);
	set_left(xr->right, x);
	set_right(x, xr);
}


static void rb_insert_fixup(rb_tree_t *tree, node_t *path_node){
	while(path_node->parent != NULL &&
				path_node->parent->parent != NULL &&
				path_node->parent->color == RED){
		if(path_node->parent == path_node->parent->parent->left){
			node_t *uncle = path_node->parent->parent->right;
			color_t uncle_color = (uncle == NULL)? BLACK : uncle->color;
			if(uncle_color == RED){
				path_node->parent->color = BLACK;
				uncle->color = BLACK;
				path_node->parent->parent->color = RED;
				path_node = path_node->parent->parent;
			} else {
				if(path_node == path_node->parent->right){
					path_node = path_node->parent;
					left_rotate(tree, path_node);}
				path_node->parent->color = BLACK;
				path_node->parent->parent->color = RED;
				right_rotate(tree, path_node->parent->parent);
			}	
		} else {
			node_t *uncle = path_node->parent->parent->left;
			color_t uncle_color = (uncle == NULL)? BLACK : uncle->color;
			if(uncle_color == RED){
				path_node->parent->color = BLACK;
				uncle->color = BLACK;
				path_node->parent->parent->color = RED;
				path_node = path_node->parent->parent;
			} else {
				if(path_node == path_node->parent->left){
					path_node = path_node->parent;
					right_rotate(tree, path_node);}
				path_node->parent->color = BLACK;
				path_node->parent->parent->color = RED;
				left_rotate(tree, path_node->parent->parent);
			}
		}
	}
}


void rb_insert(rb_tree_t *tree, int val){
	node_t *new_node = create_node(val);
	node_t *path_node = tree->top;

	if(tree->top == NULL) {
		new_node->color = BLACK;
		tree->top = new_node;
		tree->nil->left = new_node;
		tree->nil->right = new_node;
		new_node->parent = tree->nil;
		return;} 

	for(;;){
		if(path_node->val == val) {
			free(new_node);
			return;}

		if(path_node->val > val){
			if(path_node->left == NULL) {
				set_left(new_node, path_node);
				break;}
			path_node = path_node->left;
		}

		if(path_node->val < val){
			if(path_node->right == NULL) {
				set_right(new_node, path_node);
				break;}
			path_node = path_node->right;
		}
	}
	rb_insert_fixup(tree, new_node); 
}


static node_t* find_node(rb_tree_t *tree, int val){
	node_t *path_node = tree->top;
	while(path_node != NULL){
		if(path_node->val == val) return path_node;
		if(path_node->val > val) path_node = path_node->left;
		else                     path_node = path_node->right;
	}
	return NULL;
}


static node_t* rb_minimum(node_t *path_node){
	while(path_node->left != NULL)
		path_node = path_node->left;
	return path_node;
}


int rb_find(rb_tree_t *tree, int val){
	node_t *node = find_node(tree, val);
	return (node == NULL)? -1 : node->val;
}


static void delete_fixup(rb_tree_t *tree, node_t *path_node){
	while(path_node != tree->top && path_node->color == BLACK){
		if(path_node == path_node->parent->left){
			node_t *bro_node = path_node->parent->right;
			if(bro_node->color == RED){
				bro_node->color = BLACK;
				path_node->parent->color = RED;
				left_rotate(tree, path_node->parent);
				bro_node = path_node->parent->right;
			}
			if(bro_node->left->color == BLACK && bro_node->right->color == BLACK){
				bro_node->color = RED;
				path_node = path_node->parent;
			}
			else{
				if(bro_node->right->color == BLACK){
					bro_node->left->color = BLACK;
					bro_node->color = RED;
					right_rotate(tree, bro_node);
					bro_node = path_node->parent->right;
				}
				bro_node->color = path_node->parent->color;
				path_node->parent->color = BLACK;
				bro_node->right->color = BLACK;
				left_rotate(tree, path_node->parent);
				path_node = tree->top;
			}
		} else {
			node_t *bro_node = path_node->parent->left;
			if(bro_node->color == RED){
				bro_node->color = BLACK;
				path_node->parent->color = RED;
				right_rotate(tree, path_node->parent);
				bro_node = path_node->parent->left;
			}
			if(bro_node->right->color == BLACK && bro_node->left->color == BLACK){
				bro_node->color =  RED;
				path_node = path_node->parent;
			}
			else {
				if(bro_node->left->color == BLACK){
					bro_node->right->color = BLACK;
					bro_node->color = RED;
					left_rotate(tree, bro_node);
					bro_node = path_node->parent->left;
				}
				bro_node->color = path_node->parent->color;
				path_node->parent->color = BLACK;
				bro_node->left->color = BLACK;
				right_rotate(tree, path_node->parent);
				path_node = tree->top;
			}
		}
	} 	
	path_node->color = BLACK;
}


void rb_delete(rb_tree_t *tree, int val){	
	node_t *rm_node = find_node(tree, val);
	node_t *min_node;
	node_t *fixup_node;
	color_t fixup_color = rm_node->color;
	if(rm_node == NULL) return;

	if(rm_node->left == NULL){
		fixup_node = rm_node->right;
		take_parent(tree, rm_node, rm_node->right);}
	else if(rm_node->right == NULL){
		fixup_node = rm_node->left;
		take_parent(tree, rm_node, rm_node->left);}
	else {
		min_node = rb_minimum(rm_node->right);
		fixup_node = rm_node->right;
		fixup_color = min_node->color;
		if(min_node->parent != rm_node){
			take_parent(tree, min_node, min_node->right);
			set_right(rm_node->right, min_node);
		}
		take_parent(tree, rm_node, min_node);
		set_left(rm_node->left, min_node);
		min_node->color = rm_node->color;
	}
	free(rm_node);
	if(fixup_color == BLACK)
		delete_fixup(tree, fixup_node);
}


static void print_postorder(node_t* path_node){
	if(path_node == NULL) return;
	print_postorder(path_node->left);
	printf("%d ", path_node->val);
	print_postorder(path_node->right);
}


void rb_print_postorder(rb_tree_t *tree){
	node_t *path_node = tree->top;
	print_postorder(path_node);
	printf("\n");
}


// TODO: rbt_print_preorder()
// TODO: rbt_clean()
// TODO: rbt_print_graphic()


//     +---+
//     | p |   
//   +-|___|-+  
//   |       |  
// +---+   +---+
// | l |   | r |
// |___|   |___|
