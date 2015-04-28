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
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/types/forward_declarations_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

void forward_declarations_formatter_stitch(std::ostream& s,
    const boost::optional<dogen::formatters::general_settings>& gs,
    const settings::formatter_settings& fs,
    const formattables::forward_declarations_info& fd) {

    dogen::formatters::cpp::scoped_boilerplate_formatter
       sbf(s, gs, fs.inclusion_dependencies(), *fs.header_guard());
s << std::endl;
s << "namespace boost {" << std::endl;
s << "namespace serialization {" << std::endl;
s << std::endl;
s << "template<class Archive>" << std::endl;
s << "void save(Archive& ar, const " << fd.qualified_name() << "& v, unsigned int version);" << std::endl;
s << std::endl;
s << "template<class Archive>" << std::endl;
s << "void load(Archive& ar, " << fd.qualified_name() << "& v, unsigned int version);" << std::endl;
s << std::endl;
s << "} }" << std::endl;
s << std::endl;
}

} } } }
