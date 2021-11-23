#ifndef REVENUE_H
#define REVENUE_H

#include "Building.h"
class Revenue: public Building {
public:
    virtual Building::Category get_category() const override;

protected:
    explicit Revenue(City &city);
};
#endif // REVENUE_H
