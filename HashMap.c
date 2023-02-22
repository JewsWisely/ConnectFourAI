#include "HashMap.h"

/**

    initialize the elements of the supplied hmap

**/
void createHashMap(HashMap* hmap, int n_elems){

    hmap->n_elems = n_elems;
    hmap->entries = calloc(n_elems, sizeof(HashEntry*));
    hmap->size = 0;

}

/**

    if hmap has no entry with given key, add it in,
    use linear probing to handle collisions,
    return the load factor of hmap

**/
float hashAdd(HashMap* hmap, HashEntry* entry){

    if(hmap->size > hmap->n_elems){
        printf("critical error: hmap->size > hmap->n_elems");
        return -1;
    }
    else if(hmap->size == hmap->n_elems){
        printf("can not add error: hmap is full");
        return 1.0f;
    }

    if(hmap->entries[entry->key % hmap->n_elems] == NULL){
        hmap->entries[entry->key % hmap->n_elems] = entry;
    }
    else{
        for(int i = 0; i < hmap->n_elems; i++){
            HashEntry* thing = hmap->entries[(entry->key + i) % hmap->n_elems];
            if(thing != NULL){
                if(thing->key == entry->key){
                    //duplicate key is a problem, return without adding entry
                    return ((float)++hmap->size) / hmap->n_elems;
                }
            }
            else{
                hmap->entries[(entry->key + i) % hmap->n_elems] = entry;
                break;
            }
        }
    }
    return ((float)++hmap->size) / hmap->n_elems;

}


/**

    return pointer to value of entry for given key,
    or NULL if entry with given key isn't found

**/
void* hashGet(HashMap* hmap, Key key){

    for(int i = 0; i < hmap->n_elems; i++){
        if(hmap->entries[(key + i) % hmap->n_elems] != NULL){
            return hmap->entries[(key + i) % hmap->n_elems]->value;
        }
    }
    return NULL;

}

/**

    free all dynamic memory in the hmap and
    reset all of its other fields

**/
void destroyHashMap(HashMap* hmap){

    //printf("\ndestroying hash map...");
    for(int i = 0; i < hmap->n_elems; i++){
        if(hmap->entries[i] != NULL){
            free(hmap->entries[i]->value);
            free(hmap->entries[i]);
        }
    }
    free(hmap->entries);

    hmap->n_elems = 0;
    hmap->size = 0;
    //printf(" Success!\n");
}

void printEntry(HashEntry* entry){

    printf("{key: %d, value: %p}\n", entry->key, entry->value);

}
