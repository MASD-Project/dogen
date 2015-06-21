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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_BUILDER_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_BUILDER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates inclusion dependencies builders.
 */
class inclusion_dependencies_builder_factory final {
public:
    inclusion_dependencies_builder_factory(
        const enablement_repository& erp,
        const settings::bundle_repository& brp,
        const inclusion_directives_repository& idrp,
        const integrated_facets_repository& ifrp);

public:
    /**
     * @brief Create an inclusion dependencies builder.
     */
    inclusion_dependencies_builder make() const;

private:
    const enablement_repository& enablement_repository_;
    const settings::bundle_repository& bundle_repository_;
    const inclusion_directives_repository& directives_repository_;
    const integrated_facets_repository& integrated_facets_repository_;
};

} } }

#endif
