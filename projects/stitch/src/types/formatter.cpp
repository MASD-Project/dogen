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
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("stitch.formatters"));

const std::string model_name("stitch");
const std::string facet_name;
const std::string formatter_name("stitch.formatter");
const std::string group_name;

const std::string spaced_inserter(" << ");
const std::string spaced_inserter_endl(" << std::endl;");

}

namespace dogen {
namespace stitch {

// class visitor : private boost::static_visitor<> {
// public:
//     visitor(const std::string& stream_name, std::ostream& s) : stream_(s) { }

// public:
//     void operator()(const mixed_content_line& l) const {
//         for (const auto& s : l.segments()) {
//             if (s.type() == text)
//                 stream_ << stream_name << spaced_inserter << s.content();
//             else
//                 stream_ << s.content();
//         }
//     }

//     void operator()(const std::string& l) const {
//         stream_ << l << std::endl;
//     }

//     void operator()(const mixed_content_block& b) const {
//         for (const auto& l : b.content())
//             boost::apply_visitor(*this, l);
//     }

//     void operator()(const scriptlet_block& b) const {
//         for (const auto& l : b.content())
//             stream_ << l << std::endl;
//     }

// private:
//     std::ostream& stream_;
// };

dynamic::schema::ownership_hierarchy formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(model_name, facet_name, formatter_name, group_name);
    return r;
}

dogen::formatters::file formatter::format(const text_template& /*tt*/) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting template.";

    // std::ostringstream ss;
    // boost::iostreams::filtering_ostream fo;
    // dogen::formatters::indent_filter::push(fo, 4);
    // fo.push(ss);
    // visitor v(fo);

    dogen::formatters::file r;
    // for (const auto& b : tt.content()) {
    //     boost::apply_visitor(v, b);
    //             const auto& mcb(boost::get<mixed_content_block>(b));
    //             for (const auto& l : mcb.content() {
    //                     if (l.which() == 0) {
    //                         const auto& s(boost::get<std::string>(l));

    //                         BOOST_LOG_SEV(lg, debug) << "Formatting template.";

    return r;
}

} }
