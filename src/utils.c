#include "../include/utils.h"

int scan_bool(bool* boolean) {
    char *tmp = malloc(2*sizeof(char));
    scanf("%s", tmp);
    if (*tmp == 'y') {
        free(tmp);
        *boolean = true;
        return 0;
    }
    else {
        if (*tmp == 'n') { 
        free(tmp);
        *boolean = false;
        return 0;
        }
        else{
            free(tmp);
            return -1;
        }
    }
}

int read_storage_info(Storage* storage) {
    if (storage == NULL) {
        return -1;
    }

    printf("%s", "Enter serial number: ");
    char* input = malloc(15*sizeof(char));
    scanf("%s", input);
    storage->number = strtoul(input, NULL, 10);
    printf("%s%zu\n", "serial number is: ", storage->number);
    free(input);

    printf("%s", "Enter the type of storage: ");
    scanf("%s", storage->type);
    printf("%s%s\n", "type is: ", storage->type);

    printf("%s", "Enter the capacity: ");
    char* input2 = malloc(15*sizeof(char));
    scanf("%s", input2);
    storage->capacity = strtoul(input2, NULL, 10);
    printf("%s%zu\n", "capacity is: ", storage->capacity);
    free(input2);

    printf("%s", "Is the storage re-recordable (y/n): ");
    if (scan_bool(&storage->re_recordable) != 0){
        return -1;
    }
    printf("%s%d\n", "rrcdbl is: ", storage->re_recordable);

    return 0;
}

Storage *create_storage() {
    Storage *storage = calloc(1, sizeof(Storage));
    if (storage == NULL) {
        return NULL;
    }
    storage->type = calloc(10, sizeof(char)); // ne zabit'
    if (storage->type == NULL) {
        free(storage);
        return NULL;
    }

    if(read_storage_info(storage) != 0){
        free(storage->type);
        free(storage);
        return NULL;
    };
    return storage;
}

int delete_storage(Storage *storage) {
    if (storage == NULL) {
        return -1;
    }
    free(storage->type);
    free(storage);
    return 0;
}

Storages *create_array_of_storages() {
    Storages *array_of_storages = calloc(1, sizeof(Storages));
    if (array_of_storages == NULL) {
        return NULL;
    }
    array_of_storages->buffer = calloc(STARTING_BUFFER_SIZE, sizeof(Storage));
    if (array_of_storages->buffer == NULL) {
        free(array_of_storages);
        return NULL;
    }

    array_of_storages->number_of_cells = STARTING_BUFFER_SIZE;
    array_of_storages->number_of_storages = 0;
    return array_of_storages;
}

int delete_array_of_storages(Storages *array_of_storages) {
    if (array_of_storages == NULL) {
        return -1;
    }
    if (array_of_storages->buffer == NULL) {
        free(array_of_storages);
        return 0;
    }
    for (size_t i = 0; i < array_of_storages->number_of_storages; i++){
        free(array_of_storages->buffer[i].type);
    }
    free(array_of_storages->buffer);
    free(array_of_storages);
    return 0;
}

int increase_array (Storages *array_of_storages) {
    if (array_of_storages == NULL) {
        return -1;
    }

    array_of_storages->buffer = realloc(array_of_storages->buffer, array_of_storages->number_of_cells * BUFFER_INCREASE_COEFF);
    if (array_of_storages->buffer == NULL) {
        return -1;
    }

    array_of_storages->number_of_cells *= BUFFER_INCREASE_COEFF;
    return 0;
}

int add_storage_to_array(Storage* storage, Storages* array_of_storages) {
    if (storage == NULL || array_of_storages == NULL) {
        return -1;
    }

    if (array_of_storages->number_of_cells == array_of_storages->number_of_storages) {
        increase_array(array_of_storages);
    }

    array_of_storages->buffer[array_of_storages->number_of_storages] = *storage;
    free(storage);
    array_of_storages->number_of_storages++;
    return 0;
}
