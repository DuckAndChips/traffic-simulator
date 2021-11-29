#ifndef HEALTH_H
#define HEALTH_H

#include "Node.h"

/* *
* Health Class
* 
* This class holds information and methods for Health nodes in the city grid. 
* This class inherites the Node class. 
*
* */


class Health: public Node {
public:
    virtual Node::Category get_category() const override;

protected:
    explicit Health(City &city);
};
#endif // HEALTH_H
