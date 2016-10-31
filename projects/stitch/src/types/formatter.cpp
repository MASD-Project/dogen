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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/stitch/io/block_types_io.hpp"
#include "dogen/stitch/types/formatting_error.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("stitch.formatters"));

const std::string empty_header_guard;
const std::string model_name("stitch");
const std::string facet_name("types");
const std::string formatter_name("stitch.formatter");

const std::string inserter("<<");
const std::string endl("std::endl;");

const std::string empty_stream_name("Stream name cannot be empty.");
const std::string empty_line("Line has no content.");
const std::string unsupported_block_type("Block type is unsupported: ");

}

namespace dogen {
namespace stitch {

void formatter::format_text_block_line(const std::string& stream_name,
    const std::string& l, std::ostream& s) const {
    const auto spaces(formatters::spacing_types::left_and_right_space);
    s << stream_name;

    const formatters::utility_formatter u(s);
    u.insert(inserter, spaces);
    if (!l.empty()) {
        u.insert_quoted(l, true/*escape_content*/);
        u.insert(inserter, spaces);
    }
    u.insert(endl);
    s << std::endl;
}

void formatter::
format_expression_block_line(const std::string& stream_name,
    const std::string& l, std::ostream& s) const {
    s << stream_name;

    const formatters::utility_formatter u(s);
    const auto spaces(formatters::spacing_types::left_and_right_space);
    u.insert(inserter, spaces);

    s << l;

    u.insert(inserter, spaces);
    u.insert(endl);
    s << std::endl;
}

void formatter::
format_standard_control_block_line(
    const std::string& l, std::ostream& s) const {
    s << l << std::endl;
}

void formatter::format_mixed_content_line(const std::string& stream_name,
    const line& l, std::ostream& s) const {
    const auto spaces(formatters::spacing_types::left_and_right_space);
    const formatters::utility_formatter u(s);
    bool is_first(true);
    for (const auto& b : l.blocks()) {
        if (is_first) {
            s << stream_name;
            is_first = false;
        }

        u.insert(inserter, spaces);
        if (b.type() == block_types::text_block)
            u.insert_quoted(b.content(), true/*escape_content*/);
        else
            s << b.content();
    }
    u.insert(inserter, spaces);
    u.insert(endl);
    s << std::endl;
}

void formatter::format_line_with_single_block(const std::string& stream_name,
    const line& l, std::ostream& s) const {
    const auto& b(l.blocks().front());
    const auto& c(b.content());
    switch(b.type()) {
    case block_types::text_block:
        format_text_block_line(stream_name, c, s);
        break;
    case block_types::expression_block:
        format_expression_block_line(stream_name, c, s);
        break;
    case block_types::standard_control_block:
        format_standard_control_block_line(c, s);
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_block_type << b.type();
        const auto s(boost::lexical_cast<std::string>(b.type()));
        BOOST_THROW_EXCEPTION(
            formatting_error(unsupported_block_type + s));
    }
}

annotations::archetype_location formatter::ownership_hierarchy() const {
    static annotations::archetype_location
        r(model_name, facet_name, formatter_name);
    return r;
}

dogen::formatters::artefact formatter::format(const text_template& tt) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting template.";

    const auto& ss(tt.properties().stitching_properties());
    const auto stream_variable_name(ss.stream_variable_name());
    if (stream_variable_name.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_stream_name;
        BOOST_THROW_EXCEPTION(formatting_error(empty_stream_name));
    }

    std::ostringstream s;
    {
        const auto& id(ss.inclusion_dependencies());
        dogen::formatters::cpp::scoped_boilerplate_formatter
            sbf(s, tt.properties().decoration_properties(), id,
                empty_header_guard);

        dogen::formatters::cpp::scoped_namespace_formatter snf(
            s, ss.containing_namespaces(), false/*create_anonymous_namespace*/,
            true/*add_new_line_*/);

        for (const auto& l : tt.lines()) {
            if (l.blocks().empty()) {
                BOOST_LOG_SEV(lg, error) << empty_line;
                BOOST_THROW_EXCEPTION(formatting_error(empty_line));
            } else if (l.blocks().size() == 1)
                format_line_with_single_block(stream_variable_name, l, s);
            else
                format_mixed_content_line(stream_variable_name, l, s);
        }
    }

    dogen::formatters::artefact r;
    r.overwrite(true);
    r.content(s.str());
    if (tt.properties().stitching_properties().output_path())
        r.path(*tt.properties().stitching_properties().output_path());

    BOOST_LOG_SEV(lg, debug) << "Formatted template.";

    return r;
}

} }
