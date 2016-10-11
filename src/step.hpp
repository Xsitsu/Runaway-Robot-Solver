#ifndef STEP_HPP
#define STEP_HPP

#include <iostream>

class Step
{
private:
    bool did_R;
    bool did_D;
    char cur;
    
public:
    Step();
    Step(char step);
    Step(const Step& copy);
    ~Step();
    Step& operator=(const Step& rhs);
    
    char GetStep() { return cur; }
    bool Exhausted() { return did_R && did_D; }
    
    void ChangeDirection();
    
};

#endif // STEP_HPP
