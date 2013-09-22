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
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/om/types/formatting_error.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"
#include "dogen/om/types/cpp_domain_header_formatter.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om_formatters.modeline_formatter"));

const std::string empty;
const std::string missing_stream_ptr("Stream pointer is null");
const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

}

namespace dogen {
namespace om {

cpp_domain_header_formatter::cpp_domain_header_formatter()
    : stream_(nullptr),
      doxygen_next_(
          !start_on_first_line,
          use_documentation_tool_markup,
          !documenting_previous_identifier,
          comment_styles::c_style,
          !last_line_is_blank),
      doxygen_previous_(
          start_on_first_line,
          use_documentation_tool_markup,
          documenting_previous_identifier,
          comment_styles::cpp_style,
          !last_line_is_blank) { }

std::list<std::string> cpp_domain_header_formatter::
namespaces(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    return r;
}

void cpp_domain_header_formatter::
visit(const dogen::sml::enumeration& e) const {
    if (stream_ == nullptr) {
        BOOST_LOG_SEV(lg, error) << missing_stream_ptr;
        BOOST_THROW_EXCEPTION(formatting_error(missing_stream_ptr));
    }

    BOOST_LOG_SEV(lg, debug) << "Formatting enumeration: " << e.name();

    std::ostream& s(*stream_);
    cpp_formatters::indenter indenter;
    cpp_formatters::utility u(*stream_, indenter);

    {
        cpp_formatters::namespace_helper ns(s, namespaces(e.name()));

        u.blank_line();

        doxygen_next_.format(*stream_, e.documentation());
        s << indenter << "enum class " << e.name().simple_name()
          << " : unsigned int ";

        u.open_scope();
        {
            cpp_formatters::positive_indenter_scope is(indenter);
            bool is_first(true);
            std::ostringstream assignment;
            std::ostringstream comment;
            for (const auto& enumerator : e.enumerators()) {
                if (!is_first) {
                    const auto c(comment.str());
                    s << assignment.str() << ",";
                    if (!c.empty())
                        s << " " << c;
                    assignment.str(empty);
                    comment.str(empty);
                }
                assignment << indenter << enumerator.name() << " = "
                           << enumerator.value();
                doxygen_previous_.format(comment, e.documentation());
                is_first = false;
            }

            s << assignment.str();
            const auto c(comment.str());
            if (!c.empty())
                s << " " << c;
        }
        s << indenter << "};" << std::endl;
        u.blank_line();
    }
    u.blank_line();
}

void cpp_domain_header_formatter::
format(std::ostream& s, const sml::type& t, const licence& l,
    const modeline& m, const std::string& marker,
    const sml::model& /*model*/) const {

    stream_ = &s;

    const cpp_includes i = cpp_includes();
    const boost::filesystem::path relative_file_path;
    cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, i, relative_file_path);
    t.accept(*this);
    f.format_end(s, m, relative_file_path);

    stream_ = nullptr;
}

} }
