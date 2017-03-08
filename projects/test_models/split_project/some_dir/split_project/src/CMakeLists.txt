set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(split_project STATIC ${files})
set_target_properties(split_project PROPERTIES
    OUTPUT_NAME dogen.split_project)

install(TARGETS split_project ARCHIVE DESTINATION lib COMPONENT libraries)
