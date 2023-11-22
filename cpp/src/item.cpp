//
// Created by strenkwalder on 21.11.23.
//

#include <string>
#include "items.h"

int default_sell_date_processor(const Item &item);
int default_quality_processor(const Item &item);

int calculate_default_quality_change(const Item &item);

int aged_brie_quality_processor(const Item &item);
int backstage_pass_quality_processor(const Item &item);
int conjured_quality_processor(const Item &item);

    int ItemProcessor::get_new_selling_days(const Item &item) const {
    return this->process_sellIn_strategy(item);
}

int ItemProcessor::get_new_quality(const Item &item) const {
    return this->process_quality_strategy(item);
}

void ItemProcessor::update(Item &item) const{
    auto new_selling_days = this->get_new_selling_days(item);
    auto new_quality = this->get_new_quality(item);

    item.sellIn = new_selling_days;
    item.quality = new_quality;
}

ItemProcessor get_item_processor(const std::string &name) {
    if(name.contains(AGEDBRIE_NAME)){
      return {default_sell_date_processor, aged_brie_quality_processor};
    } else if(name.contains(SULDURAS_NAME)){
      return {
                [](const Item &i) { return i.sellIn;},
                [](const Item &i) { return 80;}
      };
    } else if(name.contains(BACKSTAGEPASS_NAME)){
      return {default_sell_date_processor, backstage_pass_quality_processor};
    } else if(name.contains(CONJURED_NAME)){
      return {default_sell_date_processor, conjured_quality_processor};
    } else {
        return {default_sell_date_processor, default_quality_processor};
    }
}

int default_sell_date_processor(const Item &item){
    return item.sellIn - 1;
}

int aged_brie_quality_processor(const Item &item) {
    if (item.quality >= 50) {
        return item.quality;
    }

    if (item.sellIn > 0)
    {
        return item.quality + 1;
    }

    return item.quality + 2;
}
int backstage_pass_quality_processor(const Item &item) {
    if (item.sellIn <= 0) {
        return 0;
    }

    if (item.quality >= 50) {
        return item.quality;
    }

    int delta = 1;
    if (item.sellIn <= 10)
    {
        delta++;
    }

    if (item.sellIn <= 5)
    {
        delta++;
    }

    return item.quality + delta;
}

int calculate_default_quality_change(const Item &item){
    int delta = 0;
    if (item.quality >= 1)
    {
        delta--;
    }

    if (item.sellIn <= 0)
    {
        if (item.quality >= 2)
        {
          delta--;
        }
    }
    return delta;
}

int default_quality_processor(const Item &item) {
    auto delta = calculate_default_quality_change(item);
    return item.quality + delta;
}

int conjured_quality_processor(const Item &item) {
    auto delta = calculate_default_quality_change(item);
    return item.quality + (2*delta);
}
