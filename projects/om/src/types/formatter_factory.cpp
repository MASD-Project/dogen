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
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/formatter_factory.hpp"

namespace dogen {
namespace om {

std::list<boost::shared_ptr<type_formatter_interface> >
formatter_factory::build_type_formatters() {
    std::list<boost::shared_ptr<type_formatter_interface> > r;
    using tfi = boost::shared_ptr<type_formatter_interface>;
    r.push_back(tfi(new cpp_types_main_header_file_formatter));
    return r;
}

std::list<boost::shared_ptr<module_formatter_interface> >
formatter_factory::build_module_formatters() {
    std::list<boost::shared_ptr<module_formatter_interface> > r;
    using mfi = boost::shared_ptr<module_formatter_interface>;
    r.push_back(mfi(new cpp_types_main_header_file_formatter));
    return r;
}

std::list<boost::shared_ptr<concept_formatter_interface> >
formatter_factory::build_concept_formatters() {
    std::list<boost::shared_ptr<concept_formatter_interface> > r;
    return r;
}

} }
