/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#include "dogen/quilt.cpp/test_data/formattables/local_enablement_configuration_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::optional<bool>
create_boost_optional_bool(unsigned int position) {
    boost::optional<bool> r(
        create_bool(position));
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

local_enablement_configuration_generator::local_enablement_configuration_generator() : position_(0) { }

void local_enablement_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_boost_optional_bool(position + 0));
    v.supported(create_bool(position + 1));
}

local_enablement_configuration_generator::result_type
local_enablement_configuration_generator::create(const unsigned int position) {
    local_enablement_configuration r;
    local_enablement_configuration_generator::populate(position, r);
    return r;
}

local_enablement_configuration_generator::result_type*
local_enablement_configuration_generator::create_ptr(const unsigned int position) {
    local_enablement_configuration* p = new local_enablement_configuration();
    local_enablement_configuration_generator::populate(position, *p);
    return p;
}

local_enablement_configuration_generator::result_type
local_enablement_configuration_generator::operator()() {
    return create(position_++);
}

} } } }
