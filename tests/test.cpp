
#include <gtest/gtest.h>
#include <utils.h>

TEST(storage_creating, storage_creating_fail) {
    storage_t *storage = create_storage(12, nullptr, 350, false);
    EXPECT_EQ(storage, nullptr);
    delete_storage(storage);
}

TEST(storage_creating, storage_creating) {
    storage_t *expected_storage = (storage_t *) malloc(sizeof(storage_t));
    EXPECT_FALSE(expected_storage == nullptr);

    expected_storage->number = 12;
    expected_storage->capacity = 350;
    expected_storage->type = (char *) malloc(TYPE_SIZE * sizeof(char));
    EXPECT_FALSE(expected_storage->type == nullptr);
    strcpy(expected_storage->type, "HDD");
    expected_storage->re_recordable = false;

    storage_t *storage = create_storage(12, (char *) "HDD", 350, false);
    EXPECT_FALSE(storage == nullptr);
    EXPECT_EQ(storage->number, expected_storage->number);
    EXPECT_EQ(storage->capacity, expected_storage->capacity);
    EXPECT_EQ(storage->re_recordable, expected_storage->re_recordable);
    EXPECT_EQ(0, strcmp(storage->type, expected_storage->type));

    delete_storage(expected_storage);
    delete_storage(storage);
}


TEST(creating_array_of_storages, creating_array_of_storages) {
    storages_t *array = create_array_of_storages();
    EXPECT_FALSE(array == nullptr);

    EXPECT_FALSE(array->buffer == nullptr);
    EXPECT_TRUE(array->number_of_cells == STARTING_BUFFER_SIZE);
    EXPECT_TRUE(array->number_of_storages == 0);
    delete_array_of_storages(array);
}

TEST(add_storage_to_array, add_storage_to_array_fail) {
    storage_t *storage = nullptr;
    storages_t *array = create_array_of_storages();
    EXPECT_FALSE(array == nullptr);
    EXPECT_TRUE(add_storage_to_array(storage, array) == -1);
    delete_storage(storage);
    delete_array_of_storages(array);
}


TEST(add_storage_to_array, add_storage_to_array_fail2) {
    storage_t *storage = create_storage(12, (char *) "HDD", 350, false);
    EXPECT_FALSE(storage == nullptr);
    storages_t *array = nullptr;
    EXPECT_TRUE(add_storage_to_array(storage, array) == -1);
    delete_storage(storage);
    delete_array_of_storages(array);
}


TEST(add_storage_to_array, add_storage_to_array) {
    storage_t *storage1 = create_storage(1, (char *) "HDD", 50, true);
    EXPECT_FALSE(storage1 == nullptr);
    storages_t *array = create_array_of_storages();
    EXPECT_FALSE(array == nullptr);

    EXPECT_TRUE(add_storage_to_array(storage1, array) == 0);

    EXPECT_TRUE(array->buffer[0].number == 1);
    EXPECT_TRUE(array->buffer[0].capacity == 50);
    EXPECT_EQ(0, strcmp(array->buffer[0].type, (char *) "HDD"));
    EXPECT_TRUE(array->buffer[0].re_recordable == true);

    delete_array_of_storages(array);
}

TEST(array_increasing, array_increasing_fail) {
    storages_t *array = nullptr;
    EXPECT_TRUE(increase_array(array) == -1);
    delete_array_of_storages(array);
}


TEST(array_increasing, array_increasing) {
    storage_t *storage1 = create_storage(1, (char *) "HDD", 50, true);
    EXPECT_FALSE(storage1 == nullptr);
    storage_t *storage2 = create_storage(2, (char *) "SSD", 150, true);
    EXPECT_FALSE(storage2 == nullptr);
    storage_t *storage3 = create_storage(3, (char *) "USB", 250, true);
    EXPECT_FALSE(storage3 == nullptr);
    storages_t *array = create_array_of_storages();
    EXPECT_FALSE(array == nullptr);

    EXPECT_TRUE(array->number_of_storages == 0);
    EXPECT_TRUE(array->number_of_cells == STARTING_BUFFER_SIZE);

    EXPECT_TRUE(add_storage_to_array(storage1, array) == 0);
    EXPECT_TRUE(add_storage_to_array(storage2, array) == 0);
    EXPECT_TRUE(add_storage_to_array(storage3, array) == 0);

    EXPECT_TRUE(array->number_of_storages == 3);
    EXPECT_TRUE(array->number_of_cells == 4);

    EXPECT_TRUE(increase_array(array) == 0);

    EXPECT_TRUE(array->number_of_storages == 3);
    EXPECT_TRUE(array->number_of_cells == 8);

    delete_array_of_storages(array);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}