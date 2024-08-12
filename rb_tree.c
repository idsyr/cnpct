#include <stdlib.h>

typedef enum color {BLACK = 0, RED} color_t; 


typedef struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	color_t color;
	int val;
} node_t;


typedef struct rb_tree {
	node_t *top;
} rb_tree_t;


static void left_rotate(node_t *x){
	node_t *y = x->right;
	node_t *parent = x->parent;
	if(parent->left == x) parent->left  = y;
	else                  parent->right = y;
	x->right = y->left;
	y->left  = x;
}


static void right_rotate(node_t *y){
	node_t *x = y->left;
	node_t *parent = y->parent;
	if(parent->left == y) parent->left  = x;
	else                  parent->right = x;
	y->left  = x->right;
	x->right = y;
}


node_t* create_node(int val){
	node_t *node = malloc(sizeof(node_t));
	node->parent = NULL;
	node->left   = NULL;
	node->right  = NULL;
	node->color  = RED;
	node->val    = val;
	return node;
}


static void rb_insert_fixup(rb_tree_t *tree, node_t *path_node){
	while(path_node->parent->color == RED){
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
					left_rotate(path_node);}
				path_node->parent->color = BLACK;
				path_node->parent->parent->color = RED;
				right_rotate(path_node->parent->parent);
			}	
		} else {
			// TODO: right version
		}
	}
}


void rb_insert(rb_tree_t *tree, int val){
	node_t *new_node = create_node(val);
	node_t *path_node = tree->top;

	if(tree->top == NULL) {
		new_node->color = BLACK;
		tree->top = new_node;
		return;} 

	for(;;){
		if(path_node->val == val) {
			free(new_node);
			return;}

		if(path_node->val < val){
			if(path_node->left == NULL) {
				path_node->left = new_node;
				new_node->parent = path_node;
				break;}
			path_node = path_node->left;
		}

		if(path_node->val > val){
			if(path_node->right == NULL) {
				path_node->right = new_node;
				new_node->parent = path_node;
				break;}
			path_node = path_node->right;
		}
	}
	if(new_node->parent != tree->top) rb_insert_fixup(tree, new_node); 
}


static node_t* find_node(rb_tree_t *tree, int val){
	node_t *path_node = tree->top;
	while(path_node != NULL){
		if(path_node->val == val) return path_node;
		if(path_node->val < val)
			path_node = path_node->left;
		else
			path_node = path_node->right;
	}
	return NULL;
}


static void rb_reconnect_parent(rb_tree_t *tree, node_t *src_node, node_t *new_node){
	if(src_node->parent == NULL)
		tree->top = new_node;
	else if(src_node == src_node->parent->left) // left node for parent
		src_node->parent->left = new_node;
	else                                        // right node for parent
		src_node->parent->right = new_node;
	new_node->parent = src_node->parent;
}


static void rb_reconnect_right(node_t *src_node, node_t *new_node){
	new_node->right = src_node->right;
	new_node->right->parent = new_node;
}


static void rb_reconnect_left(node_t *src_node, node_t *new_node){
	new_node->left = src_node->left;
	new_node->left->parent = new_node;
}


static node_t* rb_minimum(node_t *path_node){
	while(path_node->left != NULL){
		path_node = path_node->left;}
	return path_node;
}


static void delete_fixup(rb_tree_t *tree, node_t *path_node){
	while(path_node != tree->top && path_node->color == BLACK){
		if(path_node == path_node->parent->left){
			node_t *bro_node = path_node->parent->right;
			if(bro_node->color == RED){
				bro_node->color = BLACK;
				path_node->parent->color = RED;
				left_rotate(path_node->parent);
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
					right_rotate(bro_node);
					bro_node = path_node->parent->right;
				}
				bro_node->color = path_node->parent->color;
				path_node->parent->color = BLACK;
				bro_node->right->color = BLACK;
				left_rotate(path_node->parent);
				path_node = tree->top;
			}
		} else {
			// TODO: right version
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
		rb_reconnect_parent(tree, rm_node, rm_node->right);}
	else if(rm_node->right == NULL){
		fixup_node = rm_node->left;
		rb_reconnect_parent(tree, rm_node, rm_node->left);}
	else {
		min_node = rb_minimum(rm_node->right);
		fixup_node = rm_node->right;
		fixup_color = min_node->color;
		if(min_node->parent != rm_node){
			rb_reconnect_parent(tree, min_node, min_node->right);
			rb_reconnect_right(rm_node, min_node);
		} 
		rb_reconnect_parent(tree, rm_node, min_node);
		rb_reconnect_left(rm_node, min_node);
		min_node->color = rm_node->color;
	}
	free(rm_node);
	if(fixup_color == BLACK)
		delete_fixup(tree, fixup_node);
}


//     +---+
//     | p |   
//   +-|___|-+  
//   |       |  
// +---+   +---+
// | l |   | r |
// |___|   |___|
