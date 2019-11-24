/* -*- sql-product: postgres; tab-width: 4; indent-tabs-mode: nil -*-
*
* Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*/
-- stop annoying echo.
\set QUIET 1

/**
 * display table sizes
 */
\set rtsize '(select table_schema, table_name, pg_relation_size( quote_ident( table_schema ) || \'.\' || quote_ident( table_name ) ) as size, pg_total_relation_size( quote_ident( table_schema ) || \'.\' || quote_ident( table_name ) ) as total_size  from information_schema.tables where table_type = \'BASE TABLE\' and table_schema not in (\'information_schema\', \'pg_catalog\') order by pg_relation_size( quote_ident( table_schema ) || \'.\' || quote_ident( table_name ) ) desc, table_schema, table_name)'
\set tsize '(select table_schema, table_name, pg_size_pretty(size) as size, pg_size_pretty(total_size) as total_size from (:rtsize) x order by x.size desc, x.total_size desc, table_schema, table_name)'

/**
 * useful run table management
 */
\set selccy '(select * from "DOGEN"."RUN")'
\set delccy '(delete from "DOGEN"."RUN")'

-- display null with brackets
\pset null '[null]'

-- informative prompt
\set PROMPT1 '[%n@%M:%> (%`date +%H:%M:%S`) %/ %x]$ '
\set PROMPT2 ''

-- one history file per database, per host.
\set HISTFILE ~/.psql_history- :HOST - :DBNAME

-- history size.
\set HISTSIZE 2000

-- report on how long the query took.
\timing

-- set the dogen schema on the search path
set SEARCH_PATH to "DOGEN", "$user", "public";

-- do not auto-commit
-- disabled for the moment as this means we have to commit even on selects!
-- \set AUTOCOMMIT OFF

\unset QUIET
