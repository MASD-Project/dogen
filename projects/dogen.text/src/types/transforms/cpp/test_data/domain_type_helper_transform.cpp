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
#include "dogen.text/types/transforms/cpp/test_data/domain_type_helper_transform.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::transforms::cpp::test_data {
std::string domain_type_helper_transform::id() const {
    static auto r(std::string("<masd.cpp.test_data>") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string domain_type_helper_transform::family() const {
    static std::string r("Default");
    return r;
}

std::list<std::string>
domain_type_helper_transform::owning_formatters() const {
    static auto r(std::list<std::string> {
        "masd.cpp.test_data.class_implementation",
        "masd.cpp.test_data.primitive_implementation"
    });
    return r;
}

std::list<std::string>
domain_type_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        "masd.cpp.test_data"
    });
    return r;
}

std::string domain_type_helper_transform::helper_name() const {
    static std::string r("domain_type_helper_transform");
    return r;
}

bool domain_type_helper_transform::is_enabled(
    const physical::entities::model& /*m*/,
    const logical::entities::element& /*e*/,
    const physical::entities::artefact& /*a*/,
    const logical::entities::helper_properties& /*hp*/) const {
    return true;
}

void domain_type_helper_transform::apply(std::ostream& os, const logical::entities::model& /*m*/,
    const logical::entities::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const bool is_pointer(d.is_pointer());
    const bool is_recursive(d.is_circular_dependency());

    if (is_recursive) {
os << std::endl;
os << qn << (is_pointer ? "*" : "") << std::endl;
os << "create_" << ident << "(const unsigned int) {" << std::endl;
        if (is_pointer) {
os << "    return nullptr;" << std::endl;
        } else {
os << "    return " << qn << "();" << std::endl;
        }
os << "}" << std::endl;
    } else {
os << std::endl;
os << qn << (is_pointer ? "*" : "") << std::endl;
os << "create_" << ident << "(const unsigned int position) {" << std::endl;
os << "    return " << qn << "_generator::create" << (is_pointer ? "_ptr" : "") << "(position);" << std::endl;
os << "}" << std::endl;
    }
}
}
