#include "GildedRose.h"
#include "items.h"

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}
    
void GildedRose::updateQuality() 
{
    for( auto &item : items){

      auto processor = get_item_processor(item.name);
      processor.update(item);
//
//        if(item.name == "Aged Brie"){
//            if (item.quality < 50)
//            {
//                item.quality = item.quality + 1;
//            }
//            item.sellIn = item.sellIn - 1;
//
//            if (item.sellIn < 0 && item.quality < 50)
//            {
//                item.quality = item.quality + 1;
//            }
//
//        } else if(item.name == "Backstage passes to a TAFKAL80ETC concert"){
//            if (item.quality < 50)
//            {
//                item.quality = item.quality + 1;
//                if (item.sellIn < 11)
//                {
//                    if (item.quality < 50)
//                    {
//                        item.quality = item.quality + 1;
//                    }
//                }
//
//                if (item.sellIn < 6)
//                {
//                    if (item.quality < 50)
//                    {
//                        item.quality = item.quality + 1;
//                    }
//                }
//            }
//            item.sellIn = item.sellIn - 1;
//
//            if (item.sellIn < 0) {
//                item.quality = item.quality - item.quality;
//            }
//
//        } else if(item.name == "Sulfuras, Hand of Ragnaros") {
//
//        } else {
//            if (item.quality > 0)
//            {
//                item.quality = item.quality - 1;
//            }
//            item.sellIn = item.sellIn - 1;
//
//            if (item.sellIn < 0)
//            {
//                if (item.quality > 0)
//                {
//                    item.quality = item.quality - 1;
//                }
//            }
//        }


    }
}
