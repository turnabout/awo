#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input_Handlers/Keyboard_Handler/keyboard_handler.h"
#include "Input_State/Keyboard_State/keyboard_state.h"
#include "Linked_List/linked_list.h"

struct Keyboard_Handler {

    // GLFW window handle.
    GLFWwindow* glfw_window;

};