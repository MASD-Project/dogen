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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/formattables/container.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the inclusion dependencies repository.
 */
class inclusion_dependencies_repository_factory {
public:
    /**
     * @brief Create the inclusion dependencies repository.
     */
    inclusion_dependencies_repository make(
        const inclusion_dependencies_builder_factory& bf, const container& c,
        const sml::model& m) const;
};

} } }

#endif
