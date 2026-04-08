#include <assert.h>
#include <stdio.h>
#include <kv.h>

int main(void) {
    kv_t *db = kv_init(16);
    
    assert(db != NULL);
    assert(db->capacity == 16);
    assert(db->count == 0);
    assert(db->entries != NULL);

    kv_free(db);
    
    printf("All tests passed!\n");

    return 0;
}
