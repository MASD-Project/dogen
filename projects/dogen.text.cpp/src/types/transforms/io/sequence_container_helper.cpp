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
#include "dogen.text.cpp/types/transforms/io/sequence_container_helper.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/formattables/helper_properties.hpp"

namespace dogen::text::cpp::transforms::io {

std::string sequence_container_helper::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string sequence_container_helper::family() const {
    static std::string r("SequenceContainer");
    return r;
}

std::list<std::string>
sequence_container_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        io::traits::class_implementation_archetype_qn(),
        io::traits::primitive_implementation_archetype_qn(),
        types::traits::class_implementation_archetype_qn(),
        types::traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
sequence_container_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet_qn(), types::traits::facet_qn()
    });
    return r;
}

std::string sequence_container_helper::helper_name() const {
    static std::string r("sequence_container_helper");
    return r;
}

bool sequence_container_helper::is_enabled(const assistant& a,
    const formattables::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

void sequence_container_helper::apply(assistant& ast, const formattables::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto qn(d.name_tree_qualified());
        auto snf(ast.make_scoped_namespace_formatter(d.namespaces()));
        const auto containee(hp.direct_descendants().front());
ast.stream() << std::endl;
ast.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << qn << "& v) {" << std::endl;
ast.stream() << "    s << \"[ \";" << std::endl;
ast.stream() << "    for (auto i(v.begin()); i != v.end(); ++i) {" << std::endl;
ast.stream() << "        if (i != v.begin()) s << \", \";" << std::endl;
ast.stream() << "        s << " << ast.streaming_for_type(containee, "*i") << ";" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "    s << \"] \";" << std::endl;
ast.stream() << "    return s;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
    }
ast.stream() << std::endl;
}
}
