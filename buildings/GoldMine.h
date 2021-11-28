#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "Revenue.h"
class GoldMine: public Revenue {
public:
    static const int cost{400};
    static const int attractiveness{4};

    explicit GoldMine(City &city);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;
    virtual int get_attractiveness() const override;

    virtual int get_revenue() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // GOLDMINE_H
