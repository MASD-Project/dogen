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
#include "dogen/quilt.cpp/types/properties/helper_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/associative_container_helper_stitch.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

std::string associative_container_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
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
        test_data::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string>
associative_container_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        test_data::traits::facet_name()
    });
    return r;
}

bool associative_container_helper::requires_explicit_call() const {
    return false;
}

std::string associative_container_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

bool associative_container_helper::is_enabled(const assistant& a,
    const properties::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

std::string associative_container_helper::helper_name() const {
    static std::string r("associative_container_helper");
    return r;
}

void associative_container_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
a.stream() << std::endl;
a.stream() << qn << " create_" << ident << "(unsigned int position) {" << std::endl;
a.stream() << "    " << qn << " r;" << std::endl;
a.stream() << "    for (unsigned int i(0); i < 4; ++i) {" << std::endl;
    if (hp.direct_descendants().size() == 1) {
        const auto containee(hp.direct_descendants().front());
a.stream() << "        r.insert(create_" << containee.name_tree_identifiable() << "(position + i));" << std::endl;
    } else if (hp.direct_descendants().size() == 2) {
        const auto key(hp.direct_descendants().front());
        const auto value(hp.direct_descendants().back());
a.stream() << "        r.insert(std::make_pair(create_" << key.name_tree_identifiable() << "(position + i), create_" << value.name_tree_identifiable() << "(position + i)));" << std::endl;
    }
a.stream() << "    }" << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
}

void associative_container_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t) {
a.stream() << std::endl;
a.stream() << t.complete_name() << " create_" << t.complete_identifiable_name() << "(unsigned int position) {" << std::endl;
a.stream() << "    " << t.complete_name() << " r;" << std::endl;
a.stream() << "    for (unsigned int i(0); i < 4; ++i) {" << std::endl;
    if (t.children().size() == 1) {
        const auto containee(t.children().front());
a.stream() << "        r.insert(create_" << containee.complete_identifiable_name() << "(position + i));" << std::endl;
    } else if (t.children().size() == 2) {
        const auto key(t.children().front());
        const auto value(t.children().back());

a.stream() << "        r.insert(std::make_pair(create_" << key.complete_identifiable_name() << "(position + i), create_" << value.complete_identifiable_name() << "(position + i)));" << std::endl;
    }
a.stream() << "    }" << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
