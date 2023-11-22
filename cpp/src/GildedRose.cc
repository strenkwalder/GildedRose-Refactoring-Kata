#include "GildedRose.h"
#include "items.h"

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}
    
void GildedRose::updateQuality() 
{
    for( auto &item : items){

      auto processor = get_item_processor(item.name);
      processor.update(item);
    }
}
