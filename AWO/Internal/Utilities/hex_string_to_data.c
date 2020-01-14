#include <string.h>
#include <stdlib.h>

#include "Utilities/utilities.h"

/*! @brief Reads a string of following hexadecimal characters and translates it into a data array.
 *
 *  @param[in] string The string to translate.
 *  @param[out] data_length The length of the data array.
 *  @return The generated data array.
 */
Uint8* hex_string_to_data(char* string, size_t* data_length)
{

    if (string == NULL) {
        return NULL;
    }

    size_t string_length = strlen(string);

    if ((string_length % 2) != 0) {
        return NULL;
    }

    *data_length = string_length / 2;

    Uint8* data = malloc(*data_length);
    memset(data, 0, *data_length);

    size_t index = 0;

    while (index < string_length) {
        char c = string[index];
        int value = 0;

        if (c >= '0' && c <= '9') {
            value = (c - '0');

        } else if (c >= 'A' && c <= 'F') {
            value = (10 + (c - 'A'));

        } else if (c >= 'a' && c <= 'f') {
            value = (10 + (c - 'a'));

        } else {
            free(data);
            return NULL;
        }

        data[(index/2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}
