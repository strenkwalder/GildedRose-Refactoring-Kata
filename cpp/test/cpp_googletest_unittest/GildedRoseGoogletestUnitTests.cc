#include <gtest/gtest.h>
#include "GildedRose.h"
#include "items.h"

//TEST(GildedRoseTest, Foo) {
//    vector<Item> items;
//    items.push_back(Item("Foo", 0, 0));
//    GildedRose app(items);
//    app.updateQuality();
//    EXPECT_EQ("fixme", app.items[0].name);
//}

TEST(BasicTests, item_processor_should_lower_sellIn) {
    Item item("Something", 150, 15);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(150 - 1, item.sellIn);
}

TEST(BasicTests, item_processor_should_lower_quality_by_one) {
    Item item("Something", 150, 15);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(15 - 1, item.quality);
}

TEST(BasicTests, item_processor_should_lower_quality_twice_as_fast_when_sell_date_has_passed) {
    Item item("Something", 0, 15);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(15 - 2, item.quality);
}

TEST(BasicTests, quality_should_never_be_negative) {
    Item item("Something", 0, 1);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    processor.update(item);
    ASSERT_EQ(0, item.quality);
}

TEST(BasicTests, aged_brie_increases_quality_with_update) {
    Item item("Aged Brie", 50, 15);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(15+1, item.quality);
}

TEST(BasicTests, aged_brie_cannot_increases_quality_over_50) {
    Item item("Aged Brie", 29, 50);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(50, item.quality);
}

TEST(BasicTests, sulfuras_quality_is_constantly_80) {
    Item item("Sulfuras", 29, 25);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    processor.update(item);
    ASSERT_EQ(80, item.quality);
}

TEST(BasicTests, sulfuras_dont_change_sell_date_on_update) {
    Item item("Sulfuras", 29, 25);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    processor.update(item);
    ASSERT_EQ(29, item.sellIn);
}

TEST(BasicTests, backstage_pass_increases_quality_after_update) {
    Item item("Backstage pass", 29, 25);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(26, item.quality);
}

TEST(BasicTests, backstage_pass_increases_quality_by_two_if_fewer_than_10_days_remain) {
    Item item("Backstage pass", 10, 25);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(27, item.quality);
}

TEST(BasicTests, backstage_pass_increases_quality_by_three_if_fewer_than_5_days_remain) {
    Item item("Backstage pass", 5, 25);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(28, item.quality);
}

TEST(BasicTests, backstage_pass_increases_quality_is_zero_when_after_the_concert) {
    Item item("Backstage pass", 0, 25);
    const auto processor = get_item_processor(item.name);
    processor.update(item);
    ASSERT_EQ(0, item.quality);
}

TEST(BasicTests, conjoured_decreases_quality_twice_as_much_as_a_normal_item) {
    Item conjured_item("Conjured", 50, 25);
    Item normal_item("some item", 50, 25);
    const auto processor = get_item_processor(conjured_item.name);
    processor.update(conjured_item);
    const auto normal_processor = get_item_processor(normal_item.name);
    normal_processor.update(normal_item);
    ASSERT_EQ(conjured_item.quality - 25, (normal_item.quality - 25)*2);
}
