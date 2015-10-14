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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/enum_header_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace test_data {

dogen::formatters::file enum_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::enum_info& e) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());
fa.stream() << std::endl;
fa.stream() << e.name() << "_generator::" << e.name() << "_generator() : position_(0) { }" << std::endl;
fa.stream() << "void " << e.name() << "_generator::" << std::endl;
fa.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
fa.stream() << "    v = static_cast<" << e.name() << ">(position % " << e.enumerators().size() << ");" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
fa.stream() << e.name() << "_generator::result_type" << std::endl;
fa.stream() << e.name() << "_generator::create(const unsigned int  position) {" << std::endl;
fa.stream() << "    result_type r;" << std::endl;
fa.stream() << "    " << e.name() << "_generator::populate(position, r);" << std::endl;
fa.stream() << "    return r;" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
fa.stream() << e.name() << "_generator::result_type" << std::endl;
fa.stream() << e.name() << "_generator::operator()() {" << std::endl;
fa.stream() << "    return create(position_++);" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
         } // snf
    } // sbf
    return fa.make_file();
}

} } } }
