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
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/backends/cpp/formatters/production_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_facet_includer.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_facet_includer.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_hash_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_hash_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_io_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_io_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_generator_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_generator_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_database_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_database_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_registrar_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_registrar_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_forward_declarations_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_null_formatter.hpp"
#include "dogen/generator/backends/cpp/formatters/factory.hpp"

using namespace dogen::utility::log;

namespace {

static logger lg(logger_factory("formatters::factory"));
const std::string production_failure_msg("Formatter factory not setup for: ");

using dogen::generator::backends::cpp::cpp_facet_types;
bool contains(const std::set<cpp_facet_types>& f, cpp_facet_types ft) {
    return f.find(ft) != f.end();
}

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

factory::factory(const config::cpp_settings& settings)
    : settings_(settings),
      disable_io_(!contains(settings_.enabled_facets(),
              cpp_facet_types::io)),
      disable_serialization_(!contains(settings_.enabled_facets(),
              cpp_facet_types::serialization)) { }

factory::result_type
factory::create_main_formatter(std::ostream& s, cpp_facet_types ft,
    cpp_file_types flt) const {

    switch (ft) {
    case cpp_facet_types::domain:
        if (flt == cpp_file_types::header)
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
        if (flt == cpp_file_types::header)
            return io_header::create(s);
        else
            return io_implementation::create(s);
        break;
    case cpp_facet_types::hash:
        if (flt == cpp_file_types::header)
            return hash_header::create(s);
        else
            return hash_implementation::create(s);
        break;
    case cpp_facet_types::serialization:
        if (flt == cpp_file_types::header)
            return serialization_header::create(s,
                settings_.disable_xml_serialization());
        else
            return serialization_implementation::create(s,
                settings_.disable_xml_serialization());
        break;
    case cpp_facet_types::test_data:
        if (flt == cpp_file_types::header)
            return generator_header::create(s);
        else
            return generator_implementation::create(s);
        break;

    default: {
        std::ostringstream s;
        s << production_failure_msg << ft << ", " << flt;
        throw production_failure(s.str());
    } }
}

factory::result_type factory::create_registrar_formatter(
    std::ostream& s, cpp_file_types flt) const {

    switch (flt) {
    case cpp_file_types::header:
        return registrar_header::create(s);
        break;

    case cpp_file_types::implementation:
        return registrar_implementation::create(s,
            settings_.disable_xml_serialization());
        break;

    default: {
        std::ostringstream ss;
        ss << production_failure_msg << flt;
        throw production_failure(ss.str());
    } }
}

factory::result_type factory::create_null_formatter(std::ostream& s) const {
    return null_formatter::create(s);
}

factory::result_type
factory::create(std::ostream& s, cpp_facet_types ft, cpp_file_types flt,
    cpp_aspect_types at) const {

    switch (at) {
    case cpp_aspect_types::main:
        return create_main_formatter(s, ft, flt);
        break;
    case cpp_aspect_types::includers:
        return facet_includer::create(s, ft);
        break;
    case cpp_aspect_types::forward_decls:
        return forward_declarations_header::create(s);
        break;
    case cpp_aspect_types::registrar:
        return create_registrar_formatter(s, flt);
        break;
    case cpp_aspect_types::null_aspect:
        return create_null_formatter(s);
        break;
    default: {
        std::ostringstream s;
        s << production_failure_msg << ft << ", " << flt << ", " << at;
        BOOST_LOG_SEV(lg, error) << s.str();
        throw production_failure(s.str());
    } }
}

} } } } }
