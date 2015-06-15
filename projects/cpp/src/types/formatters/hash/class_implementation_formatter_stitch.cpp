/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace hash {

dogen::formatters::file class_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::class_info& c) {
    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
fa.stream() << std::endl;
fa.stream() << "namespace {" << std::endl;
fa.stream() << std::endl;
        if (!c.properties().empty() || !c.parents().empty()) {
fa.stream() << "template <typename HashableType>" << std::endl;
fa.stream() << "inline void combine(std::size_t& seed, const HashableType& value) {" << std::endl;
fa.stream() << "    std::hash<HashableType> hasher;" << std::endl;
fa.stream() << "    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);" << std::endl;
fa.stream() << "}" << std::endl;
        }

        fa.add_helper_methods();
fa.stream() << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
        {
            auto snf(fa.make_scoped_namespace_formatter());
fa.stream() << std::endl;
fa.stream() << "std::size_t " << c.name() << "_hasher::hash(const " << c.name() << "&" << ((c.properties().empty() && c.parents().empty()) ? "" : " v") << ") {" << std::endl;
fa.stream() << "    std::size_t seed(0);" << std::endl;
            if (!c.parents().empty()) {
fa.stream() << std::endl;
                for (const auto p : c.parents())
fa.stream() << "    combine(seed, dynamic_cast<const " << p.qualified_name() << "&>(v));" << std::endl;

            }

            if (!c.properties().empty()) {
fa.stream() << std::endl;
                for (const auto p : c.properties()) {
                    if (fa.requires_hashing_helper_method(p.type()))
fa.stream() << "    combine(seed, hash_" << p.type().complete_identifiable_name() << "(v." << p.name() << "()));" << std::endl;
                    else
fa.stream() << "    combine(seed, v." << p.name() << "()" << (p.type().is_date() ? ".modjulian_day()" : "") << ");" << std::endl;
                }

                if (c.properties().size() > 1)
fa.stream() << std::endl;
            }
fa.stream() << "    return seed;" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
        } // snf
    } // sbf
    // return fa.make_file();
    return fa.make_file(false/*override*/);
}
} } } }
