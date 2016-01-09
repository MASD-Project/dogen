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
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_dependencies_builder_factory::inclusion_dependencies_builder_factory(
    const enablement_repository& erp,
    const settings::bundle_repository& brp,
    const inclusion_directives_repository& idrp,
    const integrated_facets_repository& ifrp)
    : enablement_repository_(erp), bundle_repository_(brp),
      directives_repository_(idrp),
      integrated_facets_repository_(ifrp) {}

inclusion_dependencies_builder inclusion_dependencies_builder_factory::
make() const {
    return inclusion_dependencies_builder(
        enablement_repository_,
        bundle_repository_,
        directives_repository_,
        integrated_facets_repository_);
}

} } } }
