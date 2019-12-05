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

-- Official docs: http://www.postgresql.org/docs/9.3/static/app-psql.html
-- Unofficial docs: http://robots.thoughtbot.com/improving-the-command-line-postgres-experience

-- Don't display the "helpful" message on startup.
\set QUIET 1
\pset null '[NULL]'

-- http://www.postgresql.org/docs/9.3/static/app-psql.html#APP-PSQL-PROMPTING
\set PROMPT1 '%[%033[1m%]%M %n@%/%R%[%033[0m%]%# '
-- PROMPT2 is printed when the prompt expects more input, like when you type
-- SELECT * FROM<enter>. %R shows what type of input it expects.
\set PROMPT2 '[more] %R > '

-- Show how long each query takes to execute
\timing

-- Use best available output format
\x auto
\set VERBOSITY verbose
\set HISTFILE ~/.psql_history- :DBNAME
\set HISTCONTROL ignoredups
\set COMP_KEYWORD_CASE upper
\unset QUIET

-- psql can't check for a file's existence, so we'll provide an empty local
-- file that users can override with their custom dotfiles. To set your own
-- personal settings, place your own file in ~/.psqlrc.local
\i ~/.psqlrc.local

\set PROMPT1 '(%n@%M:%>) [%/] > '
\set PROMPT2 ''

-- Put this alias in .bashrc to turn on session logging
-- alias psql='psql -eL /tmp/psql.log'
\timing on
\setenv LESS -imx4F
\x auto

-- Put a space in front of queries you don't want to save
\set HISTCONTROL ignorespace
\set HISTFILE ~/.psql_history- :DBNAME
\set HISTSIZE 20000
-- Huge history file -- ctrl-r is useful
\pset null '[NULL]'
-- Don't exit with ctrl-d unless you press it 5 times
\set IGNOREEOF 5

\set QUIET 1

-- Errors are ignored in interactive sessions,
-- and not when reading script files.
\set ON_ERROR_ROLLBACK interactive

-- To have all queries display query times.
\timing

-- Verbose error reports.
\set VERBOSITY verbose

-- Use table format (with headers across the top) by default,
-- but switch to expanded table format when there's a lot of data,
-- which makes it much easier to read.
\x auto

-- Use a separate history file per-database.
\set HISTFILE ~/.psql_history- :DBNAME

-- If a command is run more than once in a row,
-- only store it once in the history.
\set HISTCONTROL ignoredups

-- By default, NULL displays as an empty space. Is it actually an empty
-- string, or is it null? This makes that distinction visible.
\pset null '(null)'

\unset QUIET
