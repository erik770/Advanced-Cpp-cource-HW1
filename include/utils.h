#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 15
#define TYPE_SIZE 10
#define STARTING_BUFFER_SIZE 2
#define BUFFER_INCREASE_COEFF 2

typedef struct storage {
    size_t number;
    size_t capacity;
    char *type;
    bool re_recordable;
} storage_t;

typedef struct storages {
    storage_t *buffer;
    size_t number_of_storages;
    size_t number_of_cells;
} storages_t;

storage_t *create_storage(size_t number, const char *type, size_t capacity, bool re_recordable);

storage_t *create_storage_from_terminal();

storages_t *create_array_of_storages();

int add_storage_to_array(storage_t *storage, storages_t *array_of_storages);

int increase_array(storages_t *array_of_storages);

int delete_storage(storage_t *storage);

int delete_array_of_storages(storages_t *array_of_storages);

int read_storage_info(storage_t *storage);

int scan_bool(bool *boolean);

int display_suitable(size_t required_capacity, const storages_t *storages);

#if defined(__cplusplus)
}
#endif

#endif  //  INCLUDE_UTILS_H_
