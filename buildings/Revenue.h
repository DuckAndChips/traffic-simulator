#ifndef REVENUE_H
#define REVENUE_H

#include "Node.h"
class Revenue: public Node {
public:
    virtual Node::Category get_category() const override;

protected:
    explicit Revenue(City &city);
};
#endif // REVENUE_H
