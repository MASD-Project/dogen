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
#include "dogen.text.cpp/types/transforms/hash/smart_pointer_helper.hpp"

namespace dogen::text::cpp::transforms::hash {

std::string smart_pointer_helper::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string smart_pointer_helper::family() const {
    static std::string r("SmartPointer");
    return r;
}

std::list<std::string>
smart_pointer_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype_qn(),
        traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
smart_pointer_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet_qn()
    });
    return r;
}

std::string smart_pointer_helper::helper_name() const {
    static std::string r("smart_pointer_helper");
    return r;
}

bool smart_pointer_helper::is_enabled(const assistant& /*a*/,
    const formattables::helper_properties& /*hp*/) const {
    return true;
}

void smart_pointer_helper::
apply(assistant& ast, const formattables::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const auto containee(hp.direct_descendants().front());
ast.stream() << std::endl;
ast.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
ast.stream() << "    std::size_t seed(0);" << std::endl;
    if (!containee.requires_hashing_helper())
ast.stream() << "    combine(seed, *v);" << std::endl;
    else
ast.stream() << "    combine(seed, hash_" << containee.name_tree_identifiable() << "(*v));" << std::endl;
ast.stream() << "    return seed;" << std::endl;
ast.stream() << "}" << std::endl;
}
}
