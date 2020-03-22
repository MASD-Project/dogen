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
#include "dogen.m2t.cpp/types/transforms/test_data/date_helper.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/helper_properties.hpp"

namespace dogen::m2t::cpp::transforms::test_data {

std::string date_helper::id() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string date_helper::family() const {
    static std::string r("BoostDate");
    return r;
}

std::list<std::string>
date_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype(),
        traits::primitive_implementation_archetype()
    });
    return r;
}

std::list<std::string>
date_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet()
    });
    return r;
}

std::string date_helper::helper_name() const {
    static std::string r("date_helper");
    return r;
}

bool date_helper::is_enabled(const assistant& /*a*/,
    const formattables::helper_properties& /*hp*/) const {
    return true;
}

void date_helper::
apply(assistant& a, const formattables::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
a.stream() << std::endl;
a.stream() << qn << std::endl;
a.stream() << "create_" << ident << "(const unsigned int position) {" << std::endl;
a.stream() << "    const auto day(static_cast<unsigned short>(1 + (position % 27)));" << std::endl;
a.stream() << "    boost::gregorian::date r(2002, 2, day);" << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
}
}
