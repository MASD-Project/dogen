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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.extraction/io/quote_types_io.hpp"
#include "masd.dogen.extraction/types/formatting_error.hpp"
#include "masd.dogen.extraction/types/utility_formatter.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("extraction.utility?formatter"));

const std::string space(" ");
const std::string inserter("<<");
const std::string single_quote("'");
const std::string double_quote("\"");
const std::string single_quote_escaped("\\\'");
const std::string double_quote_escaped("\\\"");
const std::string escape("\\");
const std::string escape_escaped("\\\\");
const std::string unsupported_quote_type("Invalid or unsupported quote type: ");

}

namespace masd::dogen::extraction {

class space_scope {
public:
    space_scope(const spacing_types st, std::ostream& s)
        : spacing_type_(st), stream_(s) {

        if (spacing_type_ == spacing_types::left_space ||
            spacing_type_ == spacing_types::left_and_right_space)
            stream_ << space;
    }

    ~space_scope() {
        if (spacing_type_ == spacing_types::right_space ||
            spacing_type_ == spacing_types::left_and_right_space)
            stream_ << space;
    }

private:
    const spacing_types spacing_type_;
    std::ostream& stream_;
};

utility_formatter::utility_formatter(std::ostream& s)
    : stream_(s) {}

void utility_formatter::insert(const std::string& s,
    const spacing_types st) const {
    const space_scope scope(st, stream_);
    stream_ << s;
}

void utility_formatter::insert_quote(const quote_types qt) const {
    switch(qt) {
    case quote_types::single_quote:
        stream_ << single_quote;
        return;
    case quote_types::double_quote:
        stream_ << double_quote;
        return;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_quote_type << qt;
        BOOST_THROW_EXCEPTION(formatting_error(
                unsupported_quote_type + boost::lexical_cast<std::string>(qt)));
    }
}

std::string utility_formatter::
escape_quote(const std::string& s, const quote_types qt) const {
    auto r(boost::replace_all_copy(s, escape, escape_escaped));
    switch(qt) {
    case quote_types::single_quote:
        boost::replace_all(r, single_quote, single_quote_escaped);
        break;
    case quote_types::double_quote:
        boost::replace_all(r, double_quote, double_quote_escaped);
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_quote_type << qt;
        BOOST_THROW_EXCEPTION(formatting_error(
                unsupported_quote_type + boost::lexical_cast<std::string>(qt)));
    }
    return r;
}

void utility_formatter::insert_escaped(const std::string& s,
    const quote_types qt, const spacing_types st) const {
    const space_scope scope(st, stream_);
    stream_ << escape_quote(s, qt);
}

void utility_formatter::insert_quoted(const std::string& s,
    const bool escape_content, const quote_types qt,
    const spacing_types st) const {
    const space_scope scope(st, stream_);

    insert_quote(qt);
    if (escape_content)
        insert_escaped(s, qt);
    else
        stream_ << s;

    insert_quote(qt);
}

void utility_formatter::insert_quoted_escaped(const std::string& s) const {
    const auto qt(quote_types::double_quote);
    insert_quote(qt);
    insert_escaped(s, qt);
    insert_quote(qt);
}

void utility_formatter::insert_streamed(const std::string& s) const {
    stream_ << double_quote << double_quote_escaped << double_quote
            << space << inserter << space
            << s
            << space << inserter << space
            << double_quote << double_quote_escaped << double_quote;
}

void utility_formatter::insert_end_line(const unsigned int n) const {
    for (unsigned int i(0); i < n; ++i)
        stream_ << std::endl;
}

}
