#include <kv.h>

kv_t *kv_init(size_t capacity) {
    if (capacity == 0) return NULL;

    kv_t *db = malloc(sizeof(kv_t));
    if (db == NULL) {
        return NULL;
    }

    db->capacity = capacity;
    db->count = 0;

    db->entries = calloc(capacity, sizeof(kv_entry_t));
    if (db->entries == NULL) {
        free(db);
        return NULL;
    }

    return db;
}

void kv_free(kv_t *db) {
    if (db == NULL) return;

    for (size_t i = 0; i < db->capacity; i++) {
        free(db->entries[i].key);
        free(db->entries[i].value);
    }

    free(db->entries);
    free(db);
}

