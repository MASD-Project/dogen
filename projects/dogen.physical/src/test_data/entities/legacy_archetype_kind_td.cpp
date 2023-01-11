/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.physical/test_data/entities/legacy_archetype_kind_td.hpp"

namespace dogen::physical::entities {

legacy_archetype_kind_generator::legacy_archetype_kind_generator() : position_(0) { }
void legacy_archetype_kind_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<legacy_archetype_kind>(position % 14);
}

legacy_archetype_kind_generator::result_type
legacy_archetype_kind_generator::create(const unsigned int  position) {
    result_type r;
    legacy_archetype_kind_generator::populate(position, r);
    return r;
}

legacy_archetype_kind_generator::result_type
legacy_archetype_kind_generator::operator()() {
    return create(position_++);
}

}
