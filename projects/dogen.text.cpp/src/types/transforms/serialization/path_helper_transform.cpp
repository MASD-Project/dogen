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
#include "dogen.text.cpp/types/transforms/serialization/path_helper_transform.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::cpp::transforms::serialization {
std::string path_helper_transform::id() const {
    static auto r(std::string("<") + traits::facet_qn() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string path_helper_transform::family() const {
    static std::string r("BoostPath");
    return r;
}

std::list<std::string>
path_helper_transform::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype_qn(),
        traits::primitive_implementation_archetype_qn()
    });
    return r;
}

std::list<std::string>
path_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet_qn()
    });
    return r;
}

std::string path_helper_transform::helper_name() const {
    static std::string r("path_helper_transform");
    return r;
}

bool path_helper_transform::is_enabled(
    const physical::entities::model& /*m*/,
    const logical::entities::element& /*e*/,
    const physical::entities::artefact& /*a*/,
    const logical::entities::helper_properties& /*hp*/) const {
    return true;
}

void path_helper_transform::
apply(std::ostream& os, const logical::entities::model& /*m*/,
    const logical::entities::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
os << "namespace boost {" << std::endl;
os << "namespace serialization {" << std::endl;
os << std::endl;
os << "template<class Archive>" << std::endl;
os << "void serialize(Archive& ar, boost::filesystem::path& p, const unsigned int/*v*/)" << std::endl;
os << "{" << std::endl;
os << "    std::string s;" << std::endl;
os << "    if(Archive::is_saving::value)" << std::endl;
os << "        s = p.generic_string();" << std::endl;
os << "    ar & boost::serialization::make_nvp(\"path\", s);" << std::endl;
os << "    if(Archive::is_loading::value)" << std::endl;
os << "        p = s;" << std::endl;
os << "}" << std::endl;
os << std::endl;
os << "} }" << std::endl;
    }
}
}
