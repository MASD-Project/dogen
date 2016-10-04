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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

dogen::formatters::file class_implementation_formatter_stitch(
    assistant& a, const yarn::object& o) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        a.add_helper_methods(o.name().id());

        const auto qn(a.get_qualified_name(o.name()));
        const bool has_attributes(!o.local_attributes().empty());
        const bool has_parent(o.parent());
        const bool has_attributes_or_parent(has_attributes || has_parent);

        if (o.is_parent() || o.parent()) {
a.stream() << std::endl;
a.stream() << "BOOST_CLASS_TRACKING(" << std::endl;
a.stream() << "    " << qn << "," << std::endl;
a.stream() << "    boost::serialization::track_selectively)" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;

        /*
         * Save function
         */
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void save(Archive& " << (has_attributes_or_parent ? "ar" : "/*ar*/") << "," << std::endl;
a.stream() << "    const " << qn << "& " << (has_attributes_or_parent ? "v" : "/*v*/") << "," << std::endl;
a.stream() << "    const unsigned int /*version*/) {" << std::endl;
        if (o.parent()) {
            const auto& pn(*o.parent());
            const auto pqn(a.get_qualified_name(pn));
a.stream() << "    ar << make_nvp(\"" << pn.simple() << "\", base_object<" << pqn << ">(v));" << std::endl;
        }

        if (has_attributes && has_parent)
a.stream() << std::endl;
        for (const auto attr : o.local_attributes()) {
a.stream() << "    ar << make_nvp(\"" << attr.name().simple() << "\", v." << a.make_member_variable_name(attr) << ");" << std::endl;
        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        /*
         * Load function
         */
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void load(Archive& " << (has_attributes_or_parent ? "ar," : "/*ar*/,") << std::endl;
a.stream() << "    " << qn << "& " << (has_attributes_or_parent ? "v" : "/*v*/") << "," << std::endl;
a.stream() << "    const unsigned int /*version*/) {" << std::endl;
        if (o.parent()) {
            const auto& pn(*o.parent());
            const auto pqn(a.get_qualified_name(pn));
a.stream() << "    ar >> make_nvp(\"" << pn.simple() << "\", base_object<" << pqn << ">(v));" << std::endl;
            if (has_attributes && has_parent)
a.stream() << std::endl;
        }

        for (const auto attr : o.local_attributes()) {
a.stream() << "    ar >> make_nvp(\"" << attr.name().simple() << "\", v." << a.make_member_variable_name(attr) << ");" << std::endl;
        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "} }" << std::endl;
a.stream() << std::endl;
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::polymorphic_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::polymorphic_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::text_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::text_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::binary_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::binary_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::xml_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::xml_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "} }" << std::endl;
    } // sbf
    return a.make_file();
}

} } } } }
