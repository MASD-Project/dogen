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
#include <boost/algorithm/string.hpp>
#include <boost/variant/apply_visitor.hpp>
#include "dogen/stitch/io/mixed_content_line_io.hpp"
#include "dogen/stitch/io/mixed_content_block_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {

struct boost_variant_std_string_dogen_stitch_mixed_content_line_visitor : public boost::static_visitor<> {
    boost_variant_std_string_dogen_stitch_mixed_content_line_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_std_string_dogen_stitch_mixed_content_line_visitor() { stream_ << " }"; }

    void operator()(const std::string& v) const {
        stream_ << v;
    }

    void operator()(const dogen::stitch::mixed_content_line& v) const {
        stream_ << v;
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<std::string, dogen::stitch::mixed_content_line>& v) {
    boost::apply_visitor(boost_variant_std_string_dogen_stitch_mixed_content_line_visitor(s), v);
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace stitch {

std::ostream& operator<<(std::ostream& s, const mixed_content_block& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::stitch::mixed_content_block\"" << ", "
      << "\"content\": " << v.content()
      << " }";
    return(s);
}

} }