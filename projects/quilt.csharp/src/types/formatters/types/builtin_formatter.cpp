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
#include "dogen/quilt.csharp/types/formatters/types/builtin_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/types/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace types {

std::string builtin_formatter::static_artefact() {
    return traits::builtin_archetype();
}

std::string builtin_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location builtin_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::backend(),
          traits::facet(),
          builtin_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& builtin_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_builtin_name());
    return r;
}

boost::filesystem::path builtin_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> builtin_formatter::
inclusion_dependencies(const yarn::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact builtin_formatter::
format(const context& /*ctx*/, const yarn::meta_model::element& /*e*/) const {
    dogen::formatters::artefact r;
    return r;
}

} } } } }
