#include <math.h>

int round_float_to_int(float number)
{
    return (int) ( (number < 0) ? number - 0.5 : number + 0.5 );
}