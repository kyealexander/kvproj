#include <assert.h>
#include <stdio.h>

#include "kv.h"

int main(void) {
    kv_t *db = kv_init(1024);
    
    assert(db != NULL);
    assert(db->capacity == 1024);
    assert(db->count == 0);
    assert(db->entries != NULL);

    kv_put(db, "hehe", "haha");
    kv_put(db, "hehe", "hoho");
    kv_put(db, "lala", "hoho");

    for (size_t i = 0; i < db->capacity; i++) {
        if (db->entries[i].key) {
            printf("[%zu] %s: %s\n", 
            i,
            db->entries[i].key, 
            db->entries[i].value);
        }
    }

    kv_free(db);
    
    printf("All tests passed!\n");

    return 0;
}
