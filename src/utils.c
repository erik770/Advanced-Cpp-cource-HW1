#include "utils.h"

int scan_bool(bool *boolean) {
    if (boolean == NULL) {
        return -1;
    }

    char tmp[2];
    scanf("%1s", tmp);

    if (*tmp != 'y' && *tmp != 'n') {
        return -1;
    }
    if (*tmp == 'n') {
        *boolean = false;
        return 0;
    }
    *boolean = true;
    return 0;
}

int read_storage_info(storage_t *storage) {
    if (storage == NULL) {
        return -1;
    }

    printf("Enter serial number: ");
    char input[INPUT_BUFFER_SIZE];
    scanf("%14s", input);
    storage->number = strtoul(input, NULL, 10);

    printf("Enter the type of storage: ");
    scanf("%15s", storage->type);

    printf("Enter the capacity: ");
    char input2[INPUT_BUFFER_SIZE];
    scanf("%14s", input2);
    storage->capacity = strtoul(input2, NULL, 10);

    printf("Is the storage re-recordable (y/n): ");
    if (scan_bool(&storage->re_recordable) != 0) {
        return -1;
    }

    return 0;
}

storage_t *create_storage(size_t number, const char *type,  size_t capacity, bool re_recordable) {
    if (type == NULL) {
        return NULL;
    }

    storage_t *storage = calloc(1, sizeof(storage_t));
    if (storage == NULL) {
        return NULL;
    }
    storage->type = calloc(TYPE_SIZE, sizeof(char));
    if (storage->type == NULL) {
        free(storage);
        return NULL;
    }

    if (snprintf(storage->type, TYPE_SIZE * sizeof(char), "%s", type) < 0) {
        delete_storage(storage);
        return NULL;
    }
    storage->number = number;
    storage->capacity = capacity;
    storage->re_recordable = re_recordable;

    return storage;
}


storage_t *create_storage_from_terminal() {
    storage_t *storage = calloc(1, sizeof(storage_t));
    if (storage == NULL) {
        return NULL;
    }
    storage->type = calloc(TYPE_SIZE, sizeof(char));
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

int delete_storage(storage_t *storage) {
    if (storage == NULL) {
        return -1;
    }
    free(storage->type);
    free(storage);
    return 0;
}

storages_t *create_array_of_storages() {
    storages_t *array_of_storages = calloc(1, sizeof(storages_t));
    if (array_of_storages == NULL) {
        return NULL;
    }
    array_of_storages->buffer = calloc(STARTING_BUFFER_SIZE, sizeof(storage_t));
    if (array_of_storages->buffer == NULL) {
        free(array_of_storages);
        return NULL;
    }

    array_of_storages->number_of_cells = STARTING_BUFFER_SIZE;
    array_of_storages->number_of_storages = 0;
    return array_of_storages;
}

int delete_array_of_storages(storages_t *array_of_storages) {
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

int increase_array(storages_t *array_of_storages) {
    if (array_of_storages == NULL) {
        return -1;
    }

    array_of_storages->buffer = realloc(array_of_storages->buffer,
                           sizeof(storage_t) * array_of_storages->number_of_cells * BUFFER_INCREASE_COEFF);
    if (array_of_storages->buffer == NULL) {
        delete_storage(array_of_storages->buffer);
        delete_array_of_storages(array_of_storages);
        return -1;
    }


    array_of_storages->number_of_cells *= BUFFER_INCREASE_COEFF;
    return 0;
}

int add_storage_to_array(storage_t *storage, storages_t *array_of_storages) {
    if (storage == NULL || array_of_storages == NULL) {
        return -1;
    }

    if (array_of_storages->number_of_cells == array_of_storages->number_of_storages) {
        if (increase_array(array_of_storages) !=0) {
            free(storage);
            return -1;
        }
    }

    array_of_storages->buffer[array_of_storages->number_of_storages] = *storage;
    free(storage);
    array_of_storages->number_of_storages++;
    return 0;
}

int display_suitable(size_t required_capacity, const storages_t *storages) {
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
