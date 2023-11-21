//
// Created by strenkwalder on 21.11.23.
//

#include <string>
#include "items.h"

int default_sell_date_processor(const Item &item);
int default_quality_processor(const Item &item);
int aged_brie_quality_processor(const Item &item);
int backstage_pass_quality_processor(const Item &item);

int ItemProcessor::get_new_sellIn(const Item &item) const {
    return this->process_sellIn_strategy(item);
}

int ItemProcessor::get_new_quality(const Item &item) const {
    return this->process_quality_strategy(item);
}

void ItemProcessor::update(Item &item) const{
    auto new_sellIn = this->get_new_sellIn(item);
    auto new_quality = this->get_new_quality(item);

    item.sellIn = new_sellIn;
    item.quality = new_quality;
}

ItemProcessor get_item_processor(const std::string &name) {
    if(name.contains(AGEDBRIE_NAME)){
        return {
                default_sell_date_processor,
                aged_brie_quality_processor
        };
    } else if(name.contains(SULDURAS_NAME)){
        return {
                [](const Item &i) { return i.sellIn;},
                [](const Item &i) { return 80;}
        };
    } else if(name.contains(BACKSTAGEPASS_NAME)){
        return {
                default_sell_date_processor,
                backstage_pass_quality_processor
        };
    } else if(name.contains(CONJURED_NAME)){
        return {
                default_sell_date_processor,
                default_quality_processor
        };
    } else {
        return {
                default_sell_date_processor,
                default_quality_processor
        };
    }
}

int default_sell_date_processor(const Item &item){
    return item.sellIn - 1;
}

int default_quality_processor(const Item &item){
    auto quality = item.quality;

    if( item.sellIn > 0 ){
        quality -= 1;
    } else {
        quality -= 2;
    }

    return std::min(std::max(quality, 0), 50);
}

int aged_brie_quality_processor(const Item &item){
    auto quality = item.quality;

    quality++;

    return std::max(
            std::min(quality,50),
            0
    );
}

int backstage_pass_quality_processor(const Item &item){
    auto quality = item.quality;

    if(item.sellIn <= 0){
        return 0;
    } else if(item.sellIn <= 5){
        quality += 3;
    } else if(item.sellIn <= 10){
        quality += 2;
    } else {
        quality++;
    }

    return std::min(quality,50);
}
