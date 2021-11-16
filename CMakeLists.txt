# Minimum version of CMAKE
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Menu VERSION 0.1)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configuring header file to pass version number to the source code
configure_file(inc/config.h.in config.h)



# Add files ending with .cpp to source file list
file (GLOB SOURCE_FILES "src/*.cpp")

# Add the executable
add_executable(Menu ${SOURCE_FILES})

# Include files from directory specially header files
target_include_directories(Menu PRIVATE 
                                        inc
                                        ${PROJECT_BINARY_DIR}
                            )

