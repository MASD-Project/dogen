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
#include "dogen/cpp/types/formatters/types/forward_declarations_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::file forward_declarations_formatter_stitch(
    formatters::formatting_assistant& fa,
    const formattables::forward_declarations_info& fd) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());

            if (fd.is_enum()) {
fa.stream() << std::endl;
fa.stream() << "enum class " << fd.name() << " : " << fd.enum_type() << ";" << std::endl;
fa.stream() << std::endl;
            } else {
fa.stream() << std::endl;
fa.stream() << "class " << fd.name() << ";" << std::endl;
fa.stream() << std::endl;
            }
        } // snf
fa.stream() << std::endl;
    } // sbf
    return fa.make_file();
}

} } } }
