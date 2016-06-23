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
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/types/smart_pointer_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

std::string smart_pointer_helper::family() const {
    static std::string r("SmartPointer");
    return r;
}

std::list<std::string>
smart_pointer_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_formatter_name()
    });
    return r;
}

bool smart_pointer_helper::requires_explicit_call() const {
    return false;
}

std::string smart_pointer_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

bool smart_pointer_helper::
is_enabled(const assistant& /*a*/, const bool /*in_inheritance*/) const {
    return true;
}

void smart_pointer_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    {
        const auto d(hp.descriptor());
        auto snf(a.make_scoped_namespace_formatter(d.namespaces()));
a.stream() << std::endl;
a.stream() << "inline bool operator==(const " << d.name_tree_qualified() << "& lhs," << std::endl;
a.stream() << "const " << d.name_tree_qualified() << "& rhs) {" << std::endl;
a.stream() << "    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}

} } } } }
