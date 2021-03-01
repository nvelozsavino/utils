//
// Created by nico on 1/3/21.
//


#include "rb_bst.h"
#include <stdlib.h>


static bool is_red(node_t* node){
    if (node==NULL){
        return false;
    }
    return node->is_red;
}

static node_t* rotate_left(node_t* node){
    node_t* x = node->right;
    x->parent.parent=node->parent.parent;
    x->parent.is_left=node->parent.is_left;

    node->right = x->left;
    if (node->right!=NULL) {
        node->right->parent.parent = node->right;
        node->right->parent.is_left = false;
    }
    x->left=node;
    node->parent.parent=x;
    node->parent.is_left=true;
    x->is_red=node->is_red;
    node->is_red=true;
    return x;
}

node_t* rotate_right(node_t* node){
    node_t* x = node->left;
    x->parent.parent=node->parent.parent;
    node->left=x->right;
    if (node->left!=NULL) {
        node->left->parent.parent = node->left;
        node->left->parent.parent = true;
    }
    x->right=node;
    node->parent.parent=x;
    node->parent.is_left=false;
    x->is_red=node->is_red;
    node->is_red=true;
    return x;
}

void flip_colors(node_t* node){

    if (node->left!=NULL){
        node->left->is_red=!node->left->is_red;
    }
    if (node->right!=NULL){
        node->right->is_red=!node->right->is_red;
    }
    node->is_red=!node->is_red;

}


bool insert_no_recursive(node_t* root, const void* element, int (*cmp_func)(const void* a, const void* b), bool unique){
    node_t** node = &root;
    node_t* parent = root;
    bool parent_is_left=false;
    while (*node!=NULL){
        parent=*node;
        int cmp = cmp_func((*node)->value,element);
        if (cmp<=0){
            parent_is_left=true;
            node=&(*node)->left;
            continue;
        } else {
            node=&(*node)->right;
            continue;
        }
    }
    *node = malloc(sizeof(node_t));
    if ((*node)==NULL){
        return false;
    }
    (*node)->is_red=true;
    (*node)->left=NULL;
    (*node)->right=NULL;
    (*node)->value=element;
    (*node)->parent.parent=parent;
    (*node)->parent.is_left=parent_is_left;
    while (parent!=NULL){
        if (is_red(parent->right) && !is_red(parent->left)){
            parent= rotate_left(parent);
        }
        if (is_red(parent->left) && is_red(parent->left->left)){
            parent=rotate_right(parent);
        }
        if (is_red(parent->left) && is_red(parent->right)){
            flip_colors(parent);
        }
        parent = parent->parent.parent;
    }
    return true;

}

node_t* insert(node_t* parent, const void* element, int (*cmp_func)(const void* a, const void* b), bool unique,node_t* up_link,bool is_left){
    if (parent==NULL){
        node_t* node = malloc(sizeof(node_t));
        if (node==NULL){
            return NULL;
        }
        node->is_red=true;
        node->left=NULL;
        node->right=NULL;
        node->value=element;
        node->parent.parent=up_link;
        node->parent.is_left=is_left;
        return node;
    }
    int cmp = cmp_func(parent->value,element);
    if (unique && cmp==0){
        return parent;
    }
    if (cmp<=0){
        parent->left = insert(parent->left,element,cmp_func,unique,parent,true);
    } else if (cmp>0){
        parent->right = insert(parent->right,element,cmp_func,unique,parent,false);
    }
    if (is_red(parent->right) && !is_red(parent->left)){
        parent= rotate_left(parent);
    }
    if (is_red(parent->left) && is_red(parent->left->left)){
        parent=rotate_right(parent);
    }
    if (is_red(parent->left) && is_red(parent->right)){
        flip_colors(parent);
    }

    return parent;
}


int iterate(node_t* node, int next, void** arr, bool clean){
    if (node==NULL){
        return next;
    }
    next = iterate(node->left,next,arr,clean);
    const void* ptr = node->value;
    if (arr!=NULL){
        arr[next] = (void*)ptr;
    }
    next++;
    next = iterate(node->right,next,arr,clean);
    if (clean){
        free(node);
    }
    return next;
}

int iterate_no_recursion(node_t* root, void** arr, bool clean){
    int next=0;
    node_t *node=root;
    node_t* latest=NULL;
    while(node!=NULL){
        if (latest==NULL) {
            if (node->left == NULL) {
                if (arr != NULL) {
                    arr[next] = (void *) node->value;
                }
                next++;
            } else {
                node = node->left;
                continue;
            }
        } else {
            if (latest->parent.is_left){
                if (arr != NULL) {
                    arr[next] = (void *) node->value;
                }
                next++;
            } else {
                latest=node;
                node=node->parent.parent;
                continue;
            }
        }

        if (node->right==NULL) {
            latest=node;
            node=node->parent.parent;
        } else {
            node=node->right;
            latest=NULL;
        }

    }

}


