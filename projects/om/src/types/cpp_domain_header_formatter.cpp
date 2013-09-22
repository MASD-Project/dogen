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
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"
#include "dogen/om/types/cpp_domain_header_formatter.hpp"

namespace {

const std::string empty;
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

void cpp_domain_header_formatter::
visit(const dogen::sml::enumeration& e) const {
    if (stream_ == nullptr) {
        // throw
    }

    std::ostream& s(*stream_);
    cpp_formatters::indenter indenter;
    cpp_formatters::utility u(*stream_, indenter);

    {
        std::list<std::string> namespaces;
        cpp_formatters::namespace_helper ns(s, namespaces);

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
                    s << assignment.str() << "," << comment.str() << std::endl;
                    assignment.str(empty);
                    comment.str(empty);
                }
                assignment << indenter << enumerator.name() << " = "
                           << enumerator.value();
                doxygen_previous_.format(s, comment.str());
                is_first = false;
            }
            s << assignment.str() << comment.str() << std::endl;
        }
        s << indenter << "};" << std::endl;
        u.blank_line();
    }
    u.blank_line(2);
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
