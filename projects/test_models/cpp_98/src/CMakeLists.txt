set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(cpp_98 STATIC ${files})
set_target_properties(cpp_98 PROPERTIES
    CXX_STANDARD 98
    OUTPUT_NAME dogen.cpp_98)

install(TARGETS cpp_98 ARCHIVE DESTINATION lib COMPONENT libraries)
