#include "step.hpp"

Step::Step() : did_R(false), did_D(false), cur('X')
{
    
}

Step::Step(char step) : did_R(false), did_D(false), cur(step)
{
    if (cur == 'R')
        did_R = true;
    else
        did_D = true;
}

Step::Step(const Step& copy) : did_R(copy.did_R), did_D(copy.did_D), cur(copy.cur)
{
    did_R = copy.did_R;
    did_D = copy.did_D;
    
}

Step::~Step()
{
    
}

Step& Step::operator=(const Step& rhs)
{
    if (this != &rhs)
    {
        cur = rhs.cur;
        did_R = rhs.did_R;
        did_D = rhs.did_D;
    }
    
    return *this;
}

void Step::ChangeDirection()
{
    if (did_R)
    {
        cur = 'D';
        did_D = true;
    }
    else
    {
        cur = 'R';
        did_R = true;
    }
    
    did_R = true;
    did_D = true;
}
