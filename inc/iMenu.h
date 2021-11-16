#include <stdint.h>

class iMenu 
{
    public:
        virtual void display() = 0;
        virtual bool handle(uint8_t command) = 0;
};