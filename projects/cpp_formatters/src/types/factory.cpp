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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/cpp/io/file_types_io.hpp"
#include "dogen/cpp/io/content_types_io.hpp"
#include "dogen/cpp/io/aspect_types_io.hpp"
#include "dogen/cpp_formatters/types/production_failure.hpp"
#include "dogen/cpp_formatters/types/facet_includer.hpp"
#include "dogen/cpp_formatters/types/domain_header.hpp"
#include "dogen/cpp_formatters/types/domain_implementation.hpp"
#include "dogen/cpp_formatters/types/facet_includer.hpp"
#include "dogen/cpp_formatters/types/hash_header.hpp"
#include "dogen/cpp_formatters/types/hash_implementation.hpp"
#include "dogen/cpp_formatters/types/io_header.hpp"
#include "dogen/cpp_formatters/types/io_implementation.hpp"
#include "dogen/cpp_formatters/types/generator_header.hpp"
#include "dogen/cpp_formatters/types/generator_implementation.hpp"
#include "dogen/cpp_formatters/types/serialization_header.hpp"
#include "dogen/cpp_formatters/types/serialization_implementation.hpp"
#include "dogen/cpp_formatters/types/registrar_header.hpp"
#include "dogen/cpp_formatters/types/registrar_implementation.hpp"
#include "dogen/cpp_formatters/types/forward_declarations_header.hpp"
#include "dogen/cpp_formatters/types/null_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_documentation.hpp"
#include "dogen/cpp_formatters/types/odb_header.hpp"
#include "dogen/cpp_formatters/types/visitor.hpp"
#include "dogen/cpp_formatters/types/factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.factory"));
const std::string production_failure_msg("Formatter factory not setup for: ");

bool contains(const std::set<dogen::config::cpp_facet_types>& f,
    dogen::config::cpp_facet_types ft) {
    return f.find(ft) != f.end();
}

}

namespace dogen {
namespace cpp_formatters {

factory::factory(const config::cpp_settings& settings)
    : settings_(settings),
      disable_io_(!contains(settings_.enabled_facets(),
              config::cpp_facet_types::io)),
      disable_serialization_(!contains(settings_.enabled_facets(),
              config::cpp_facet_types::serialization)) { }

factory::result_type factory::create_main_formatter(std::ostream& s,
    const cpp::content_descriptor& cd) const {

    using config::cpp_facet_types;
    using cpp::file_types;
    switch (cd.facet_type()) {
    case cpp_facet_types::types:
        if (cd.file_type() == file_types::header)
            return domain_header::create(s,
                settings_.disable_complete_constructor(),
                settings_.use_integrated_io(),
                disable_io_, disable_serialization_);
        else
            return domain_implementation::create(s,
                settings_.disable_complete_constructor(),
                settings_.use_integrated_io(),
                disable_io_);
        break;
    case cpp_facet_types::io:
        if (cd.file_type() == file_types::header)
            return io_header::create(s);
        else
            return io_implementation::create(s);
        break;
    case cpp_facet_types::hash:
        if (cd.file_type() == file_types::header)
            return hash_header::create(s);
        else
            return hash_implementation::create(s);
        break;
    case cpp_facet_types::serialization:
        if (cd.file_type() == file_types::header)
            return serialization_header::create(s,
                settings_.disable_xml_serialization());
        else
            return serialization_implementation::create(s,
                settings_.disable_xml_serialization());
        break;
    case cpp_facet_types::test_data:
        if (cd.file_type() == file_types::header)
            return generator_header::create(s);
        else
            return generator_implementation::create(s);
        break;
    case cpp_facet_types::odb:
        if (cd.file_type() == file_types::header)
            return odb_header::create(s);

    default: {
        std::ostringstream s;
        s << production_failure_msg << cd.facet_type()
          << ", " << cd.file_type() ;
        BOOST_THROW_EXCEPTION(production_failure(s.str()));
    } }
}

factory::result_type factory::create_registrar_formatter(
    std::ostream& s, const cpp::content_descriptor& cd) const {

    using cpp::file_types;
    switch (cd.file_type()) {
    case file_types::header:
        return registrar_header::create(s);
        break;

    case file_types::implementation:
        return registrar_implementation::create(s,
            settings_.disable_xml_serialization());
        break;

    default: {
        std::ostringstream ss;
        ss << production_failure_msg << cd.file_type();
        BOOST_LOG_SEV(lg, error) << ss.str();
        BOOST_THROW_EXCEPTION(production_failure(ss.str()));
    } }
}

factory::result_type factory::create_null_formatter(std::ostream& s) const {
    return null_formatter::create(s);
}

factory::result_type
factory::create(std::ostream& s, const cpp::content_descriptor& cd) const {

    using cpp::aspect_types;
    using cpp::content_types;
    switch (cd.aspect_type()) {
    case aspect_types::main:
        switch(cd.content_type()) {
        case content_types::includer:
            return facet_includer::create(s);
            break;
        case content_types::registrar:
            return create_registrar_formatter(s, cd);
            break;
        case content_types::namespace_doc:
            return namespace_documentation::create(s);
            break;
        case content_types::visitor:
            return visitor::create(s);
            break;
        case content_types::exception:
        case content_types::enumeration:
        case content_types::value_object:
        case content_types::unversioned_key:
        case content_types::versioned_key:
            return create_main_formatter(s, cd);
            break;
        case content_types::user_defined_service:
            return create_null_formatter(s);
            break;
        default: {
            std::ostringstream s;
            s << production_failure_msg << cd.facet_type() << ", "
              << cd.file_type() << ", " << cd.aspect_type() << ", "
              << cd.content_type();
            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(production_failure(s.str()));
        } };
    case aspect_types::forward_decls:
        return forward_declarations_header::create(s);
        break;
    case aspect_types::null_aspect:
        return create_null_formatter(s);
        break;
    default: {
        std::ostringstream s;
        s << production_failure_msg << cd.facet_type() << ", "
          << cd.file_type() << ", " << cd.aspect_type();
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(production_failure(s.str()));
    } }
}

} }
