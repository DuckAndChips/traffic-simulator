#ifndef SILVERMINE_H
#define SILVERMINE_H

#include "Revenue.h"
class SilverMine: public Revenue {
public:
    static const int cost{50};
    static const int attractiveness{2};
    static const int revenue_per_worker{5};

    explicit SilverMine(City &city);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;
    virtual int get_attractiveness() const override;

    virtual int get_revenue() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // SILVERMINE_H
