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

-- drop currency production sprocs.
drop function if exists kitanda.currency_load(
     v_numeric_code kitanda.currency.numeric_code%type);
drop function if exists kitanda.currency_save(
    v_numeric_code kitanda.currency.numeric_code%type,
    v_name kitanda.currency.name%type,
    v_alpha_code kitanda.currency.alpha_code%type,
    v_decimal_places kitanda.currency.decimal_places%type,
    v_snapshot kitanda.currency.snapshot%type);
drop function if exists kitanda.currency_delete(
    v_numeric_code kitanda.currency.numeric_code%type);
