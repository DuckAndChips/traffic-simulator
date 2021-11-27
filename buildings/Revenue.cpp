#include "Revenue.h"

Revenue::Revenue(City &city): Node(city) {}

Node::Category Revenue::get_category() const {
    return Category::REVENUE;
}
