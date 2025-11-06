cmake_minimum_required(VERSION 3.10)

# Find pybind11
find_package(pybind11 CONFIG REQUIRED)

# Find Python
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Create Python module
pybind11_add_module(pyeyerec py_pure.cpp)

# Link against the eyerec library
target_link_libraries(pyeyerec PRIVATE eyerec ${OpenCV_LIBS})

# Include directories
target_include_directories(pyeyerec PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${OpenCV_INCLUDE_DIRS}
)

# Set output directory
set_target_properties(pyeyerec PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/python"
)
