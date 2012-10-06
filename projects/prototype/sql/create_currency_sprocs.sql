/* -*- sql-product: postgres; tab-width: 4; indent-tabs-mode: nil -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
set client_min_messages = ERROR;

/**
 * @brief Returns the latest revision of one or all currencies
 * in the currency table.
 *
 * @param v_numeric_code ISO 4127 currency code. If null, returns all
 * currencies.
 */
create or replace function kitanda.currency_load(
    v_numeric_code kitanda.currency.numeric_code%type)
returns setof kitanda.currency as
$body$
begin
    if (v_numeric_code is null) then
        return query select * from kitanda.currency where latest = true;
    else
        return query
            select * from kitanda.currency
            where v_numeric_code = numeric_code and latest = true;
    end if;

    return;
end
$body$
language 'plpgsql';

/**
 * @brief Create new currency.
 */
create or replace function kitanda.currency_save(
    v_numeric_code kitanda.currency.numeric_code%type,
    v_name kitanda.currency.name%type,
    v_alpha_code kitanda.currency.alpha_code%type,
    v_decimal_places kitanda.currency.decimal_places%type,
    v_snapshot kitanda.currency.snapshot%type)
returns int as
$body$
declare
    current_snapshot kitanda.currency.snapshot%type;
    current_ts kitanda.currency.timestamp%type;
begin
    select into current_snapshot snapshot
    from kitanda.currency
    where numeric_code = v_numeric_code and latest = true;

    if current_snapshot is null then
        current_snapshot := 0;
    end if;

    if current_snapshot != v_snapshot then
        raise exception 'currency_save: record is not up-to-date.';
    end if;

    if current_snapshot != 0 then
        update kitanda.currency
        set latest = false
        where numeric_code = v_numeric_code and
            snapshot = v_snapshot;
    end if;

    current_ts := cast(extract(epoch from now()) as integer);
    insert into kitanda.currency (numeric_code, name, alpha_code,
        decimal_places, snapshot, latest, timestamp)
    values (v_numeric_code, v_name, v_alpha_code, v_decimal_places,
        v_snapshot + 1, true, current_ts);
    return current_ts;
end
$body$
language 'plpgsql';

/**
 * @brief Deletes countries from the database.
 *
 * @param v_numeric_code ISO 4127 currency code. If non-null, deletes the
 * currency represented by that code; If null, deletes all countries.
 */
create or replace function kitanda.currency_delete(
    v_numeric_code kitanda.currency.numeric_code%type)
returns void as
$body$
begin
    delete from kitanda.currency
    where numeric_code = coalesce (v_numeric_code, numeric_code);
    return;
end
$body$
language 'plpgsql';
