// Include header files for test frameworks 
#include <gtest/gtest.h>
#include <ApprovalTests.hpp>

// Include code to be tested
#include "GildedRose.h"
#include "items.h"

std::ostream& operator<<(std::ostream& os, const Item& obj)
{
    return os
        << "name: " << obj.name
        << ", sellIn: " << obj.sellIn
        << ", quality: " << obj.quality;
}

TEST(GildedRoseApprovalTests, VerifyCombinations) {

    std::vector<string> names {
        "Item",
        "OtherItem",
        "Aged Brie",
        "Sulfuras, Hand of Ragnaros",
        "Backstage passes to a TAFKAL80ETC concert",
    };
    std::vector<int> sellIns { -1, 0, 1, 10, INT32_MAX};
    std::vector<int> qualities { -1, 0, 1, 10, 50, INT32_MAX};
    std::vector<unsigned int> updates {0, 1, 2, 5};

    auto f = [](string name, int sellIn, int quality, unsigned int updates) {
        vector<Item> items = {Item(name, sellIn, quality)};
        GildedRose app(items);
        for(size_t i = 0; i < updates; i++){
            app.updateQuality();
        }
        return items[0];
    };

    ApprovalTests::CombinationApprovals::verifyAllCombinations(
            f,
            names, sellIns, qualities, updates);

}
