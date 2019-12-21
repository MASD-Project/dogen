/* -*- sql-product: postgres; tab-width: 4; indent-tabs-mode: nil -*-
 *
 * Copyright (C) 2012-2019 Marco Craveiro <marco.craveiro@gmail.com>
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
 */

/**
 * Returns all of the runs available.
 */
create or replace function runs()
    returns table("VERSION" text, "TIMESTAMP" timestamp,
        "RUN_ID" text, "LOGGING_IMPACT" text, "TRACING_IMPACT"text)
as $$
    select "RUN_EVENT"."VERSION", "RUN_EVENT"."TIMESTAMP", "RUN_EVENT"."RUN_ID",
        "RUN_EVENT"."LOGGING_IMPACT", "RUN_EVENT"."TRACING_IMPACT"
        from "RUN_EVENT"
        where "EVENT_TYPE" = 1
        order by "TIMESTAMP" desc;
$$ language 'sql';

/**
 * Returns details of the last run.
 */
create or replace function last_run()
    returns table("VERSION" text, "TIMESTAMP" timestamp,
        "RUN_ID" text, "LOGGING_IMPACT" text, "TRACING_IMPACT"text)
as $$
    select "RUN_EVENT"."VERSION", "RUN_EVENT"."TIMESTAMP", "RUN_EVENT"."RUN_ID",
        "RUN_EVENT"."LOGGING_IMPACT", "RUN_EVENT"."TRACING_IMPACT"
        from "RUN_EVENT"
        where "EVENT_TYPE" = 1
        order by "TIMESTAMP" desc limit 1;
$$ language 'sql';

/**
 * Returns the run_id of the last session.
 */
create or replace function last_run_id()
    returns text as $$
    select "RUN_ID" from last_run();
$$ language 'sql';

/**
 * Returns the top few lines of a log for a given run.
 */
create or replace function peek_log(in p_run_id text, in p_how_many int)
    returns setof "LOG_EVENT" as $$
    select *
    from "LOG_EVENT"
    where "RUN_ID" = p_run_id
    order by "TIMESTAMP" asc limit p_how_many;
$$ language 'sql';

/*
 *
 */
create or replace function get_configuration(in p_run_id text)
    returns setof TEXT as $$
begin
    return query select "MESSAGE"
    from "LOG_EVENT"
    where "COMPONENT" = 'main' and "RUN_ID" = p_run_id

    and "MESSAGE" like 'Command line arguments: %';
end;
$$ language 'plpgsql';
