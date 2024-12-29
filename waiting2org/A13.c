#ifdef RVRS_LIST_RNG

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int val;
} node_t;

node_t* reverse(node_t* node_1){
    node_t* node_2 = node_1->next;
    if(node_2 == NULL) return node_1;
    node_t* node_3 = node_2->next;
    node_1->next = NULL;
    while(1){
        node_2->next = node_1;
        node_1 = node_2;
        node_2 = node_3;
        if(node_3 == NULL) break;
        node_3 = node_3->next;
    }
    return node_2;
}

static void goto_pos(node_t** node_ptr, int pos){
    node_t* node = *node_ptr;
    for(int i = 0; i<pos; ++i)
        node = node->next;
    *node_ptr = node;
}

/**
  *
  *    
* *     |_______|_______|_______|_______|_______|
 */

node_t* rvrse_list_rng(node_t* node_1, 
                         int pos_1, 
                         int pos_2){
    node_t 
        *start_node,
        *node_0,
        *node_2,
        *node_3,
        *node_4;
    
    start_node = node_1;
    if(start_node->next == NULL) return start_node;

    if(pos_1-1 >= 0) {
        goto_pos(&node_1, pos_1-1);
        node_0 = node_1;
        node_1 = node_1->next;
    }

    node_4 = node_1;
    node_2 = node_1->next;
    node_3 = node_2->next;

    for(int i = pos_1; i<pos_2; ++i){
        node_2->next = node_1;
        node_1 = node_2;
        node_2 = node_3;
        if(node_3 == NULL) {break;}
        node_3 = node_3->next;
    }

    node_4->next = node_2;
    if(pos_1-1<0) return node_1;

    node_0->next = node_1;
    return start_node;
}

void print_list(const node_t* node){
    while(node != NULL){
    //for(int i = 0; i<20; ++i){
        printf("%d", node->val);
        node = node->next;
    }
    printf("\n");
}

int main(){
    node_t node_1; node_1.val = 1;
    node_t node_2; node_2.val = 2;
    node_t node_3; node_3.val = 3;
    node_t node_4; node_4.val = 4;
    node_t node_5; node_5.val = 5;
    node_t node_6; node_6.val = 6;
    node_t node_7; node_7.val = 7;
    node_t node_8; node_8.val = 8;
    node_t node_9; node_9.val = 9;
    node_1.next = &node_2;
    node_2.next = &node_3;
    node_3.next = &node_4;
    node_4.next = &node_5;
    node_5.next = &node_6;
    node_6.next = &node_7;
    node_7.next = &node_8;
    node_8.next = &node_9;
    node_9.next = NULL;

    //node_t* top = calloc(1, sizeof(node_t)); 
    
    //node_t* new_start = reverse(&node_1);
    //print_list(new_start);
    const node_t* new_st = rvrse_list_rng(&node_1, 1, 4);
    print_list(new_st);
}
#endif






//floyd algo
// алгоритм Брента

#ifdef P_AL

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    struct node* next;
    int val;
} node_t;

node_t* algo_p_al(FILE* file_ptr){
    node_t* node_start, *node_end, *node_rm;

    node_t* node = calloc(1, sizeof(node_t));
    node_start = node;
    node_end = node;

    for(;;){
        int res, num;

        res = fscanf(file_ptr, "%d", &num);
        fprintf(stdout, "%d", num);
        if(res == EOF) break;
        if(res != 1){
            fprintf(stderr,
                    "ERROR: file bad format");
        }

        node_t* new_node = calloc(1, sizeof(node_t));
        new_node->val = num;
        if(num % 2 == 1){
            new_node->next = node_start;
            if(new_node->next == node)
                node_rm = new_node;
            node_start = new_node;
        } else {
            node_end->next = new_node;
            node_end = new_node; 
        }
    }
    printf("\n");
    node_t* tmp = node_rm->next;
    node_rm->next = node_rm->next->next;
    free(tmp);

    return node_start;
}

void print_list(const node_t* node){
    while( node != NULL ){
        fprintf(stdout, "%d", node->val);
        node = node->next;
    }

}

int main(){
    node_t* res;
    FILE* file_ptr = fopen("input_p_al.dat", "r");
    if(!file_ptr){
        perror("ERROR: opening file");
        abort();
    }
    res = algo_p_al(file_ptr);
    print_list(res);
}

#endif

// skip - p_al and rvrse ok(?)
