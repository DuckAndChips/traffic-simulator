#ifndef REVENUE_H
#define REVENUE_H

#include "Node.h"

/**
 * Revenue class
 * 
 * This class holds information and methods for Revenue type nodes in the city grid.
 * This class inherits the Node class.
 * 
 */
class Revenue: public Node {
public:
    virtual Node::Category get_category() const override;
    virtual int get_working_population() const override;
    virtual void set_working_population(int population);

protected:
    explicit Revenue(City &city);
    int working_population;
};
#endif // REVENUE_H
