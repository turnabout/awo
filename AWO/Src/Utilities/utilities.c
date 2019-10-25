#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

int read_file(const char *file_name, char **buffer)
{
    FILE* f_stream;
    long f_size;

    #ifndef __EMSCRIPTEN__
    errno_t err;
    #endif

    // Open the file
    #ifdef __EMSCRIPTEN__
    if ((f_stream = fopen(file_name, "r")) == NULL) {
    #else
    if ((err = fopen_s(&f_stream, file_name, "r")) != 0) {
    #endif
        printf("Error opening file %s\n", file_name);
        return 0;
    }

    if (f_stream == 0) {
        printf("Error reading file %s\n", file_name);
        return 0;
    }

    // Get file size
    fseek(f_stream, 0, SEEK_END);
    f_size = ftell(f_stream);
    fseek(f_stream, 0, SEEK_SET);

    // Store file contents
    *buffer = malloc(f_size + 1);

    if (*buffer != NULL) {
        fread(*buffer, 1, f_size, f_stream);
        fclose(f_stream);
        (*buffer)[f_size] = '\0';

        return f_size;
    }

    printf("Error storing file contents\n");
    return 0;
}
