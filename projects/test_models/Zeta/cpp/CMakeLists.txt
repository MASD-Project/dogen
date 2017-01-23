add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

install(
    DIRECTORY include/
    DESTINATION include/
    COMPONENT headers
    FILES_MATCHING PATTERN "*.hpp")

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include//Zeta")
set(all_odb_files "")
file(GLOB_RECURSE all_odb_files RELATIVE
    "${include_dir}/odb/"
    "${include_dir}/odb/*_pragmas.hpp")

set(src_odb_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/odb/")
if(NOT EXISTS "${src_odb_dir}")
    file(MAKE_DIRECTORY "${src_odb_dir}")
endif()

add_custom_target(codegen_Zeta_odb
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/include//Zeta/odb/*.cpp
    ${src_odb_dir})

set(ignore_file false)
foreach(odb_file ${all_odb_files})
    if (odb_file MATCHES "all_pragmas.hpp")
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(type_name "")
        string(REPLACE "_pragmas.hpp" "" type_name ${odb_file})
        string(REPLACE "\\" "_" type_name ${type_name})
        string(REPLACE "/" "_" type_name ${type_name})

        set(pfh_dir "$ENV{PFH_LOCATION}")
        set(target_name "codegen_Zeta_odb_${type_name}")
        add_custom_target(${target_name}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/src/options.odb
            --std c++11
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/include//Zeta/odb/
            --odb-epilogue '\#include \"/Zeta/odb/${odb_file}\"'
            -I ${pfh_dir}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${include_dir}/types/${type_name}.hpp)

        add_dependencies(codegen_Zeta_odb ${target_name})
    endif()
    add_dependencies(codegen_Zeta_odb codegen_Zeta)
    set(ignore_file false)
endforeach()
