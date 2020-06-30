cmake_minimum_required(VERSION 3.16)
project(AWO_Solution C)

SET(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/output")

add_subdirectory("${PROJECT_SOURCE_DIR}/AWO_Desktop" "${OUTPUT_DIR}/AWO_Desktop")

