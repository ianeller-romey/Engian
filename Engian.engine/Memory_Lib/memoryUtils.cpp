
#include "memoryUtils.h"


namespace Memory 
{

    bool getBit(const char& byte, const unsigned position)
    {
        return (byte >> position) & 0x1;
    }


    void toggleBit(char& byte, const unsigned position)
    {
        byte ^= 0x1 << position;
    }

}
