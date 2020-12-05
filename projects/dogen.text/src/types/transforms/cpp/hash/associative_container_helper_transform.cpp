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
#include "dogen.logical/types/entities/helper_properties.hpp"
#include "dogen.text/types/transforms/cpp/hash/associative_container_helper_transform.hpp"

namespace dogen::text::transforms::cpp::hash {
std::string associative_container_helper_transform::id() const {
    static auto r(std::string("<masd.cpp.hash>") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string associative_container_helper_transform::family() const {
    static std::string r("AssociativeContainer");
    return r;
}

std::list<std::string>
associative_container_helper_transform::owning_formatters() const {
    static auto r(std::list<std::string> {
        "masd.cpp.hash.class_implementation",
        "masd.cpp.hash.primitive_implementation"
    });
    return r;
}

std::list<std::string>
associative_container_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        "masd.cpp.hash"
    });
    return r;
}

std::string associative_container_helper_transform::helper_name() const {
    static std::string r("associative_container_helper_transform");
    return r;
}

bool associative_container_helper_transform::is_enabled(
    const physical::entities::model& /*m*/,
    const logical::entities::element& /*e*/,
    const physical::entities::artefact& /*a*/,
    const logical::entities::helper_properties& /*hp*/) const {
    return true;
}

void associative_container_helper_transform::
apply(std::ostream& os, const logical::entities::model& /*m*/,
    const logical::entities::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());

    if (hp.direct_descendants().size() == 2) {
        const auto key(hp.direct_descendants().front());
        const auto value(hp.direct_descendants().back());
os << std::endl;
os << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
os << "    std::size_t seed(0);" << std::endl;
os << "    for (const auto& i : v) {" << std::endl;
        if (!key.requires_hashing_helper())
os << "        combine(seed, i.first);" << std::endl;
        else
os << "        combine(seed, hash_" << key.name_tree_identifiable() << "(i.first));" << std::endl;

        if (!(value.requires_hashing_helper()))
os << "        combine(seed, i.second);" << std::endl;
        else
os << "        combine(seed, hash_" << value.name_tree_identifiable() << "(i.second));" << std::endl;
os << "    }" << std::endl;
os << "    return seed;" << std::endl;
os << "}" << std::endl;
    } else {
        const auto containee(hp.direct_descendants().front());
os << std::endl;
os << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
os << "    std::size_t seed(0);" << std::endl;
os << "    for (const auto& i : v) {" << std::endl;
    if (!containee.requires_hashing_helper())
os << "        combine(seed, i);" << std::endl;
    else
os << "        combine(seed, hash_" << containee.name_tree_identifiable() << "(i));" << std::endl;
os << "    }" << std::endl;
os << "    return seed;" << std::endl;
os << "}" << std::endl;
    }
}
}
