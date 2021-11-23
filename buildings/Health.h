#ifndef HEALTH_H
#define HEALTH_H

#include "Building.h"
class Health: public Building {
public:
    virtual Building::Category get_category() const override;

protected:
    explicit Health(City &city);
};
#endif // HEALTH_H
