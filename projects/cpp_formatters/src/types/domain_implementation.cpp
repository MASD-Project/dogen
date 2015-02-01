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
#include <ostream>
#include <boost/throw_exception.hpp>
#include <boost/pointer_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/inserter_implementation.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/key_class_implementation.hpp"
#include "dogen/cpp_formatters/types/domain_class_implementation.hpp"
#include "dogen/cpp_formatters/types/domain_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.domain_implementation"));

const std::string inserter("<< ");
const std::string space_inserter(" << ");
const std::string open_bracket(" {");
const std::string close_bracket(" }");
const std::string colon(": ");
const std::string semi_colon(";");
const std::string space(" ");
const std::string comma(",");

const std::string missing_class_info("Class info is empty");
const std::string enum_info_not_supported(
    "Enumerations do not have an implementation");
const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");

const std::string invalid_aspect_type("Invalid value for aspect_types");
const std::string invalid_category_type("Invalid value for category_types");

// FIXME: until we add support to indenter.
const std::string special_indent("       ");

}

namespace dogen {
namespace cpp_formatters {

domain_implementation::
domain_implementation(std::ostream& stream, bool disable_complete_constructor,
    bool use_integrated_io, bool disable_io) :
    stream_(stream),
    utility_(stream_, indenter_),
    disable_complete_constructor_(disable_complete_constructor),
    use_integrated_io_(use_integrated_io),
    disable_io_(disable_io) { }

file_formatter::shared_ptr domain_implementation::
create(std::ostream& stream, bool disable_complete_constructor,
    bool use_integrated_io, bool disable_io) {
    return file_formatter::shared_ptr(new domain_implementation(stream,
            disable_complete_constructor, use_integrated_io, disable_io));
}

void domain_implementation::
smart_pointer_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_smart_pointer));
    }
    const auto container(nti);
    {
        namespace_helper ns_helper(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline bool operator=="
                << "(const " << container.complete_name() << "& lhs,"
                << std::endl
                << indenter_ << "const "
                << container.complete_name() << "& rhs) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "return (!lhs && !rhs) ||"
                    << "(lhs && rhs && (*lhs == *rhs));"
                    << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void domain_implementation::
recursive_helper_method_creator(const cpp::formattables::nested_type_info& nti,
    std::unordered_set<std::string>& types_done) {
    if (types_done.find(nti.complete_identifiable_name()) != types_done.end())
        return;

    const auto children(nti.children());
    for (const auto c : children)
        recursive_helper_method_creator(c, types_done);

    if (nti.is_smart_pointer())
        smart_pointer_helper(nti);

    types_done.insert(nti.complete_identifiable_name());
}

void domain_implementation::io_helper_methods(
    const cpp::formattables::class_info& ci) {
    const bool has_io(ci.is_parent() || !ci.parents().empty() ||
        use_integrated_io_);

    if (!has_io  || disable_io_)
        return;

    const bool inside_class(false);
    inserter_implementation i(stream_, indenter_, inside_class);
    i.format_helper_methods(ci);
}

void domain_implementation::
inserter_operator(const cpp::formattables::class_info& ci) {
    if (!use_integrated_io_ || disable_io_)
        return;

    const bool no_arg(!ci.is_parent() && ci.parents().empty() &&
        ci.properties().empty());
    stream_ << indenter_ << "std::ostream& operator<<(std::ostream& s"
            << ", const " << ci.name() << "&" << (no_arg ? ") " : "v) ");

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        if (ci.is_parent() || !ci.parents().empty()) {
            stream_ << indenter_ << "v.to_stream(s);" << std::endl
                    << indenter_ << "return(s);" << std::endl;
        } else {
            const bool inside_class(false);
            inserter_implementation i(stream_, indenter_, inside_class);
            i.format_inserter_implementation(ci);
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void domain_implementation::
class_implementation(const cpp::formattables::content_descriptor& cd,
    const cpp::formattables::class_info& ci) {

    using dogen::utility::exception::invalid_enum_value;
    using cpp::formattables::aspect_types;
    using cpp::formattables::content_types;
    if (cd.aspect_type() == aspect_types::main) {
        const auto ct(cd.content_type());
        if (ct == content_types::versioned_key ||
            ct == content_types::unversioned_key) {
            key_class_implementation
                f(stream_, disable_complete_constructor_, disable_io_);
            f.format(ci);
            return;
        } else if (ct == content_types::value_object) {
            domain_class_implementation
                f(stream_, disable_complete_constructor_, disable_io_);
            f.format(ci);
            return;
        }
        BOOST_LOG_SEV(lg, error) << invalid_category_type;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_category_type));
    }
    BOOST_LOG_SEV(lg, error) << invalid_aspect_type;
    BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_aspect_type));
}

void domain_implementation::format_class(
    const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::class_info>(f.entity()));
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }
    const cpp::formattables::class_info& ci(*o);
    io_helper_methods(ci);

    std::unordered_set<std::string> types_done;
    const auto props(ci.properties());
    for (const auto p : props)
        recursive_helper_method_creator(p.type(), types_done);

    namespace_helper ns_helper(stream_, ci.namespaces());
    utility_.blank_line();
    class_implementation(f.descriptor(), ci);
    inserter_operator(ci);
}

void domain_implementation::format_enumeration(
    const cpp::formattables::file_info&) {
    BOOST_LOG_SEV(lg, error) << missing_class_info;
    BOOST_THROW_EXCEPTION(
        formatting_error(enum_info_not_supported));
}

void domain_implementation::format(const cpp::formattables::file_info& f) {
    licence licence(stream_);
    licence.format();

    includes includes(stream_);
    includes.format(f);

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
