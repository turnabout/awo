#pragma once

#include "Headers/macros.h"
#include "Headers/types.h"

/*! @brief Reads a file and returns its contents in allocated memory.
 *
 *  @param[in] file_path The path of the file to read.
 *  @return Pointer to the buffer containing the read data or NULL if an error occurred.
 */
char* read_file(const char* file_path);

/*! @brief Reads a string of following hexadecimal characters and converts into a data byte array.
 *
 *  @param[in] string The string to translate.
 *  @param[out] data_length The length of the data array.
 *  @return The generated data bytes array.
 */
Uint8* hex_string_to_data(char* string, size_t* data_length);

/*! @brief Rounds a float number and returns as an integer.
 *
 *  @param[in] number Float to round.
 *  @return The rounded integer.
 */
int round_float_to_int(float number);