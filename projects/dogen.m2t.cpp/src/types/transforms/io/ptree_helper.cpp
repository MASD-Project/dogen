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
#include "dogen.m2t.cpp/types/transforms/io/ptree_helper.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/helper_properties.hpp"

namespace dogen::m2t::cpp::transforms::io {

std::string ptree_helper::id() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string ptree_helper::family() const {
    static std::string r("BoostPTree");
    return r;
}

std::list<std::string>
ptree_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        io::traits::class_implementation_archetype(),
        io::traits::primitive_implementation_archetype(),
        types::traits::class_implementation_archetype(),
        types::traits::primitive_implementation_archetype()
    });
    return r;
}

std::list<std::string>
ptree_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet(), types::traits::facet()
    });
    return r;
}

std::string ptree_helper::helper_name() const {
    static std::string r("ptree_helper");
    return r;
}

bool ptree_helper::is_enabled(const assistant& a,
    const formattables::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

void ptree_helper::
apply(assistant& a, const formattables::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
        auto snf(a.make_scoped_namespace_formatter(d.namespaces()));
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << nt_qn << "& v) {" << std::endl;
a.stream() << "    std::ostringstream ss;" << std::endl;
a.stream() << "    boost::property_tree::write_json(ss, v);" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::string content(ss.str());" << std::endl;
a.stream() << "    boost::replace_all(content, \"\\r\\n\", \"\");" << std::endl;
a.stream() << "    boost::replace_all(content, \"\\n\", \"\");" << std::endl;
a.stream() << std::endl;
a.stream() << "    s << content;" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}
}
