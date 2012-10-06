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
 * @brief Currency as defined in ISO 4127.
 */
create table kitanda.currency (
    numeric_code int not null,
    name varchar(150) not null,
    alpha_code char(3) not null,
    decimal_places int not null,

    snapshot kitanda.snapshot_type not null,
    latest boolean not null,
    timestamp kitanda.timestamp_type not null,

    constraint currency_alpha_code_uq
        unique (alpha_code, snapshot),
    primary key (numeric_code, snapshot)
);

-- build user has all rights
grant all privileges on table kitanda.currency to build;