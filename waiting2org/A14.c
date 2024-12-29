// Cемианр 4.2. Обходы деревьев

typedef struct node{
    struct node *parent;
    struct node *left;
    struct node *right;
    void *data;
} node_t;


// postorder LRV удаление
// inorder   LVR проекция
// preorder  VLR топологический порядок

void inter_preorder(node_t* root){
    stacknode* s = NULL;
    stack_push(&s, root);
    while(!empty(s)){
        //pop
        //print
        //push l
        //push r
    }
}

void push(struct stacknode **stack, 
          struct node *data){
    struct stacknode *tmp = 
        calloc(1, sizeof(struct stacknode));
    tmp->data = data; 
    tmp->next = *stack;
    *stack = tmp;
}

struct treenode* pop(struct stacknode** top){
    treenode* tmp = *top->val;
    stacknode* for_rm = *top;
    *top = *top->next;
    free(for_rm);
    return tmp;
} 

//22.21

// сортированность inorder обхода - инвариант поисковости

//42:53
