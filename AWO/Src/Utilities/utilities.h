#pragma once

/*! @brief Reads a file and returns its contents in allocated memory.
 *
 *  @param[in] file_path The path of the file to read.
 *  @return Pointer to the buffer containing the read data or NULL if an error occurred.
 */
char* read_file(const char* file_path);