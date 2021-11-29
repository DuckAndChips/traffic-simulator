#ifndef SILVERMINE_H
#define SILVERMINE_H

#include "Revenue.h"

/* *
* SilverMine Class
* 
* This class holds information and methods for SilverMine nodes in the city grid. 
* This class inherites the Revenue class, which inherits the Node class. 
*
* */
class SilverMine: public Revenue {
public:
    static const int cost{50};
    static const int attractiveness{2};

    explicit SilverMine(City &city);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;
    virtual int get_attractiveness() const override;

    virtual int get_revenue() const override;
    virtual int get_revenue_per_worker() const override;
    virtual void set_revenue_per_worker(int r);

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;

private:
    int revenue_per_worker = 5;
};
#endif // SILVERMINE_H
