//
// Created by strenkwalder on 21.11.23.
//

#ifndef GILDED_ROSE_REFACTORING_KATA_CPP_ITEMS_H
#define GILDED_ROSE_REFACTORING_KATA_CPP_ITEMS_H

#include <string>
#include <utility>
#include <memory>

class Item
{
public:
    std::string name;
    int sellIn;
    int quality;

    Item(
        std::string name,
        int sellIn,
        int quality
    ) : name(std::move(name)), sellIn(sellIn), quality(quality){}
};

const std::string AGEDBRIE_NAME = "Aged Brie";
const std::string SULDURAS_NAME = "Sulfuras";
const std::string BACKSTAGEPASS_NAME = "Backstage pass";
const std::string CONJURED_NAME = "Conjured";

typedef int (*SellInProcessor)(const Item &item);
typedef int (*QualityProcessor)(const Item &item);

class ItemProcessor {
    SellInProcessor process_sellIn_strategy;
    QualityProcessor process_quality_strategy;

    int get_new_sellIn(const Item &item) const;
    int get_new_quality(const Item &item) const;

public:
    ItemProcessor(
        SellInProcessor updateSellIn,
        QualityProcessor updateQuality
    ): process_sellIn_strategy(updateSellIn), process_quality_strategy(updateQuality) {}

    void update(Item &item) const;

};

ItemProcessor get_item_processor(const std::string &name);

#endif //GILDED_ROSE_REFACTORING_KATA_CPP_ITEMS_H
