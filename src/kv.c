#include <kv.h>
#include <string.h>
#include <stdlib.h>

#define TOMBSTONE 0x1


size_t hash(char *val, int capacity) {
    size_t hash = 0x13371337deadbeef;

    while(*val) {
        hash ^= *val;
        hash = hash << 8;
        hash += *val;

        val++;
    }

    return hash % capacity;
}

int kv_put(kv_t *db, char *key, char *value) {
    if (!db || !key || !value) return -1;

    size_t idx = hash(key, db->capacity);

    for (size_t i = 0; i < db->capacity - 1; i++) {
        size_t real_idx = (idx + i) % db->capacity;

        kv_entry_t *entry = &db->entries[real_idx];

        if (entry->key &&
            entry->key != (void*)TOMBSTONE &&
            !strcmp(entry->key, key)) {
                char *newval = strdup(value);
                if (!newval) return -1;
                entry->value = newval;
                
                return real_idx;    
            }

        if (!entry->key || entry->key == (void*)TOMBSTONE) {
            char *newval = strdup(value);
            char *newkey = strdup(key);
            if (!newval || !newkey) {
                free(newkey);
                free(newval);
                return -1;
            }
            entry->value = newval;
            entry->key = newkey;

            db->count++;
            return real_idx;
        }
    }

   return -2; 
}

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

