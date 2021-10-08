#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define STARTING_BUFFER_SIZE 3
#define BUFFER_INCREASE_COEFF 2

typedef struct Storage {
    size_t number;
    char *type;
    size_t capacity;
    _Bool re_recordable;
} Storage;

typedef struct ArrayOfStorages {
    Storage *buffer;
    size_t number_of_storages;
    size_t number_of_cells;
} Storages;

Storage *create_storage();
Storages *create_array_of_storages();

int add_storage_to_array(Storage *storage, Storages *array_of_storages);
int increase_array(Storages *array_of_storages);

int delete_storage(Storage *storage);
int delete_array_of_storages(Storages *array_of_storages);

int read_storage_info(Storage* storage);
int scan_bool(bool* boolean);

#endif //  PROJECT_INCLUDE_UTILS_H_