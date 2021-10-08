#include <stdio.h>
#include "../include/utils.h"

int main()
{
    Storage* storage = create_storage();
    Storages *arr = create_array_of_storages();
    add_storage_to_array(storage, arr);
    printf("%s", arr[0].buffer->type);
    delete_array_of_storages(arr);
}