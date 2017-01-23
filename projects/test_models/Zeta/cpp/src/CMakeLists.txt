set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Zeta STATIC ${files})
set_target_properties(Zeta PROPERTIES
    OUTPUT_NAME Zeta)

install(TARGETS Zeta ARCHIVE DESTINATION lib COMPONENT libraries)
