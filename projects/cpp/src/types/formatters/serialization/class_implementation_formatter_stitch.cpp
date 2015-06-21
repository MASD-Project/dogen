/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/cpp/types/formatters/serialization/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

dogen::formatters::file class_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::class_info& c) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        const bool has_properties(!c.properties().empty());
        const bool has_parents(!c.parents().empty());
        const bool has_properties_or_parents(has_properties || has_parents);

        if (c.is_parent() || !c.parents().empty()) {
fa.stream() << std::endl;
fa.stream() << "BOOST_CLASS_TRACKING(" << std::endl;
fa.stream() << "    " << c.qualified_name() << "," << std::endl;
fa.stream() << "    boost::serialization::track_selectively)" << std::endl;
        }
fa.stream() << std::endl;
fa.stream() << "namespace boost {" << std::endl;
fa.stream() << "namespace serialization {" << std::endl;

        /*
         * Save function
         */
fa.stream() << std::endl;
fa.stream() << "template<typename Archive>" << std::endl;
fa.stream() << "void save(Archive& " << (has_properties_or_parents ? "ar" : "/*ar*/") << "," << std::endl;
fa.stream() << "    const " << c.qualified_name() << "& " << (has_properties_or_parents ? "v" : "/*v*/") << "," << std::endl;
fa.stream() << "    const unsigned int /*version*/) {" << std::endl;
        for (const auto p : c.parents()) {
            if (fa.is_xml_serialization_disabled())
fa.stream() << "    ar << base_object<" << p.qualified_name() << ">(v);" << std::endl;
            else
fa.stream() << "    ar << make_nvp(\"" << p.name() << "\", base_object<" << p.qualified_name() << ">(v));" << std::endl;
        }

        if (has_properties && has_parents)
fa.stream() << std::endl;
        for (const auto p : c.properties()) {
            if (fa.is_xml_serialization_disabled())
fa.stream() << "    ar << " << fa.make_member_variable_name(p) << (p.type().is_filesystem_path() ? ".generic_string()" : "") << ";" << std::endl;
            else
fa.stream() << "    ar << make_nvp(\"" << p.name() << "\", v." << fa.make_member_variable_name(p) << (p.type().is_filesystem_path() ? ".generic_string()" : "") << ");" << std::endl;
        }
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
        /*
         * Load function
         */
fa.stream() << "template<typename Archive>" << std::endl;
fa.stream() << "void load(Archive& " << (has_properties_or_parents ? "ar," : "/*ar*/,") << std::endl;
fa.stream() << "    " << c.qualified_name() << "& " << (has_properties_or_parents ? "v" : "/*v*/") << "," << std::endl;
fa.stream() << "    const unsigned int /*version*/) {" << std::endl;
        for (const auto p : c.parents()) {
            if (fa.is_xml_serialization_disabled())
fa.stream() << "    ar >> \"" << p.name() << "\", base_object<" << p.qualified_name() << ">(v);" << std::endl;
            else
fa.stream() << "    ar >> make_nvp(\"" << p.name() << "\", base_object<" << p.qualified_name() << ">(v));" << std::endl;
            if (has_properties && has_parents)
fa.stream() << std::endl;
        }

        for (const auto p : c.properties()) {
            if (p.type().is_filesystem_path()) {
fa.stream() << "    std::string " << p.name() << "_tmp;" << std::endl;
                if (fa.is_xml_serialization_disabled())
fa.stream() << "    ar >> " << p.name() << "_tmp;" << std::endl;
                else
fa.stream() << "    ar >> make_nvp(\"" << p.name() << "\", " << p.name() << "_tmp);" << std::endl;
fa.stream() << "    v." << fa.make_member_variable_name(p) << " = " << p.name() << "_tmp;" << std::endl;
            } else {
                if (fa.is_xml_serialization_disabled())
fa.stream() << "    ar >> " << p.name() << ";" << std::endl;
                else
fa.stream() << "    ar >> make_nvp(\"" << p.name() << "\", v." << fa.make_member_variable_name(p) << ");" << std::endl;
            }
        }
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
fa.stream() << "} }" << std::endl;
fa.stream() << std::endl;
fa.stream() << "namespace boost {" << std::endl;
fa.stream() << "namespace serialization {" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template void save(archive::polymorphic_oarchive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << "template void load(archive::polymorphic_iarchive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template void save(archive::text_oarchive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << "template void load(archive::text_iarchive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template void save(archive::binary_oarchive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << "template void load(archive::binary_iarchive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
        if (!fa.is_xml_serialization_disabled()) {
fa.stream() << "template void save(archive::xml_oarchive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << "template void load(archive::xml_iarchive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
        }

        if (!fa.is_eos_serialization_disabled()) {
fa.stream() << "template void save(eos::portable_oarchive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << "template void load(eos::portable_iarchive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
        }
fa.stream() << "} }" << std::endl;
    } // sbf
    // return fa.make_file();
    return fa.make_file(false/*overwrite*/);
}

} } } }
