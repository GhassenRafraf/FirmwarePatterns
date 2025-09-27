// Memory efficient hash table implementation
// for real time data lookup

#include <stdint.h>
#include <stdbool.h>

#define HASH_SIZE 32

typedef struct {
    uint8_t key;
    uint8_t value;
    bool occupied;
} hash_entry_t;

typedef struct {
    hash_entry_t entries[HASH_SIZE];
} hash_table_t;

uint32_t hash(uint8_t key) {
    return key % HASH_SIZE;
}

bool hash_insert(hash_table_t *table, uint8_t key, uint8_t value) {
    uint32_t index = hash(key);
    uint32_t start = index;
    do {
        if (!table->entries[index].occupied) {
            table->entries[index].key = key;
            table->entries[index].value = value;
            table->entries[index].occupied = true;
            return true;
        }
        index = (index + 1) % HASH_SIZE;
    } while (index != start);
    return false;
}

bool hash_lookup(hash_table_t *table, uint8_t key, uint8_t *value) {
    uint32_t index = hash(key);
    uint32_t start = index;
    do {
        if (table->entries[index].occupied && table->entries[index].key == key) {
            *value = table->entries[index].value;
            return true;
        }
        index = (index + 1) % HASH_SIZE;
    } while (index != start && table->entries[index].occupied);
    return false;
}