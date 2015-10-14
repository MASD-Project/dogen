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
#include "dogen/cpp/types/formatters/hash/variant_helper_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace hash {

void variant_helper_stitch(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t) {
fa.stream() << std::endl;
fa.stream() << "struct " << t.complete_identifiable_name() << "_visitor : public boost::static_visitor<> {" << std::endl;
fa.stream() << "    " << t.complete_identifiable_name() << "_visitor() : hash(0) {}" << std::endl;
    const auto children(t.children());
    for (const auto& c : children) {
fa.stream() << "    void operator()(const " << c.name() << (c.is_primitive() ? "" : "&") << " v) const {" << std::endl;
        if (!fa.requires_hashing_helper_method(c))
fa.stream() << "        combine(hash, v);" << std::endl;
        else
fa.stream() << "        combine(hash, hash_" << c.complete_identifiable_name() << "(v));" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << std::endl;
    }
fa.stream() << "    mutable std::size_t hash;" << std::endl;
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
fa.stream() << "inline std::size_t hash_" << t.complete_identifiable_name() << "(const " << t.complete_name() << "& v) {" << std::endl;
fa.stream() << "    " << t.complete_identifiable_name() << "_visitor vis;" << std::endl;
fa.stream() << "    boost::apply_visitor(vis, v);" << std::endl;
fa.stream() << "    return vis.hash;" << std::endl;
fa.stream() << "}" << std::endl;
}
} } } }
