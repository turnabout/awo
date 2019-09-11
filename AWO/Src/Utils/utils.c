#include <stdio.h>
#include <stdlib.h>
#include "../conf.h"

#pragma warning( disable : 6386 )

int read_file(const char *file_name, char **buffer)
{
    FILE* f_stream;
    errno_t err;
    long f_size;

    // Open the file
    if ((err = fopen_s(&f_stream, file_name, "r")) != 0) {
        printf("Error opening file %s\n", file_name);
        return ERR;
    }

    if (f_stream == 0) {
        printf("Error reading file %s\n", file_name);
        return ERR;
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
    return ERR;
}
