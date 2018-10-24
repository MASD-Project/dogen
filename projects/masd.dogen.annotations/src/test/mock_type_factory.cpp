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
#include "masd.dogen.annotations/test/mock_type_factory.hpp"

namespace masd::dogen::annotations::test {

type mock_type_factory::containing_namespaces() const {
    type r;
    r.name().simple("containing_namespaces");
    r.name().qualified("containing_namespaces");
    r.archetype_location().backend("stitch");
    r.value_type(value_types::text);
    r.scope(scope_types::not_applicable);
    return r;
}

type mock_type_factory::copyright_notice() const {
    type r;
    r.name().simple("copyright_notice");
    r.name().qualified("copyright_notice");
    r.archetype_location().backend("formatters");
    r.value_type(value_types::text);
    r.scope(scope_types::not_applicable);
    return r;
}

type mock_type_factory::licence_name() const {
    type r;
    r.name().simple("licence_name");
    r.name().qualified("licence_name");
    r.archetype_location().backend("formatters");
    r.value_type(value_types::text);
    r.scope(scope_types::not_applicable);
    return r;
}

type mock_type_factory::create_comment() const {
    type r;
    r.name().simple("comment");
    r.name().qualified("yarn.dia.comment");
    r.archetype_location().backend("yarn.dia");
    r.value_type(value_types::text);
    r.scope(scope_types::not_applicable);
    return r;
}

std::list<type> mock_type_factory::make_canned_types() const {
    std::list<type> r;
    r.push_back(create_comment());
    r.push_back(licence_name());
    r.push_back(copyright_notice());
    r.push_back(containing_namespaces());
    return r;
}

type mock_type_factory::make_type(const std::string n, value_types vt) const {
    type r;
    r.name().simple(n);
    r.name().qualified(n);
    r.value_type(vt);
    r.scope(scope_types::any);
    return r;
}

}
