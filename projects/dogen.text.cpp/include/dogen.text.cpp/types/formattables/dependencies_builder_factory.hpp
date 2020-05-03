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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_DEPENDENCIES_BUILDER_FACTORY_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_DEPENDENCIES_BUILDER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.text/types/entities/element_archetype.hpp"
#include "dogen.text.cpp/types/formattables/formattable.hpp"
#include "dogen.text.cpp/types/formattables/dependencies_builder.hpp"
#include "dogen.text.cpp/types/formattables/directive_group_repository.hpp"

namespace dogen::text::cpp::formattables {

/**
 * @brief Creates inclusion dependencies builders.
 *
 * This factory exists to avoid having to supply an inclusion
 * dependencies builder as non-const, and to avoid having some kind of
 * reset method for its state. It is also useful so that we don't have
 * to pass around all of the parameters needed to construct it, we can
 * create it at a high-level and then just pass the factory around.
 *
 * Finally, the factory pre-computes the mapping of the default
 * formatters per facet.
 */
class dependencies_builder_factory final {
public:
    dependencies_builder_factory(
        const directive_group_repository& dgrp,
        const std::unordered_set<text::entities::element_archetype>&
        enabled_archetype_for_element);

public:
    /**
     * @brief Create an inclusion dependencies builder.
     */
    dependencies_builder make() const;

private:
    const directive_group_repository& inclusion_directives_;
    const std::unordered_set<text::entities::element_archetype>&
    enabled_archetype_for_element_;
};

}

#endif
