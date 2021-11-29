#include "Health.h"

/* * Construct a Health object
 * 
 * Calls constructor for a Health object.
 * 
 * @param city A reference to the current city.
 * */
Health::Health(City &city): Node(city) {}

/** Get the Node Category of the Health object
 * 
 * @return A Node::Category::HEALTH enum value of Node::Category.
 */
Node::Category Health::get_category() const {
    return Category::HEALTH;
}
