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
#include "dogen.m2t.cpp/types/transforms/serialization/path_helper.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/helper_properties.hpp"

namespace dogen::m2t::cpp::transforms::serialization {

std::string path_helper::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string path_helper::family() const {
    static std::string r("BoostPath");
    return r;
}

std::list<std::string>
path_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype_qn(),
        traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
path_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet_qn()
    });
    return r;
}

std::string path_helper::helper_name() const {
    static std::string r("path_helper");
    return r;
}

bool path_helper::is_enabled(const assistant& /*a*/,
    const formattables::helper_properties& /*hp*/) const {
    return true;
}

void path_helper::
apply(assistant& ast, const formattables::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << "namespace serialization {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<class Archive>" << std::endl;
ast.stream() << "void serialize(Archive& ar, boost::filesystem::path& p, const unsigned int/*v*/)" << std::endl;
ast.stream() << "{" << std::endl;
ast.stream() << "    std::string s;" << std::endl;
ast.stream() << "    if(Archive::is_saving::value)" << std::endl;
ast.stream() << "        s = p.generic_string();" << std::endl;
ast.stream() << "    ar & boost::serialization::make_nvp(\"path\", s);" << std::endl;
ast.stream() << "    if(Archive::is_loading::value)" << std::endl;
ast.stream() << "        p = s;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "} }" << std::endl;
    }
}
}
