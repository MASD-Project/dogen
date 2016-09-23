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
#include "dogen/quilt.cpp/types/formattables/helper_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/io/string_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string string_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string string_helper::family() const {
    static std::string r("String");
    return r;
}

std::list<std::string> string_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        io::traits::class_implementation_formatter_name(),
        types::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string> string_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet_name(),
        types::traits::facet_name()
    });
    return r;
}

std::string string_helper::helper_name() const {
    static std::string r("string_helper");
    return r;
}

bool string_helper::is_enabled(const assistant& a,
const formattables::helper_configuration& hc) const {
    return a.is_streaming_enabled(hc);
}

void string_helper::
format(assistant& a, const formattables::helper_configuration& /*hc*/) const {
a.stream() << "inline std::string tidy_up_string(std::string s) {" << std::endl;
a.stream() << "    boost::replace_all(s, \"\\r\\n\", \"<new_line>\");" << std::endl;
a.stream() << "    boost::replace_all(s, \"\\n\", \"<new_line>\");" << std::endl;
a.stream() << "    boost::replace_all(s, \"\\\"\", \"<quote>\");" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
}
} } } } }
