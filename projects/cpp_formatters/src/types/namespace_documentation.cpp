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
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/cpp/namespace_formatter.hpp"
#include "dogen/cpp/types/formattables/namespace_info.hpp"
#include "dogen/cpp_formatters/types/doxygen_comments.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/namespace_documentation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.namespace_documentation"));

const std::string missing_namespace_info("Namespace info is empty");
const std::string missing_enum_info("Enumeration info is empty");

}

namespace dogen {
namespace cpp_formatters {

namespace_documentation::
namespace_documentation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr
namespace_documentation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new namespace_documentation(stream));
}

void namespace_documentation::format_namespace(
    const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::namespace_info>(f.formattable()));
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_namespace_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_namespace_info));
    }

    {
        const cpp::formattables::namespace_info& ni(*o);
        if (ni.namespaces().empty())
            return;

        auto other_ns(ni.namespaces());
        other_ns.pop_back();
        dogen::formatters::cpp::namespace_formatter nsf;
        for (auto ns : other_ns)
            nsf.format_begin(stream_, ns);
        utility_.blank_line();

        doxygen_comments dc(stream_, indenter_);
        dc.format(ni.documentation());
        nsf.format_begin(stream_, ni.namespaces().back());

        bool first(true);
        for (auto ns : ni.namespaces()) {
            if (!first)
                stream_ << " ";
            nsf.format_end(stream_);
            first = false;
        }
    }
    utility_.blank_line(2);
}

void namespace_documentation::format(const cpp::formattables::file_info& f) {
    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(f.header_guard());
    utility_.blank_line();

    includes includes(stream_);
    includes.format(f);

    if (f.descriptor().content_type() ==
        cpp::formattables::content_types::namespace_doc)
        format_namespace(f);

    guards.format_end();
}

} }
