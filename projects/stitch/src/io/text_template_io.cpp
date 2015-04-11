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
#include <boost/variant/apply_visitor.hpp>
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/dynamic/schema/io/object_io.hpp"
#include "dogen/stitch/io/scriptlet_block_io.hpp"
#include "dogen/stitch/io/mixed_content_block_io.hpp"

namespace boost {

struct boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor : public boost::static_visitor<> {
    boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor() { stream_ << " }"; }

    void operator()(const dogen::stitch::mixed_content_block& v) const {
        stream_ << v;
    }

    void operator()(const dogen::stitch::scriptlet_block& v) const {
        stream_ << v;
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block>& v) {
    boost::apply_visitor(boost_variant_dogen_stitch_mixed_content_block_dogen_stitch_scriptlet_block_visitor(s), v);
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& v) {
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

std::ostream& operator<<(std::ostream& s, const text_template& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::stitch::text_template\"" << ", "
      << "\"extensions\": " << v.extensions() << ", "
      << "\"content\": " << v.content()
      << " }";
    return(s);
}

} }