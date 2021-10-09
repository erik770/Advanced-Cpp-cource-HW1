
#include <gtest/gtest.h>
#include <../include/utils.h>


TEST(storage_constr, storage_constr) {
    Storage *expected_storage = (Storage *) malloc(sizeof(Storage));
    EXPECT_FALSE(expected_storage == nullptr);

    expected_storage->number = 12;
    expected_storage->capacity = 350;
    expected_storage->type = (char *) malloc(10 * sizeof(char));
    EXPECT_FALSE(expected_storage->type == nullptr);
    strcpy(expected_storage->type, "HDD");
    expected_storage->re_recordable = false;

    Storage *storage = create_storage(12, (char *) "HDD", 350, false);
    EXPECT_EQ(storage->number, expected_storage->number);
    EXPECT_EQ(storage->capacity, expected_storage->capacity);
    EXPECT_EQ(storage->re_recordable, expected_storage->re_recordable);
    EXPECT_EQ(0, strcmp(storage->type, expected_storage->type));
    free(expected_storage->type);
    free(expected_storage);
    free(storage->type);
    free(storage);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}