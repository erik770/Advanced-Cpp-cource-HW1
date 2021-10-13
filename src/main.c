#include "utils.h"

int main() {
    storages_t *storages = create_array_of_storages();
    if (storages == NULL) {
        return -1;
    }
    bool ans = true;
    printf("Add your first storage:\n");
    while (ans) {
        storage_t *storage = create_storage_from_terminal();
        if (storage == NULL) {
            delete_array_of_storages(storages);
            return -1;
        }

        if (add_storage_to_array(storage, storages) != 0) {
            delete_storage(storage);
            delete_array_of_storages(storages);
            return -1;
        }


        printf("\nDo you want to add new storage(y or n): ");
        if (scan_bool(&ans) != 0) {
            return -1;
        }
    }

    printf("how much capacity do you need? : ");
    char input[INPUT_BUFFER_SIZE];
    scanf("%14s", input);
    size_t required_capacity = strtoul(input, NULL, 10);
    if (display_suitable(required_capacity, storages) != 0) {
        delete_array_of_storages(storages);
        return -1;
    }
    delete_array_of_storages(storages);
    return 0;
}
