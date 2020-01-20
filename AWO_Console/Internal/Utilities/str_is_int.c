#include <string.h>
#include <ctype.h>

int str_is_int(char* str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }

    return 1;
}

