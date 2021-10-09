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

#define STARTING_BUFFER_SIZE 2
#define BUFFER_INCREASE_COEFF 2

typedef struct Storage {
    size_t number;
    char *type;
    size_t capacity;
    bool re_recordable;
} Storage;

typedef struct ArrayOfStorages {
    Storage *buffer;
    size_t number_of_storages;
    size_t number_of_cells;
} Storages;

Storage *create_storage(size_t number, char *type, size_t capacity, bool re_recordable);

Storage *create_storage_from_terminal();

Storages *create_array_of_storages();

int add_storage_to_array(Storage *storage, Storages *array_of_storages);

int increase_array(Storages *array_of_storages);

int delete_storage(Storage *storage);

int delete_array_of_storages(Storages *array_of_storages);

int read_storage_info(Storage *storage);

int scan_bool(bool *boolean);

int display_suitable(size_t required_capacity, Storages *storages);
int display_suitable(size_t required_capacity, Storages *storages);

#if defined(__cplusplus)
}
#endif

#endif  //  INCLUDE_UTILS_H_
