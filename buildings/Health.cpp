#include "Health.h"

Health::Health(City &city): Building(city) {}

Building::Category Health::get_category() const {
    return Category::HEALTH;
}
