#include "Singleton.h"

int SingletonDatabase::count = 0;

//TEST(DatabaseTests, IsSingletonSingleTest)
//{
//    auto& db1 = SingletonDatabase::get();
//    auto& db2 = SingletonDatabase::get();
//
//    ASSERT_EQ(1, db1.count);
//    ASSERT_EQ(1, db2.count);
//}

int main(int ac, char* av[])
{
//    testing::InitGoogleTest(&ac, av);
//    return RUN_ALL_TESTS();

    auto& db = SingletonDatabase::get();

    return 0;
}
