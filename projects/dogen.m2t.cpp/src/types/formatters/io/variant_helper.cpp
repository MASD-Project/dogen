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
#include "dogen.m2t.cpp/types/formatters/io/variant_helper.hpp"
#include "dogen.m2t.cpp/types/formatters/assistant.hpp"
#include "dogen.m2t.cpp/types/formatters/io/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/types/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/helper_properties.hpp"

namespace dogen::m2t::cpp::formatters::io {

std::string variant_helper::id() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string variant_helper::family() const {
    static std::string r("BoostVariant");
    return r;
}

std::list<std::string>
variant_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        io::traits::class_implementation_archetype(),
        io::traits::primitive_implementation_archetype(),
        types::traits::class_implementation_archetype(),
        types::traits::primitive_implementation_archetype()
    });
    return r;
}

std::list<std::string>
variant_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet(), types::traits::facet()
    });
    return r;
}

std::string variant_helper::helper_name() const {
    static std::string r("variant_helper");
    return r;
}

bool variant_helper::is_enabled(const assistant& a,
    const formattables::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

void variant_helper::
format(assistant& a, const formattables::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
        const auto n_qn(d.name_qualified());
        auto snf(a.make_scoped_namespace_formatter(d.namespaces()));
a.stream() << std::endl;
a.stream() << "struct " << d.name_tree_identifiable() << "_visitor : public boost::static_visitor<> {" << std::endl;
a.stream() << "    " << d.name_tree_identifiable() << "_visitor(std::ostream& s) : stream_(s) {" << std::endl;
a.stream() << "        s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << d.name_qualified() << "\\\"\" << \", \";" << std::endl;
a.stream() << "        s << \"\\\"data\\\": \";" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    ~" << d.name_tree_identifiable() << "_visitor() { stream_ << \" }\"; }" << std::endl;
        for (const auto& dd : hp.direct_descendants()) {
a.stream() << std::endl;
a.stream() << "    void operator()(const " << dd.name_qualified() << (dd.is_simple_type() ? "" : "&") << " v) const {" << std::endl;
            if (dd.is_simple_type()) {
a.stream() << "        stream_ << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << dd.name_qualified() << "\\\"\" << \", \";" << std::endl;
a.stream() << "        stream_ << \"\\\"value\\\": \";" << std::endl;
a.stream() << "        stream_ << " << a.streaming_for_type(dd, "v") << ";" << std::endl;
a.stream() << "        stream_ << \" }\";" << std::endl;
            } else
a.stream() << "        stream_ << " << a.streaming_for_type(dd, "v") << ";" << std::endl;
a.stream() << "    }" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    std::ostream& stream_;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << d.name_tree_qualified() << "& v) {" << std::endl;
a.stream() << "    boost::apply_visitor(" << d.name_tree_identifiable() << "_visitor(s), v);" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}
}
