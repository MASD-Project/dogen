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
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/helper_properties.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/associative_container_helper.hpp"

namespace dogen::m2t::cpp::transforms::hash {

std::string associative_container_helper::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string associative_container_helper::family() const {
    static std::string r("AssociativeContainer");
    return r;
}

std::list<std::string>
associative_container_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype_qn(),
        traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
associative_container_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet_qn()
    });
    return r;
}

std::string associative_container_helper::helper_name() const {
    static std::string r("associative_container_helper");
    return r;
}

bool associative_container_helper::is_enabled(const assistant& /*a*/,
    const formattables::helper_properties& /*hp*/) const {
    return true;
}

void associative_container_helper::
apply(assistant& a, const formattables::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());

    if (hp.direct_descendants().size() == 2) {
        const auto key(hp.direct_descendants().front());
        const auto value(hp.direct_descendants().back());
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
a.stream() << "    for (const auto& i : v) {" << std::endl;
        if (!key.requires_hashing_helper())
a.stream() << "        combine(seed, i.first);" << std::endl;
        else
a.stream() << "        combine(seed, hash_" << key.name_tree_identifiable() << "(i.first));" << std::endl;

        if (!(value.requires_hashing_helper()))
a.stream() << "        combine(seed, i.second);" << std::endl;
        else
a.stream() << "        combine(seed, hash_" << value.name_tree_identifiable() << "(i.second));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
    } else {
        const auto containee(hp.direct_descendants().front());
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
a.stream() << "    for (const auto& i : v) {" << std::endl;
    if (!containee.requires_hashing_helper())
a.stream() << "        combine(seed, i);" << std::endl;
    else
a.stream() << "        combine(seed, hash_" << containee.name_tree_identifiable() << "(i));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
    }
}
}
