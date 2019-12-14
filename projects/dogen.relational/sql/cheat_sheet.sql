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

select "TIMESTAMP", "RUN_ID", "VERSION", "ACTIVITY", "LOGGING_IMPACT", "TRACING_IMPACT", cast("PAYLOAD" as varchar(20)), (CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END) as "EVENT_TYPE" from "RUN_EVENT" order by "TIMESTAMP";

--
-- Runs by time
--
select "TIMESTAMP", "RUN_ID", "ACTIVITY" from "RUN_EVENT" where "EVENT_TYPE" = 1 order by "TIMESTAMP";

--
-- All transforms in a run
--
select "TIMESTAMP", "TRANSFORM_ID", (CASE WHEN "TRANSFORM_TYPE" = 1 THEN  'CHAIN' ELSE 'LEAF' END) "TRANSFORM_TYPE",
(CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END), "PARENT_TRANSFORM", "TRANSFORM_INSTANCE_ID",
cast("PAYLOAD" as varchar(20)), "PAYLOAD"->'__type__' "PAYLOAD_TYPE"
from "TRANSFORM_EVENT"
where "RUN_ID" = 'd92263a0-4965-4a3e-803d-1e2851e96fcc'
order by "TIMESTAMP" asc;

--
-- Top-level transforms in a run
--
select "TIMESTAMP", "TRANSFORM_ID", (CASE WHEN "TRANSFORM_TYPE" = 1 THEN  'CHAIN' ELSE 'LEAF' END) "TRANSFORM_TYPE",
(CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END), "PARENT_TRANSFORM", "TRANSFORM_INSTANCE_ID",
cast("PAYLOAD" as varchar(20)), "PAYLOAD"->'__type__' "PAYLOAD_TYPE"
from "TRANSFORM_EVENT"
where "RUN_ID" = 'd92263a0-4965-4a3e-803d-1e2851e96fcc' and coalesce("PARENT_TRANSFORM", '') = ''
order by "TIMESTAMP" asc;

--
-- Transforms by parents
--
select "TIMESTAMP", "TRANSFORM_ID", (CASE WHEN "TRANSFORM_TYPE" = 1 THEN  'CHAIN' ELSE 'LEAF' END) "TRANSFORM_TYPE",
(CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END), "PARENT_TRANSFORM", "TRANSFORM_INSTANCE_ID",
cast("PAYLOAD" as varchar(20)), "PAYLOAD"->'__type__' "PAYLOAD_TYPE"
from "TRANSFORM_EVENT"
where "PARENT_TRANSFORM" = 'cb25de94-fe06-4ec0-bb8d-eb7928066221'
order by "TIMESTAMP" asc;

--
-- Navigating into transforms
--
select "TIMESTAMP", "TRANSFORM_ID", (CASE WHEN "TRANSFORM_TYPE" = 1 THEN  'CHAIN' ELSE 'LEAF' END) "TRANSFORM_TYPE",
(CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END), "PARENT_TRANSFORM", "TRANSFORM_INSTANCE_ID",
cast("PAYLOAD" as varchar(20)), "PAYLOAD"->'__type__' "PAYLOAD_TYPE"
from "TRANSFORM_EVENT"
where "PARENT_TRANSFORM" = '9b9032d1-edd9-4f34-ac2b-4f345ae5019f'
order by "TIMESTAMP" asc;

--
-- Get JSONB for dia diagram
--
select "TIMESTAMP", "TRANSFORM_ID", (CASE WHEN "TRANSFORM_TYPE" = 1 THEN  'CHAIN' ELSE 'LEAF' END) "TRANSFORM_TYPE",
(CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END) "EVENT_TYPE",
"PARENT_TRANSFORM", "TRANSFORM_INSTANCE_ID", jsonb_pretty("PAYLOAD"),
"PAYLOAD"->'__type__' "PAYLOAD_TYPE"
from "TRANSFORM_EVENT"
where "TRANSFORM_INSTANCE_ID" = 'b996c91c-de1a-4bc0-9f97-504cb89232bf' and "EVENT_TYPE" = 1
order by "TIMESTAMP" asc;


--
-- Get IDs for objects in diagram
--
select crap->'id'::text "ID", crap->'type'::text "TYPE"
from (
     select jsonb_array_elements("PAYLOAD"->'layers'->0->'objects') as crap
     from "TRANSFORM_EVENT"
     where "TRANSFORM_INSTANCE_ID" = 'b996c91c-de1a-4bc0-9f97-504cb89232bf' and "EVENT_TYPE" = 1
     order by "TIMESTAMP" asc
) as foo;

--
-- Get logging
--
select * from "LOG_EVENT" limit 30;

--
-- Log events for an interval
--
select "TIMESTAMP", "COMPONENT",  "SEVERITY", cast("MESSAGE" as varchar(100))
from "LOG_EVENT"
where "TIMESTAMP" between ' 2019-12-14 20:44:07.77754' and '2019-12-14 20:45:11.619425'
and "RUN_ID" = 'd92263a0-4965-4a3e-803d-1e2851e96fcc'
order by "TIMESTAMP";
