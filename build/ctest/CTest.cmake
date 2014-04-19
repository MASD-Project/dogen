# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#

# handle input parameters to script.
if(DEFINED CTEST_SCRIPT_ARG)
    # transform ctest script arguments of the form
    # script.ctest,var1=value1,var2=value2
    # to variables with the respective names set to the respective values
    string(REPLACE "," ";" script_args "${CTEST_SCRIPT_ARG}")
    foreach(current_var ${script_args})
        if ("${current_var}" MATCHES "^([^=]+)=(.+)$")
            set("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
        endif()
    endforeach()
endif()

#
# model
#
if(NOT DEFINED model)
    set(model Experimental)
else()
    if(${model} MATCHES Experimental)
        message("Building Experimental model.")
    elseif(${model} MATCHES Nightly)
        message("Building Nightly model.")
    elseif(${model} MATCHES Continuous)
        message("Building Continuous model.")
    else()
        message(FATAL_ERROR "Invalid model: ${model}")
    endif()
endif()

#
# product
#
if(NOT DEFINED product)
    message(FATAL_ERROR "Product not supplied")
else()
    if(${product} MATCHES dogen)
        message("Build product dogen")
    else()
        message(FATAL_ERROR "Invalid product: ${product}")
    endif()
endif()

#
# build type
#
if(NOT DEFINED build_type)
    message(FATAL_ERROR "Build type not supplied")
else()
    if(${build_type} MATCHES code)
        message("Running code build type.")
    elseif(${build_type} MATCHES doxygen)
        message("Running doxygen build type.")
    else()
        message(FATAL_ERROR "Invalid build type: ${build_type}")
    endif()
endif()

#
# build type
#
if(NOT DEFINED build_dir)
    message(FATAL_ERROR "Build directory not supplied")
else()
    message("Build directory is ${build_dir}.")
endif()

#
# additional input arguments
#
set(is_code false)
if("${build_type}" STREQUAL "code")
    set(is_code true)
endif()

if(is_code)
    # build name parameters
    if(NOT DEFINED operative_system)
        message(FATAL_ERROR "Operating system parameter not defined")
    endif()

    if(NOT DEFINED operative_system_version)
        message(FATAL_ERROR "Operating system version parameter not defined")
    endif()

    if(NOT DEFINED compiler)
        message(FATAL_ERROR "Compiler parameter not defined")
    endif()

    if(NOT DEFINED compiler_version)
        message(FATAL_ERROR "Compiler version parameter not defined")
    endif()

    if(NOT DEFINED architecture)
        message(FATAL_ERROR "Architecture parameter not defined")
    endif()
endif()

# set the time for the nightly
set(CTEST_NIGHTLY_START_TIME "00:30:00 UTC")

# no limits for test output
set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 0)
set(CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE 0)

# set the site to the hostname. this shows up in the dashboard.
site_name(CURRENT_SITE)
set(SITE "${CURRENT_SITE}")
set(CTEST_SITE "${CURRENT_SITE}")

# locate the system's temp directory
set(home_dir "$ENV{HOME}")
if(NOT EXISTS "${home_dir}")
    message(FATAL_ERROR "Cannot find the user's home directory.")
endif()

# project files to generate
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
if(WIN32)
    set(CTEST_CMAKE_GENERATOR "MSYS Makefiles")
endif()

# create the build name
set(build_name "${build_type}")
if(is_code)
    set(build_name "${operative_system}")
    set(build_name "${build_name}-${operative_system_version}")
    set(build_name "${build_name}-${architecture}")
    set(build_name "${build_name}-${compiler}-${compiler_version}")

    # compilation options
    if(NOT DEFINED number_of_cpus)
        set(number_of_cpus 1)
    endif()
endif()
set(CTEST_BUILD_NAME "${build_name}")

# output directories
set(workspace "${build_dir}/${model}/${product}/${CTEST_BUILD_NAME}")
set(CTEST_SOURCE_DIRECTORY "${workspace}/source")
set(CTEST_BINARY_DIRECTORY "${workspace}/build")

# setup make
find_program(make_command NAMES make)
if(NOT DEFINED make_command)
    message(FATAL_ERROR "make not found.")
endif()

# build target
if("${build_type}" STREQUAL "doxygen")
    set(CTEST_BUILD_TARGET "deploy_doxy")
elseif("${build_type}" STREQUAL "code")
    set(CTEST_BUILD_TARGET "package")
endif()

#
# ruby
#
find_program(CTEST_RUBY_COMMAND NAMES ruby)
if(NOT CTEST_RUBY_COMMAND)
    message(FATAL_ERROR "ruby not found.")
endif()

#
# git
#
find_program(CTEST_GIT_COMMAND NAMES git)
if(NOT CTEST_GIT_COMMAND)
    message(FATAL_ERROR "git not found.")
endif()

# get path to repository for current product
if(NOT DEFINED source_url)
    if("${product}" STREQUAL "dogen")
        set(source_url "git://github.com/DomainDrivenConsulting/dogen.git")
    else()
        message(FATAL_ERROR "Unsupported product: ${product}.")
    endif()
    set(perform_submit true)
else()
    # if we passed in a git url its because we're testing the ctest
    # script itself. there is no need to submit the build results.
    set(perform_submit false)
endif()

# clone only if we don't have a source directory
if(NOT EXISTS "${CTEST_SOURCE_DIRECTORY}")
    set(clone_args "clone ${source_url} ${CTEST_SOURCE_DIRECTORY}")
    set(CTEST_CHECKOUT_COMMAND "${CTEST_GIT_COMMAND} ${clone_args}")
endif()

#
# ssh
#
find_program(ssh_executable ssh)
if(ssh_executable)
    message(STATUS "Found ssh (${ssh_executable})...")
else()
    message(FATAL_ERROR "Could not find a valid ssh installation.")
endif()

find_program(scp_executable scp)
if(scp_executable)
    message(STATUS "Found scp (${scp_executable})...")
else()
    message(FATAL_ERROR "Could not find a valid ssh installation.")
endif()

# only run these for Nightly.
set(WITH_COVERAGE false)
set(WITH_MEMCHECK false)

# How long to wait between timed-out CTest submissions
set(submit_retry_delay 30)

# How many times to retry timed-out CTest submissions
set(submit_retry_count 10)

#
# Nightly
#
if(${CTEST_SCRIPT_ARG} MATCHES Nightly)
    # setup gcov
    find_program(CTEST_COVERAGE_COMMAND NAMES gcov-4.7 gcov)
    if(NOT CTEST_COVERAGE_COMMAND)
        message("gcov not found, disabling coverage.")
        set(WITH_COVERAGE false)
    else()
        message("Found gcov (${CTEST_COVERAGE_COMMAND})...")
        set(WITH_COVERAGE true)
    endif()

    # setup valgrind
    find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
    if(NOT CTEST_MEMORYCHECK_COMMAND)
        message("valgrind not found, disabling coverage.")
        set(WITH_MEMCHECK false)
    else()
        message("Found valgrind (${CTEST_MEMORYCHECK_COMMAND})...")
        set(WITH_MEMCHECK true)

        set(valgrind_options "--trace-children=yes")
        set(valgrind_options "${valgrind_options} --quiet")
        set(valgrind_options "${valgrind_options} --tool=memcheck")
        set(valgrind_options "${valgrind_options} --leak-check=full")
        set(valgrind_options "${valgrind_options} --show-reachable=yes")
        set(valgrind_options "${valgrind_options} --num-callers=50")
        set(valgrind_options "${valgrind_options} --demangle=yes")
        set(valgrind_options "${valgrind_options} --gen-suppressions=all")
        set(CTEST_MEMORYCHECK_COMMAND_OPTIONS ${valgrind_options})
        set(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE
            "${CTEST_SOURCE_DIRECTORY}/build/valgrind/${product}.supp")
    endif()
endif()

# configure command
set(tmp "${CMAKE_COMMAND} \"-G${CTEST_CMAKE_GENERATOR}\"")
if("${build_type}" STREQUAL "code")
    if(${model} MATCHES Nightly)
        set(CTEST_BUILD_CONFIGURATION "Profiling")
        set(CTEST_BUILD_OPTIONS "-DWITH_DEBUG=on")
        set(CTEST_BUILD_OPTIONS "${CTEST_BUILD_OPTIONS} -DWITH_PROFILING=on")
    endif()

    # -DCMAKE_MODEL:STRING=${CTEST_BUILD_CONFIGURATION}
    # -DWITH_TESTING:BOOL=ON
    set(tmp "${tmp} ${CTEST_BUILD_OPTIONS}")
endif()
set(tmp "${tmp} \"${CTEST_SOURCE_DIRECTORY}\"")
set(CTEST_CONFIGURE_COMMAND "${tmp}")

# build command
set(tmp "${make_command} ${CTEST_BUILD_TARGET} VERBOSE=1")
set(CTEST_BUILD_COMMAND "${tmp}")

#
# Continuous
#
if(${model} MATCHES Continuous)
    set(build_number 0)

    while(${CTEST_ELAPSED_TIME} LESS 86000)
        # determine whether to make a clean build or not
        math(EXPR is_clean "${build_number} % 5")
        if(is_code AND ${is_clean} EQUAL 0)
            message("Performing a clean build: ${build_number}")
            set(CTEST_BUILD_NAME "${build_name}-clean")
            ctest_empty_binary_directory(${CTEST_BINARY_DIRECTORY})
        elseif(is_code)
            message("Performing an incremental build: ${build_number}")
            set(CTEST_BUILD_NAME "${build_name}-inc")
        else()
            message("Performing a build: ${build_number}")
        endif()

        set(START_TIME ${CTEST_ELAPSED_TIME})
        message("Starting continuous build at ${START_TIME}")
        ctest_start(Continuous)

        # update files from git
        ctest_update(BUILD ${CTEST_SOURCE_DIRECTORY} RETURN_VALUE git_result)
        set(git_retries 0)
        while(git_result LESS 0 AND git_retries LESS 10)
            message("Failed to update source code from " ${source_url})
            message("Problems checking out from git repository."
            " Status: ${git_result}. Retries: ${git_retries}")
            ctest_sleep(60)
            math(EXPR git_retries "${git_retries} + 1")
            ctest_update(BUILD ${CTEST_SOURCE_DIRECTORY} RETURN_VALUE git_result)
        endwhile()

        if(git_result LESS 0)
            message(FATAL_ERROR "Failed to update files from git.")
        endif()
        message("Successfully updated source code from ${source_url}."
            " Read ${git_result} new files.")

        # get the hash of the top commit
        execute_process(COMMAND ${CTEST_GIT_COMMAND} rev-list -n 1 HEAD
            WORKING_DIRECTORY ${CTEST_SOURCE_DIRECTORY}
            ERROR_VARIABLE git_error
            OUTPUT_VARIABLE new_hash
            RESULT_VARIABLE ret_var
            OUTPUT_STRIP_TRAILING_WHITESPACE)

        # if its different from last one, do a build
        if("${old_hash}" STREQUAL "${new_hash}")
            message("No changes detected at ${CTEST_ELAPSED_TIME}")
            ctest_sleep(60)
        else()
            math(EXPR build_number "${build_number} + 1")
            message("Changes detected, performing build: ${build_number}")

            # run clone on first iteration only
            set(CTEST_CHECKOUT_COMMAND)

            # do a build
            include("${CTEST_SOURCE_DIRECTORY}/build/ctest/CTestConfig.cmake")
            set(stage_pkg_dir "${CTEST_BINARY_DIRECTORY}/stage/pkg")
            if("${build_type}" STREQUAL "code")
                # ensure the previous package directory is deleted
                # if any exists. this is because we may have changed
                # the naming convention of the package.
                file(REMOVE_RECURSE ${stage_pkg_dir})
                file(MAKE_DIRECTORY ${stage_pkg_dir})
            endif()

            ctest_configure(BUILD ${CTEST_BINARY_DIRECTORY})

            ctest_build(BUILD "${CTEST_BINARY_DIRECTORY}" APPEND)
            if("${build_type}" STREQUAL "code")
                ctest_test(BUILD "${CTEST_BINARY_DIRECTORY}"
                    PARALLEL_LEVEL ${number_of_cpus})

                if(is_code)
                    file(GLOB all_pkgs RELATIVE
                        "${stage_pkg_dir}"
                        "${stage_pkg_dir}/*")

                    foreach(local_pkg_file ${all_pkgs})
                        message("Uploading package: ${local_pkg_file}")
                        set(local_pkg_path "${stage_pkg_dir}/${local_pkg_file}")
                        # execute_process(
                        #     COMMAND ${CTEST_RUBY_COMMAND}
                        #     $ENV{PFH_LOCATION}/scripts/upload.rb
                        #     ${model} ${CURRENT_SITE} ${product} incoming
                        #     ${local_pkg_path}
                        #     WORKING_DIRECTORY ${CTEST_SOURCE_DIRECTORY})
                    endforeach()
                elseif()
                    message("Not uploading package: ${local_pkg_file} ${no_packages}")
                endif()

                if(WITH_COVERAGE AND CTEST_COVERAGE_COMMAND)
                    ctest_coverage()
                endif()

                if(WITH_MEMCHECK AND CTEST_MEMORYCHECK_COMMAND)
                    ctest_memcheck(PARALLEL_LEVEL ${number_of_cpus})
                endif()
            endif()

            if(perform_submit)
                ctest_submit(RETRY_COUNT ${submit_retry_count}
                    RETRY_DELAY ${submit_retry_delay})
            endif()
        endif()
        set(old_hash ${new_hash})
    endwhile()
    message("Continuous build finished at ${CTEST_ELAPSED_TIME}")
else()
    #
    # Nightly and Experimental
    #
    # ensure we start from a known state
    ctest_empty_binary_directory(${CTEST_BINARY_DIRECTORY})

    ctest_start("${model}")

    ctest_update(BUILD ${CTEST_SOURCE_DIRECTORY} RETURN_VALUE git_result)
    set(git_retries 0)
    while(git_result LESS 0 AND git_retries LESS 10)
        message("Failed to update source code from " ${source_url})
        message("Problems checking out from git repository."
            " Status: ${git_result}. Retries: ${git_retries}")
        ctest_sleep(60)
        math(EXPR git_retries "${git_retries} + 1")
        ctest_update(BUILD ${CTEST_SOURCE_DIRECTORY} RETURN_VALUE git_result)
    endwhile()

    if(git_result LESS 0)
        message(FATAL_ERROR "Failed to update files from git, giving up.")
    endif()
    message("Successfully updated source code from ${source_url}."
        " Read ${git_result} new files.")

    include("${CTEST_SOURCE_DIRECTORY}/build/ctest/CTestConfig.cmake")
    set(stage_pkg_dir "${CTEST_BINARY_DIRECTORY}/stage/pkg")
    if("${build_type}" STREQUAL "code")
        # ensure the previous package directory is deleted
        # if any exists. this is because we may have changed
        # the naming convention of the package.
        file(REMOVE_RECURSE ${stage_pkg_dir})
        file(MAKE_DIRECTORY ${stage_pkg_dir})
    endif()

    ctest_configure(BUILD ${CTEST_BINARY_DIRECTORY})

    ctest_build(BUILD "${CTEST_BINARY_DIRECTORY}" APPEND)
    if("${build_type}" STREQUAL "code")
        ctest_test(BUILD "${CTEST_BINARY_DIRECTORY}"
            PARALLEL_LEVEL ${number_of_cpus})

        if(is_code)
            file(GLOB all_pkgs RELATIVE
                "${stage_pkg_dir}"
                "${stage_pkg_dir}/*")

            foreach(local_pkg_file ${all_pkgs})
                message("Uploading package: ${local_pkg_file}")
                set(local_pkg_path "${stage_pkg_dir}/${local_pkg_file}")

                # execute_process(
                #     COMMAND ${CTEST_RUBY_COMMAND}
                #     $ENV{PFH_LOCATION}/scripts/upload.rb
                #     ${model} ${CURRENT_SITE} ${product} incoming
                #     ${local_pkg_path}
                #     WORKING_DIRECTORY ${CTEST_SOURCE_DIRECTORY})
            endforeach()
        elseif()
            message("Not uploading package: ${local_pkg_file} ${no_packages}")
        endif()

        if(WITH_COVERAGE)
            ctest_coverage()
        endif()
        if(WITH_MEMCHECK AND CTEST_MEMORYCHECK_COMMAND)
            ctest_memcheck(PARALLEL_LEVEL ${number_of_cpus})
        endif()
    endif()

    if(perform_submit)
        ctest_submit(RETRY_COUNT ${submit_retry_count}
            RETRY_DELAY ${submit_retry_delay})
    endif()
endif()
