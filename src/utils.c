#include "../include/utils.h"

int scan_bool(bool *boolean) {
    char *tmp = malloc(2 * sizeof(char));
    scanf("%2s", tmp);
    if (*tmp == 'y') {
        free(tmp);
        *boolean = true;
        return 0;
    } else {
        if (*tmp == 'n') {
            free(tmp);
            *boolean = false;
            return 0;
        } else {
            free(tmp);
            return -1;
        }
    }
}

int read_storage_info(Storage *storage) {
    if (storage == NULL) {
        return -1;
    }

    printf("Enter serial number: ");
    char input[15];
    scanf("%14s", input);
    storage->number = strtoul(input, NULL, 10);
//    printf("%s%zu\n", "serial number is: ", storage->number);

    printf("Enter the type of storage: ");
    scanf("%15s", storage->type);
//    printf("%s%s\n", "type is: ", storage->type);

    printf("Enter the capacity: ");
    char input2[10];
    scanf("%9s", input2);
    storage->capacity = strtoul(input2, NULL, 10);
//    printf("%s%zu\n", "capacity is: ", storage->capacity);

    printf("Is the storage re-recordable (y/n): ");
    if (scan_bool(&storage->re_recordable) != 0) {
        return -1;
    }

    return 0;
}

Storage *create_storage(size_t number, char *type, size_t capacity, bool re_recordable) {
    Storage *storage = calloc(1, sizeof(Storage));
    if (storage == NULL) {
        return NULL;
    }
    storage->type = calloc(10, sizeof(char));
    if (storage->type == NULL) {
        free(storage);
        return NULL;
    }

//    strcpy(storage->type, type);
    if (snprintf(storage->type, sizeof(storage->type), "%9s", type) < 0) {
        delete_storage(storage);
        return NULL;
    }
    storage->number = number;
    storage->capacity = capacity;
    storage->re_recordable = re_recordable;

    return storage;
}


Storage *create_storage_from_terminal() {
    Storage *storage = calloc(1, sizeof(Storage));
    if (storage == NULL) {
        return NULL;
    }
    storage->type = calloc(10, sizeof(char));
    if (storage->type == NULL) {
        free(storage);
        return NULL;
    }

    if (read_storage_info(storage) != 0) {
        free(storage->type);
        free(storage);
        return NULL;
    }
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
    for (size_t i = 0; i < array_of_storages->number_of_storages; i++) {
        free(array_of_storages->buffer[i].type);
    }
    free(array_of_storages->buffer);
    free(array_of_storages);
    return 0;
}

int increase_array(Storages *array_of_storages) {
    if (array_of_storages == NULL) {
        return -1;
    }

    array_of_storages->buffer = realloc(array_of_storages->buffer,
                            sizeof(Storage) * array_of_storages->number_of_cells * BUFFER_INCREASE_COEFF);
    if (array_of_storages->buffer == NULL) {
        delete_storage(array_of_storages->buffer);
        delete_array_of_storages(array_of_storages);
        return -1;
    }


    array_of_storages->number_of_cells *= BUFFER_INCREASE_COEFF;
    return 0;
}

int add_storage_to_array(Storage *storage, Storages *array_of_storages) {
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

int display_suitable(size_t required_capacity, Storages *storages) {
    if (storages == NULL) {
        return -1;
    }

    int counter = 1;
    for (size_t i = 0; i < storages->number_of_storages; i++) {
        if (storages->buffer[i].re_recordable == true && storages->buffer[i].capacity >= required_capacity) {
            printf("\n%d%s%zu\n", counter, ".\nserial number is: ", storages->buffer[i].number);
            printf("%s%s\n", "Type of storage is: ", storages->buffer[i].type);
            printf("%s%zu\n", "Capacity is: ", storages->buffer[i].capacity);
            printf("Re recording is available\n");
            counter++;
        }
    }
    return 0;
}
