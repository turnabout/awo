#include <string.h>

#include "cJSON.h"
#include "../../../Utils/utils.h"
#include "../../../conf.h"

int load_visuals_JSON(const cJSON **visuals_JSON)
{
    // Get file contents & size
    char *f_contents;
    int size;

    if ((size = read_file(JSON_PATH, &f_contents)) == ERR) {
        return ERR;
    }

    // Populate visuals JSON struct
    *visuals_JSON = cJSON_Parse(f_contents);

    // Clear previously accumulated file contents
    memset(f_contents, 0, size);

    return OK;
}
