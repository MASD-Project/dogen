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
#include "dogen.text.cpp/types/transforms/io/associative_container_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::cpp::transforms::io {
std::string associative_container_helper_transform::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
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
        io::traits::class_implementation_archetype_qn(),
        io::traits::primitive_implementation_archetype_qn(),
        types::traits::class_implementation_archetype_qn(),
        types::traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
associative_container_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet_qn(), types::traits::facet_qn()
    });
    return r;
}

std::string associative_container_helper_transform::helper_name() const {
    static std::string r("associative_container_helper_transform");
    return r;
}

bool associative_container_helper_transform::is_enabled(
    const physical::entities::model& m,
    const logical::entities::element& e,
    const physical::entities::artefact& a,
    const logical::entities::helper_properties& hp) const {
    return is_streaming_enabled(m, e, a, hp);
}

void associative_container_helper_transform::
apply(std::ostream& os, const logical::entities::model& m,
    const logical::entities::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto qn(d.name_tree_qualified());
        auto snf(make_scoped_namespace_formatter(os, m, d.namespaces()));

        if (hp.direct_descendants().size() == 2) {
            const auto key(hp.direct_descendants().front());
            const auto value(hp.direct_descendants().back());
os << std::endl;
os << "inline std::ostream& operator<<(std::ostream& s, const " << qn << "& v) {" << std::endl;
os << "    s << \"[\";" << std::endl;
os << "    for (auto i(v.begin()); i != v.end(); ++i) {" << std::endl;
os << "        if (i != v.begin()) s << \", \";" << std::endl;
os << "        s << \"[ { \" << \"\\\"__type__\\\": \" << \"\\\"key\\\"\" << \", \" << \"\\\"data\\\": \";" << std::endl;
os << "        s << " << streaming_for_type(key, "i->first") << ";" << std::endl;
os << "        s << \" }, { \" << \"\\\"__type__\\\": \" << \"\\\"value\\\"\" << \", \" << \"\\\"data\\\": \";" << std::endl;
os << "        s << " << streaming_for_type(value, "i->second") << ";" << std::endl;
os << "        s << \" } ]\";" << std::endl;
os << "    }" << std::endl;
os << "    s << \" ] \";" << std::endl;
os << "    return s;" << std::endl;
os << "}" << std::endl;
os << std::endl;
        } else {
        const auto containee(hp.direct_descendants().front());
os << std::endl;
os << "inline std::ostream& operator<<(std::ostream& s, const " << qn << "& v) {" << std::endl;
os << "    s << \"[ \";" << std::endl;
os << "    for (auto i(v.begin()); i != v.end(); ++i) {" << std::endl;
os << "        if (i != v.begin()) s << \", \";" << std::endl;
os << "        s << " << streaming_for_type(containee, "*i") << ";" << std::endl;
os << "    }" << std::endl;
os << "    s << \"] \";" << std::endl;
os << "    return s;" << std::endl;
os << "}" << std::endl;
os << std::endl;
        }
    }
os << std::endl;
}
}
