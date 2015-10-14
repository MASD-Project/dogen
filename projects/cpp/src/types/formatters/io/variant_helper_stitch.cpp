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
#include "dogen/cpp/types/formatters/io/variant_helper_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace io {

void variant_helper_stitch(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t) {

    {
        auto snf(fa.make_scoped_namespace_formatter(t));
fa.stream() << std::endl;
fa.stream() << "struct " << t.complete_identifiable_name() << "_visitor : public boost::static_visitor<> {" << std::endl;
fa.stream() << "    " << t.complete_identifiable_name() << "_visitor(std::ostream& s) : stream_(s) {" << std::endl;
fa.stream() << "        s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << t.name() << "\\\"\" << \", \";" << std::endl;
fa.stream() << "        s << \"\\\"data\\\": \";" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    ~" << t.complete_identifiable_name() << "_visitor() { stream_ << \" }\"; }" << std::endl;
        for (const auto& c : t.children()) {
fa.stream() << std::endl;
fa.stream() << "    void operator()(const " << c.name() << (c.is_primitive() ? "" : "&") << " v) const {" << std::endl;
            if (c.is_primitive()) {
fa.stream() << "        stream_ << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << c.name() << "\\\"\" << \", \";" << std::endl;
fa.stream() << "        stream_ << \"\\\"value\\\": \";" << std::endl;
fa.stream() << "        stream_ << " << fa.streaming_for_type(c, "v") << ";" << std::endl;
fa.stream() << "        stream_ << \" }\";" << std::endl;
            } else
fa.stream() << "        stream_ << " << fa.streaming_for_type(c, "v") << ";" << std::endl;
fa.stream() << "    }" << std::endl;
        }
fa.stream() << std::endl;
fa.stream() << "private:" << std::endl;
fa.stream() << "    std::ostream& stream_;" << std::endl;
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
fa.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << t.complete_name() << "& v) {" << std::endl;
fa.stream() << "    boost::apply_visitor(" << t.complete_identifiable_name() << "_visitor(s), v);" << std::endl;
fa.stream() << "    return s;" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
    }
fa.stream() << std::endl;
}
} } } }
