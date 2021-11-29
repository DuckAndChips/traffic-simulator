#include "Revenue.h"

/** Construct a Revenue building. 
 * 
 * Virtual function. 
 * This constructor can only be called by its childs. 
 * Constructs a Node with the current city. 
 * 
 * @param city A reference to the current city.
 */
Revenue::Revenue(City &city): Node(city) {}

/** Get the category of a Revenue building. 
 * 
 * @return A Node::Category::REVENUE enum value of Node::Category.
 * */
Node::Category Revenue::get_category() const {
    return Category::REVENUE;
}

/** Get the working poulation of a Revenue building. 
 * 
 * @return Working population of the Revenue building.
 * */
int Revenue::get_working_population() const {
    return working_population;
}

/** Set the working population of a Revenue building. 
 * 
 * @param p Working population of the Revenue building to be set to.
 * */
void Revenue::set_working_population(int p) {
    working_population = p;
}

