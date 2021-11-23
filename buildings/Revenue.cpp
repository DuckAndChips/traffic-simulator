#include "Revenue.h"

Revenue::Revenue(City &city): Building(city) {}

Building::Category Revenue::get_category() const {
    return Category::REVENUE;
}
