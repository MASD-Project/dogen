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
#include "dogen/cpp/types/formatters/hash/enum_header_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace hash {

dogen::formatters::file enum_header_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::enum_info& e) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
fa.stream() << std::endl;
fa.stream() << "namespace std {" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template<>" << std::endl;
fa.stream() << "struct hash<" << e.qualified_name() << "> {" << std::endl;
fa.stream() << "public:" << std::endl;
fa.stream() << "    size_t operator()(const " << e.qualified_name() << "& v) const {" << std::endl;
fa.stream() << "        return std::hash<unsigned int>()(static_cast<unsigned int>(v));" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
    } // sbf
    return fa.make_file();
}

} } } }
