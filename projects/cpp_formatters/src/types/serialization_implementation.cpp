/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <list>
#include <string>
#include <ostream>
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/exception_info.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/serialization_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.serialization_implementation"));

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");
const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");
const std::string enum_info_not_supported(
    "Enumerations do not have an implementation");

}

namespace dogen {
namespace cpp_formatters {

serialization_implementation::
serialization_implementation(std::ostream& stream,
    const bool disable_xml_serialization,
    const bool disable_eos_serialization) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_xml_serialization_(disable_xml_serialization),
    disable_eos_serialization_(disable_eos_serialization) { }

file_formatter::shared_ptr serialization_implementation::
create(std::ostream& stream, const bool disable_xml_serialization,
    const bool disable_eos_serialization) {
    return file_formatter::shared_ptr(
        new serialization_implementation(stream, disable_xml_serialization,
            disable_eos_serialization));
}

void serialization_implementation::save_function(
    const cpp::formattables::class_info& ci) {
    const auto parents(ci.parents());
    const auto props(ci.properties());
    const bool has_properties(!props.empty());
    const bool has_parents(!parents.empty());
    const bool has_properties_or_parents(has_properties || has_parents);

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void save(Archive& "
            << (has_properties_or_parents ? "ar," : "/*ar*/,")
            << std::endl;

    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "const ";
        qname qname(stream_);
        qname.format(ci);

        stream_ << (has_properties_or_parents ? "& v," : "& /*v*/,")
                << std::endl
                << indenter_ << "const unsigned int /*version*/) ";

        utility_.open_scope();
        {
            for (const auto p : parents) {
                if (disable_xml_serialization_) {
                    stream_ << indenter_ << "ar << base_object<";
                    qname.format(p);
                    stream_ << ">(v);" << std::endl;
                } else {
                    stream_ << indenter_ << "ar << make_nvp("
                            << utility_.quote(p.name()) << ", base_object<";
                    qname.format(p);
                    stream_ << ">(v));" << std::endl;
                }
            }

            if (has_properties && has_parents)
                utility_.blank_line();

            for (const auto p : props) {
                std::ostringstream s;
                s << "v." << utility_.as_member_variable(p.name());
                if (p.type().is_filesystem_path())
                    s << ".generic_string()";

                if (disable_xml_serialization_) {
                    stream_ << indenter_ << "ar << " << s.str() << ";"
                            << std::endl;
                } else {
                    stream_ << indenter_ << "ar << make_nvp("
                            << utility_.quote(p.name())
                            << ", " << s.str() << ");"
                            << std::endl;
                }
            }
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void serialization_implementation::load_function(
    const cpp::formattables::class_info& ci) {
    const auto parents(ci.parents());
    const auto props(ci.properties());
    const bool has_properties(!props.empty());
    const bool has_parents(!parents.empty());
    const bool has_properties_or_parents(has_properties || has_parents);

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "void load(Archive& "
            << (has_properties_or_parents ? "ar," : "/*ar*/,")
            << std::endl;

    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_;
        qname qname(stream_);
        qname.format(ci);

        stream_ << (has_properties_or_parents ? "& v," : "& /*v*/,")
                << std::endl
                << indenter_ << "const unsigned int /*version*/) ";

        utility_.open_scope();
        {
            for (const auto p : parents) {
                if (disable_xml_serialization_) {
                    stream_ << indenter_
                            << "ar >> "
                            << utility_.quote(p.name())
                            << ", base_object<";
                    qname.format(p);
                    stream_ << ">(v);" << std::endl;
                } else {
                    stream_ << indenter_
                            << "ar >> make_nvp("
                            << utility_.quote(p.name())
                            << ", base_object<";
                    qname.format(p);
                    stream_ << ">(v));" << std::endl;
                }
            }

            if (has_properties && has_parents)
                utility_.blank_line();

            for (const auto p : props) {
                std::ostringstream s;
                if (p.type().is_filesystem_path()) {
                    s << p.name() + "_tmp";
                    stream_ << indenter_ << "std::string " << s.str() << ";"
                            << std::endl;
                } else
                    s << "v." << utility_.as_member_variable(p.name());

                if (disable_xml_serialization_) {
                    stream_ << indenter_ << "ar >> " << s.str() << ";"
                            << std::endl;
                } else {
                    stream_ << indenter_ << "ar >> make_nvp("
                            << utility_.quote(p.name())
                            << ", " << s.str() << ");"
                            << std::endl;
                }

                if (p.type().is_filesystem_path()) {
                    stream_ << indenter_ << "v."
                            << utility_.as_member_variable(p.name())
                            << " = " << s.str() << ";"
                            << std::endl;
                }
            }
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void serialization_implementation::
template_instantiations(const cpp::formattables::class_info& ci) {
    stream_ << indenter_ << "template void save("
            << "archive::polymorphic_oarchive& ar, const ";
    qname qname(stream_);
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    stream_ << indenter_ << "template void load("
            << "archive::polymorphic_iarchive& ar, ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template void save(archive::text_oarchive& ar, "
            << "const ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    stream_ << indenter_ << "template void load(archive::text_iarchive& ar, ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template void save(archive::binary_oarchive& ar, "
            << "const ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    stream_ << indenter_ << "template void load(archive::binary_iarchive& ar, ";
    qname.format(ci);
    stream_ << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();

    if (!disable_xml_serialization_) {
        stream_ << indenter_ << "template void save(archive::xml_oarchive& ar, "
                << "const ";
        qname.format(ci);
        stream_ << "& v, unsigned int version);" << std::endl;
        stream_ << indenter_ << "template void load(archive::xml_iarchive& ar, ";
        qname.format(ci);
        stream_ << "& v, unsigned int version);" << std::endl;
        utility_.blank_line();
    }

    if (!disable_eos_serialization_) {
        stream_ << indenter_ << "template void save(eos::portable_oarchive& "
                << " ar, const ";
        qname.format(ci);
        stream_ << "& v, unsigned int version);" << std::endl;
        stream_ << indenter_ << "template void load(eos::portable_iarchive& ar"
                << ", ";
        qname.format(ci);
        stream_ << "& v, unsigned int version);" << std::endl
                << std::endl;
        utility_.blank_line();
    }
}

void serialization_implementation::format_class(
    const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::class_info>(f.formattable()));

    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const cpp::formattables::class_info& ci(*o);
    qname qname(stream_);
    if (ci.is_parent() || !ci.parents().empty()) {
        stream_ << indenter_ << "BOOST_CLASS_TRACKING(" << std::endl;
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_;
            qname.format(ci);
            stream_ << "," << std::endl;
            stream_ << indenter_ << "boost::serialization"
                    << "::track_selectively)"
                    << std::endl;
        }
        utility_.blank_line();
    }

    {
        const auto ns = std::list<std::string> { boost_ns, serialization_ns };
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, ns);

        utility_.blank_line();
        save_function(ci);
        load_function(ci);
    }
    utility_.blank_line(2);

    {
        const auto ns = std::list<std::string> { boost_ns, serialization_ns };
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, ns);

        utility_.blank_line();
        template_instantiations(ci);
    }
}

void serialization_implementation::
format_enumeration(const cpp::formattables::file_info&) {
    BOOST_LOG_SEV(lg, error) << enum_info_not_supported;
    BOOST_THROW_EXCEPTION(
        formatting_error(enum_info_not_supported));
}

void serialization_implementation::format(
    const cpp::formattables::file_info& f) {
    licence licence(stream_);
    licence.format();

    includes includes(stream_);
    includes.format(f);
    utility_.blank_line();

    using cpp::formattables::content_types;
    if (f.descriptor().content_type() == content_types::unversioned_key ||
        f.descriptor().content_type() == content_types::versioned_key ||
        f.descriptor().content_type() == content_types::value_object ||
        f.descriptor().content_type() == content_types::entity ||
        f.descriptor().content_type() == content_types::keyed_entity)
        format_class(f);
    else if (f.descriptor().content_type() == content_types::enumeration)
        format_enumeration(f);
}

} }
