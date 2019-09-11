#include <string.h>

#include "../cJSON/cJSON.h"
#include "../Utils/utils.h"
#include "../conf.h"

static cJSON *visuals_JSON;

int load_visuals_JSON()
{
    // Get file contents & size
    char *f_contents;
    int size;

    if ((size = read_file(JSON_PATH, &f_contents)) == ERR) {
        return ERR;
    }

    // Populate visuals JSON struct
    visuals_JSON = cJSON_Parse(f_contents);

    // Clear previously accumulated file contents
    memset(f_contents, 0, size);

    return OK;
}

void test_JSON()
{
    const cJSON* ss_meta_data = NULL;

    // Loop ss meta data
    ss_meta_data = cJSON_GetObjectItemCaseSensitive(visuals_JSON, "ssMetaData");

    // Looped values
    const cJSON* dimension = NULL;

    cJSON_ArrayForEach(dimension, ss_meta_data)
    {
        // width: ... height: ...
        // printf("%s: %d\n", dimension->string, dimension->valueint);
    }
}
