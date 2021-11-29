#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "Revenue.h"

/* *
* GoldMine Class
* 
* This class holds information and methods for GoldMine nodes in the city grid. 
* This class inherites the Revenue class, which inherits the Node class. 
*
* */


class GoldMine: public Revenue {
public:
    static const int cost{400};
    static const int attractiveness{4};

    explicit GoldMine(City &city);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;
    virtual int get_attractiveness() const override;

    virtual int get_revenue() const override;
    virtual int get_revenue_per_worker() const override;
    virtual void set_revenue_per_worker(int r);

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;

private:
    int revenue_per_worker = 10;
};
#endif // GOLDMINE_H
