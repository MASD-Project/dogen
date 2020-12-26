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
#include "dogen.text/types/transforms/cpp/io/smart_pointer_helper_transform.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::transforms::cpp::io {
std::string smart_pointer_helper_transform::id() const {
    static auto r(std::string("<masd.cpp.io>") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string smart_pointer_helper_transform::family() const {
    static std::string r("SmartPointer");
    return r;
}

std::list<std::string>
smart_pointer_helper_transform::owning_formatters() const {
    static auto r(std::list<std::string> {
        "masd.cpp.io.class_implementation",
        "masd.cpp.io.primitive_implementation",
        "masd.cpp.types.class_implementation",
        "masd.cpp.types.primitive_implementation"
    });
    return r;
}

std::list<std::string>
smart_pointer_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        "masd.cpp.io", "masd.cpp.types"
    });
    return r;
}

std::string smart_pointer_helper_transform::helper_name() const {
    static std::string r("smart_pointer_helper_transform");
    return r;
}

bool smart_pointer_helper_transform::is_enabled(
    const physical::entities::model& m,
    const logical::entities::element& e,
    const physical::entities::artefact& a,
    const logical::entities::helper_properties& hp) const {
    return is_streaming_enabled(m, e, a, hp);
}
void smart_pointer_helper_transform::apply(std::ostream& os, const logical::entities::model& m,
    const logical::entities::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
        const auto n_qn(d.name_qualified());
        auto snf(make_scoped_namespace_formatter(os, m, d.namespaces()));
        const auto containee(hp.direct_descendants().front());
os << std::endl;
os << "inline std::ostream& operator<<(std::ostream& s, const " << nt_qn << "& v) {" << std::endl;
os << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << n_qn << "\\\"\" << \", \"" << std::endl;
os << "      << \"\\\"memory\\\": \" << \"\\\"\" << static_cast<void*>(v.get()) << \"\\\"\" << \", \";" << std::endl;
os << std::endl;
os << "    if (v)" << std::endl;
os << "        s << \"\\\"data\\\": \" << " << streaming_for_type(containee, "*v") << ";" << std::endl;
os << "    else" << std::endl;
os << "        s << \"\\\"data\\\": \"\"\\\"<null>\\\"\";" << std::endl;
os << "    s << \" }\";" << std::endl;
os << "    return s;" << std::endl;
os << "}" << std::endl;
os << std::endl;
    }
os << std::endl;
}
}
