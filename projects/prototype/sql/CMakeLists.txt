# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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

# don't forget to set PGPASSWORD (or .pgpass) before attempting to run
# these targets.
set(psql_binary "psql")
set(username "postgres")
set(database "sanzala")
set(sql_dir "${CMAKE_SOURCE_DIR}/projects/prototype/sql")
set(hostname "localhost")
set(credentials -h ${hostname} -U ${username} -w --dbname ${database} -X)
set(cmd ${psql_binary} ${credentials} -v ON_ERROR_STOP=1)

message(STATUS "running against database ${database}")

#
# drop
#
add_custom_target(drop_test_run_all_unit_tests_sproc
    ${cmd} -f${sql_dir}/drop_test_run_all_unit_tests_sproc.sql)

add_custom_target(drop_currency_test_sprocs
    ${cmd} -f${sql_dir}/drop_currency_test_sprocs.sql)
add_dependencies(drop_currency_test_sprocs drop_test_run_all_unit_tests_sproc)

add_custom_target(drop_currency_sprocs
    ${cmd} -f${sql_dir}/drop_currency_sprocs.sql)
add_dependencies(drop_currency_sprocs drop_currency_test_sprocs)

add_custom_target(drop_currency_table
    ${cmd} -f${sql_dir}/drop_currency_table.sql)
add_dependencies(drop_currency_table drop_currency_sprocs)

add_custom_target(drop_domains ${cmd} -f${sql_dir}/drop_domains.sql)
add_dependencies(drop_domains drop_currency_table)

add_custom_target(drop_schema ${cmd} -f${sql_dir}/drop_schema.sql)
add_dependencies(drop_schema drop_domains)

#
# create
#
add_custom_target(create_schema ${cmd} -f${sql_dir}/create_schema.sql)

add_custom_target(create_domains ${cmd} -f${sql_dir}/create_domains.sql)
add_dependencies(create_domains create_schema)

add_custom_target(create_currency_table
    ${cmd} -f${sql_dir}/create_currency_table.sql)
add_dependencies(create_currency_table create_domains)

add_custom_target(create_currency_sprocs
    ${cmd} -f${sql_dir}/create_currency_sprocs.sql)
add_dependencies(create_currency_sprocs create_currency_table)

add_custom_target(create_currency_test_sprocs
    ${cmd} -f${sql_dir}/create_currency_test_sprocs.sql)
add_dependencies(create_currency_test_sprocs create_currency_sprocs)

add_custom_target(create_test_run_all_unit_tests_sproc
    ${cmd} -f${sql_dir}/create_test_run_all_unit_tests_sproc.sql)
add_dependencies(create_test_run_all_unit_tests_sproc
    create_currency_test_sprocs)

#
# replace
#
add_custom_target(replace_currency_sprocs
    ${cmd} -f${sql_dir}/create_currency_sprocs.sql)

add_custom_target(replace_currency_test_sprocs
    ${cmd} -f${sql_dir}/create_currency_test_sprocs.sql)

add_custom_target(replace_test_run_all_unit_tests_sproc
    ${cmd} -f${sql_dir}/create_test_run_all_unit_tests_sproc.sql)

#
# unit tests
#
add_custom_target(run_all_unit_tests
    ${cmd} -f${sql_dir}/run_all_unit_tests.sql)
