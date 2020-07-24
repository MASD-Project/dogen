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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_NAME_REPRESENTATIONS_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_NAME_REPRESENTATIONS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/logical_name_tree.hpp"
#include "dogen.identification/types/helpers/pretty_printer.hpp"
#include "dogen.identification/types/entities/qualified_name_representations.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Builds a fully qualified representation of a qualifiable
 * model element such as a name or a name tree.
 */
class name_representations_builder final {
public:
    name_representations_builder();

public:
    /**
     * @brief Adds the qualifiable model element to the pretty printers.
     */
    /**@{*/
    void add(const entities::logical_name& n);
    void add(const entities::logical_name_tree& nt);
    /**@}*/

public:
    /**
     * @brief Builds the representations.
     *
     * @pre Add must have been called at least once.
     */
    entities::qualified_name_representations build();

    /**
     * @brief Builds the representation for the supplied name.
     */
    entities::qualified_name_representations
    build(const entities::logical_name& n, const bool model_name_mode);

private:
    pretty_printer dot_printer_;
    pretty_printer colon_printer_;
};

}

#endif
