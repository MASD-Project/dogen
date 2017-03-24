# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(odb_files "")
file(GLOB_RECURSE odb_files RELATIVE
   "${CMAKE_CURRENT_SOURCE_DIR}/"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")
set(files ${files} ${odb_files})

add_library(northwind STATIC ${files})
set_target_properties(northwind PROPERTIES
    OUTPUT_NAME dogen.northwind)

install(TARGETS northwind ARCHIVE DESTINATION lib COMPONENT libraries)
#
# ODB Targets
#
add_custom_target(odb_northwind)

if (NOT ODB_EXECUTABLE)
    message(FATAL "ODB Executable not defined.")
endif()

if (NOT ODB_INCLUDE_DIRS)
    message(FATAL "ODB include directories not defined.")
endif()

get_directory_property(dirs INCLUDE_DIRECTORIES)
set(global_includes "")
foreach(dir in ${dirs})
    set(global_includes ${global_includes} -I ${dir})
endforeach()

add_custom_target(odb_northwind_order_details
    COMMENT "ODB order_details"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/order_details_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/order_details.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_order_details)

add_custom_target(odb_northwind_categories
    COMMENT "ODB categories"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/categories_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/categories.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_categories)

add_custom_target(odb_northwind_shippers
    COMMENT "ODB shippers"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/shippers_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/shippers.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_shippers)

add_custom_target(odb_northwind_suppliers
    COMMENT "ODB suppliers"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/suppliers_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/suppliers.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_suppliers)

add_custom_target(odb_northwind_orders
    COMMENT "ODB orders"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/orders_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/orders.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_orders)

add_custom_target(odb_northwind_products
    COMMENT "ODB products"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/products_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/products.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_products)

add_custom_target(odb_northwind_order_details_key
    COMMENT "ODB order_details_key"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/order_details_key_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/order_details_key.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_order_details_key)

add_custom_target(odb_northwind_customers
    COMMENT "ODB customers"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/customers_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/customers.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_customers)

add_custom_target(odb_northwind_employees
    COMMENT "ODB employees"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${ODB_EXECUTABLE}
        --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
        --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/odb
        --odb-epilogue '#include "dogen/test_models/northwind/odb/employees_pragmas.hpp"'
        -I ${ODB_INCLUDE_DIRS} ${global_includes}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen/test_models/northwind/types/employees.hpp
    VERBATIM
)
add_dependencies(odb_northwind odb_northwind_employees)
