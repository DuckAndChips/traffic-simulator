#ifndef HEALTH_H
#define HEALTH_H

#include "Node.h"

class Health: public Node {
public:
    virtual Node::Category get_category() const override;

protected:
    explicit Health(City &city);
};
#endif // HEALTH_H
