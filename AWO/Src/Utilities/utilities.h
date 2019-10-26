#pragma once

/**
 *  \brief Reads a file and stores its contents in memory.
 *
 *  \param file_name Path to the file to read.
 *
 *  \return Pointer to the buffer containing the read data.
 */
char* read_file(const char* file_name);