#include <stdio.h>
#include <stdlib.h>
#include "ordered_list.h"

t_ordered_list* create_ordered_list(int max){
    t_ordered_list* list = malloc(sizeof(t_ordered_list));
    list->items = malloc(sizeof(int) * max);
    list->n = 0;   
    list->max = max; 
    return list;
}


int size(t_ordered_list* list){
    return list->n;
}

int is_empty(t_ordered_list* list){
    return size(list) == 0 ? 1 : 0;
}

int is_full(t_ordered_list* list){
    return size(list) == list->max ? 1 : 0;
}

void destroy(t_ordered_list* list){
    free(list->items);
    free(list);
}

void clear(t_ordered_list* list){
    list->n = 0;
}

int insert(t_ordered_list* list, int value){
    if (is_full(list)) {
        list->max *= 2;
        list->items = (int*) realloc(list->items, list->max * sizeof(int));
    }

    if (is_empty(list)) {
        list->items[list->n++] = value;
        return 1;
    }

    int i = size(list) - 1;

    while (i >= 0 && list->items[i] > value) {
        list->items[i + 1] = list->items[i];
        i--;
    }

    list->items[i + 1] = value;
    list->n++;

    return 1;
}

int search(t_ordered_list* list, int value){
    int left = 0, right = size(list) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; 

        if (list->items[mid] == value)
            return mid;

        if (list->items[mid] < value)
            left = mid + 1; 
        else
            right = mid - 1; 
    }

    return -1; 
}

void print_ordered_list(t_ordered_list* list){
    if(is_empty(list)){
        printf("A lista se encontra vazia\n");
    }
    printf("Tamanho da lista: %d\n", size(list));
    for(int i = 0; i < size(list); i++){
        printf("Indice %d: %d\n", i, list->items[i]);
    }
}

int remove_by_index(t_ordered_list* list, int index){
    if(index >= size(list) || is_empty(list)){
        return 0;
    }
    for(int i = index; i < size(list); i++){
        list->items[i] = list->items[i+1];
    }
    list->n--;
    return 1;
}
int remove_by_value(t_ordered_list* list, int value){
    int index = search(list, value);
    if(index == -1){
        return 0;
    }
    int remove = remove_by_index(list, index);
    return remove;
}
int remove_end(t_ordered_list* list){
    if(is_empty(list)){
        return 0;
    }
    list->n--;
    return 1;
}

t_ordered_list* merge(t_ordered_list* l1, t_ordered_list* l2) {
    if (is_empty(l1) && is_empty(l2)) {
        return create_ordered_list(0);
    }
    if (is_empty(l1)) return l2;
    if (is_empty(l2)) return l1;

    int total_size = size(l1) + size(l2);
    t_ordered_list* merged_list = create_ordered_list(total_size);

    int i = 0, j = 0;

    while (i < size(l1) || j < size(l2)) {
        if (i < size(l1) && (j >= size(l2) || l1->items[i] < l2->items[j])) {
            insert(merged_list, l1->items[i]);
            i++;
        }
        else if (j < size(l2)) {
            insert(merged_list, l2->items[j]);
            j++;
        }
    }

    return merged_list;
}


