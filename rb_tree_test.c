#include <stdlib.h>
#include <stdio.h>
#include "rb_tree.h"

int main(void){
	setbuf(stdout, NULL);
	struct rb_tree *tree = create_rb_tree();
	
	for(int i = 0; i<15; i+=1)
		rb_insert(tree, i);
		
	rb_print_postorder(tree);
	rb_delete(tree, 7);
	rb_print_postorder(tree);

	//[ids@archlinux cnpct]$ gcc rb_tree.c rb_tree_test.c -o rb_tree_test.e -g
	//[ids@archlinux cnpct]$ ./rb_tree_test.e
	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
	//0 1 2 3 4 5 6 8 9 10 11 12 13 14 
}
