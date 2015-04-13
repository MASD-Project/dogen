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
#include <boost/variant/static_visitor.hpp>
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("stitch.formatters"));

const std::string model_name("stitch");
const std::string facet_name;
const std::string formatter_name("stitch.formatter");
const std::string group_name;

const std::string inserter("<<");
const std::string endl("std::endl;");

}

namespace dogen {
namespace stitch {

class visitor : public boost::static_visitor<> {
public:
    visitor(const std::string& stream_name, std::ostream& s)
        : utility_(s), stream_name_(stream_name), stream_(s) { }

public:
    void operator()(const mixed_content_line& l) const {
        bool is_first(true);
        const auto spaces(formatters::spacing_types::left_and_right_space);
        for (const auto& s : l.segments()) {
            if (is_first) {
                stream_ << stream_name_;
                is_first = false;
            }

            utility_.insert(inserter, spaces);
            if (s.type() == segment_types::text)
                utility_.insert_quoted(s.content(), true/*escape_content*/);
            else
                stream_ << s.content();
        }
        utility_.insert(inserter, spaces);
        utility_.insert(endl);
        stream_ << std::endl;
    }

    void operator()(const std::string& l) const {
        const auto spaces(formatters::spacing_types::left_and_right_space);
        stream_ << stream_name_;
        utility_.insert(inserter, spaces);
        utility_.insert_quoted(l, true/*escape_content*/);
        utility_.insert(inserter, spaces);
        utility_.insert(endl);
        stream_ << std::endl;
    }

    void operator()(const mixed_content_block& b) const {
        for (const auto& l : b.content())
            boost::apply_visitor(*this, l);
    }

    void operator()(const scriptlet_block& b) const {
        for (const auto& l : b.content())
            stream_ << l << std::endl;
    }

private:
    const formatters::utility_formatter utility_;
    const std::string stream_name_;
    std::ostream& stream_;
};

dynamic::schema::ownership_hierarchy formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(model_name, facet_name, formatter_name, group_name);
    return r;
}

dogen::formatters::file formatter::format(const text_template& tt) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting template.";

    std::ostringstream s;
    visitor v("stream_", s);
    for (const auto& b : tt.content())
        boost::apply_visitor(v, b);

    dogen::formatters::file r;
    r.content(s.str());

    BOOST_LOG_SEV(lg, debug) << "Formatted template.";

    return r;
}

} }
