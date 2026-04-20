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
    kv_put(db, "lala", "baba");

    for (size_t i = 0; i < db->capacity; i++) {
        if (db->entries[i].key) {
            printf("[%zu] %s: %s\n", 
            i,
            db->entries[i].key, 
            db->entries[i].value);
        }
    }

    char *val = kv_get(db, "hehe");
    char *val2 = kv_get(db, "lala");
    char *val3 = kv_get(db, "this doesn't exist");

    printf("%s %s %s\n",
       val ? val : "(null)",
       val2 ? val2 : "(null)",
       val3 ? val3 : "(null)");

    kv_free(db);
    
    printf("All tests passed!\n");

    return 0;
}
