#include "Health.h"

Health::Health(City &city): Node(city) {}

Node::Category Health::get_category() const {
    return Category::HEALTH;
}
