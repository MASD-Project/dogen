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

/*
 * Random selection of useful postgres commands and other useful SQL.
 */

-- list of tables
\dt

-- info on a table
\d TBL

-- list of functions:
\df

-- list of functions with text
\df+

-- echo the search path:
show SEARCH_PATH;

-- limit select
select * from country limit 20;

-- reconnect to db
\c [dbname] [dbuser]

-- use a different db
\d [dbname]

-- display results vertically
\x
\G

-- execute a shell command
\! ls

-- include file as if it was typed in
\i [filename]

-- list all databases
\l

-- list all schemas
\dn

-- server version
select version();

-- time now
select now();

-- current user, database
select current_user(), current_database();

-- running stored procs from psql
select kitanda.test_currency_complete_generator();

-- extract element from array
select jsonb_pretty(jsonb_array_elements("CONFIGURATION"->'all')->'facet') from "RUN";

--
select jsonb_pretty(jsonb_array_elements("CONFIGURATION"->'all')) from "RUN";

--
select jsonb_pretty("CONFIGURATION"->'all'->0->'facet') from "RUN";

--
select jsonb_pretty("CONFIGURATION") from "RUN";

--
with test as (select distinct (jsonb_array_elements("CONFIGURATION"->'all')->'archetype')::text as archetype from "RUN") select * from test where archetype like '%cpp%'

--
-- get all run events
--
select "TIMESTAMP", "RUN_ID", cast("PAYLOAD" as varchar(20)),
(CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END) as "EVENT_TYPE"
from "RUN_EVENT"
order by "TIMESTAMP";
