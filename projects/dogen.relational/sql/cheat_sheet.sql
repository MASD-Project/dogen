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


select "TIMESTAMP", "RUN_ID", "VERSION", "ACTIVITY", "LOGGING_IMPACT", "TRACING_IMPACT",
cast("PAYLOAD" as varchar(50)), (CASE WHEN "EVENT_TYPE" = 1 THEN  'START' ELSE 'END' END) as "EVENT_TYPE"
from "RUN_EVENT" order by "TIMESTAMP";

--
-- Runs by time
--
select "TIMESTAMP", "RUN_ID", "ACTIVITY"
from "RUN_EVENT"
where "EVENT_TYPE" = 1
order by "TIMESTAMP";

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
where "PARENT_TRANSFORM" = 'cb25de94-fe06-4ec0-bb8d-eb7928066221' --
order by "TIMESTAMP" asc;

select jsonb_pretty("PAYLOAD")
from "TRANSFORM_EVENT"
where "TRANSFORM_INSTANCE_ID" = 'd090c622-9c55-4bac-ac97-61ed2e35f7d1'
and "EVENT_TYPE" = 2;


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
where "TRANSFORM_INSTANCE_ID" = '27b9f4eb-a655-4fbf-83d7-c158ac8475b9' and "EVENT_TYPE" = 2
order by "TIMESTAMP" asc;


--
-- Get IDs for objects in diagram
--
select object->'id'::text "ID", object->'type'::text "TYPE"
from (
     select jsonb_array_elements("PAYLOAD"->'layers'->0->'objects') as object
     from "TRANSFORM_EVENT"
     where "TRANSFORM_INSTANCE_ID" = '954a4410-1481-48c7-8a11-5e0608ba3cff' and "EVENT_TYPE" = 1
     and object->'id'::text = 'O0'
     order by "TIMESTAMP" asc
) as foo;


select jsonb_array_elements("PAYLOAD"->'layers'->0->'objects')::text
from "TRANSFORM_EVENT"
where "TRANSFORM_INSTANCE_ID" = '954a4410-1481-48c7-8a11-5e0608ba3cff' and "EVENT_TYPE" = 1
order by "TIMESTAMP" asc;


--
-- Get logging
--
select * from "LOG_EVENT" limit 30;

-- log for a specific run
select * from "LOG_EVENT"
where "RUN_ID" = 'd9dc87fe-6ce2-4259-b780-b1b9c9d33dd9'
order by "TIMESTAMP" asc limit 20;



--
-- Log events for an interval
--
select "TIMESTAMP", "COMPONENT",  "SEVERITY", cast("MESSAGE" as varchar(100))
from "LOG_EVENT"
where "TIMESTAMP" between '2019-12-14 20:44:29.017696' and '2019-12-14 20:44:32.266955'
and "RUN_ID" = 'd92263a0-4965-4a3e-803d-1e2851e96fcc'
and "COMPONENT" like '%injection%'
order by "TIMESTAMP";

--
--
--
select "TIMESTAMP"
from "TRANSFORM_EVENT"
where  "TRANSFORM_INSTANCE_ID" = '954a4410-1481-48c7-8a11-5e0608ba3cff';


select * from runs();
select * from last_run();
select last_run_id();
select * from target_for_run() where "FILE_NAME" like '%generation%';
select * from peek_log('4a1e5d10-4179-4e42-b3d1-e31e01baa21d', 10);
select * from transforms_for_run_id('b65d66c7-9952-43c8-a59a-20bcb413c390');
select * from peek_log('5ca899c4-6d48-4a07-ae93-d43cc0d9ac9b', 10);
select * from target_for_run();
select * from configuration_for_run_id('5ca899c4-6d48-4a07-ae93-d43cc0d9ac9b');

select "RUN_ID", jsonb_pretty(substring("MESSAGE", 25)::jsonb->2) file_name
from "LOG_EVENT"
where "COMPONENT" = 'main' and "SEVERITY" = 'INFO';
and "RUN_ID" = '4a1e5d10-4179-4e42-b3d1-e31e01baa21d';


select jsonb_pretty(substring("MESSAGE", 25)::jsonb) "CONFIG"
from "LOG_EVENT"
where "COMPONENT" = 'main' and "SEVERITY" = 'INFO';


select "TRANSFORM_ID", "PAYLOAD"->>'__type__' "PAYLOAD_TYPE",
cast(
    jsonb_array_elements(
        "PAYLOAD"->'structural_elements'->'objects')->1->'data'->'data'->'__parent_0__'->'name'->'qualified'->'dot'
    as varchar(1000)
)
from "TRANSFORM_EVENT"
where "TRANSFORM_INSTANCE_ID" = 'ce9cb092-6cc4-4e2f-9c61-11311f9bbfb0';
