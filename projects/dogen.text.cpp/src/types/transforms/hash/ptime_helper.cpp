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
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/formattables/helper_properties.hpp"
#include "dogen.text.cpp/types/transforms/hash/ptime_helper.hpp"

namespace dogen::text::cpp::transforms::hash {

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
    const formattables::helper_properties& /*hp*/) const {
    return true;
}

void ptime_helper::
apply(assistant& ast, const formattables::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
ast.stream() << std::endl;
ast.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
ast.stream() << "    std::size_t seed(0);" << std::endl;
ast.stream() << "    const boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));" << std::endl;
ast.stream() << "    boost::posix_time::time_duration d(v - epoch);" << std::endl;
ast.stream() << "    seed = static_cast<std::size_t>(d.total_seconds());" << std::endl;
ast.stream() << "    return seed;" << std::endl;
ast.stream() << "}" << std::endl;
}
}
