#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* file_path)
{
    FILE* f_stream;
    long f_size;

    // Open the file
    if ((f_stream = fopen(file_path, "rb")) == NULL) {
        printf("Error opening file %s\n", file_path);
        return NULL;
    }

    if (f_stream == 0) {
        printf("Error reading file %s\n", file_path);
        return NULL;
    }

    // Get file size
    fseek(f_stream, 0, SEEK_END);
    f_size = ftell(f_stream);
    fseek(f_stream, 0, SEEK_SET);

    // Store file contents
    char *buffer = malloc(f_size + 1);

    if (buffer != NULL) {
        fread(buffer, 1, f_size, f_stream);
        fclose(f_stream);
        (buffer)[f_size] = '\0';

        return buffer;
    }

    printf("Error storing file contents\n");
    return NULL;
}
