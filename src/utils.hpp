#pragma once

#include <stdio.h>


namespace nc{
namespace utils{

    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

}
}




