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
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::string include_cmakelists_formatter::static_formatter_name() {
    return traits::include_cmakelists_formatter_name();
}

dynamic::ownership_hierarchy include_cmakelists_formatter::
ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), "cmake",
            include_cmakelists_formatter::static_formatter_name(),
            empty/*group name*/);
    return r;
}

file_types include_cmakelists_formatter::file_type() const {
    return file_types::cmakefile;
}

formattables::origin_types
include_cmakelists_formatter::formattable_origin_type() const {
    return formattables::origin_types::internal;
}

void include_cmakelists_formatter::register_inclusion_dependencies_provider(
    formattables::registrar& /*rg*/) const {}

dogen::formatters::file include_cmakelists_formatter::
format(const context& ctx, const formattables::cmakelists_info& c) const {
    assistant a(ctx, ownership_hierarchy(), file_type());
    const auto r(include_cmakelists_formatter_stitch(a, c));
    return r;
}

} } } }
