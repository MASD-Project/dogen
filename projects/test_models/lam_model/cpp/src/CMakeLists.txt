set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(lam_model STATIC ${files})
set_target_properties(lam_model PROPERTIES
    OUTPUT_NAME dogen.lam_model)

install(TARGETS lam_model ARCHIVE DESTINATION lib COMPONENT libraries)
