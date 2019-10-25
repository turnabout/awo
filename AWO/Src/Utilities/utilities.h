#pragma once

/**
 *  \brief Reads a file and stores its contents in memory.
 *
 *  \param file_name Path to the file to read.
 *
 *  \param buffer Where to store the file contents.
 *
 *  \return Returns 0 if an error occurred, or the file's size.
 */
int read_file(const char* file_name, char** buffer);