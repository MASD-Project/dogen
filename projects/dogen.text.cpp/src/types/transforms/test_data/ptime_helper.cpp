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
#include "dogen.text.cpp/types/transforms/test_data/ptime_helper.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::cpp::transforms::test_data {

std::string ptime_helper::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string ptime_helper::family() const {
    static std::string r("BoostPTime");
    return r;
}

std::list<std::string>
ptime_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype_qn(),
        traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
ptime_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet_qn()
    });
    return r;
}

std::string ptime_helper::helper_name() const {
    static std::string r("ptime_helper");
    return r;
}

bool ptime_helper::is_enabled(const assistant& /*a*/,
    const logical::entities::helper_properties& /*hp*/) const {
    return true;
}

void ptime_helper::apply(assistant& ast, const logical::entities::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
ast.stream() << std::endl;
ast.stream() << qn << std::endl;
ast.stream() << "create_" << ident << "(const unsigned int position) {" << std::endl;
ast.stream() << "    const auto day(static_cast<unsigned short>(1 + (position % 27)));" << std::endl;
ast.stream() << "    using boost::gregorian::date;" << std::endl;
ast.stream() << "    using boost::posix_time::ptime;" << std::endl;
ast.stream() << "    using boost::posix_time::time_duration;" << std::endl;
ast.stream() << "    date d(2002, 2, day);" << std::endl;
ast.stream() << "    ptime r(d, time_duration(1,2,3));" << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
}
}
