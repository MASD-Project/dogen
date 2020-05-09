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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_REPOSITORY_FACTORY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/helpers/decoration_repository.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Builds the repository with all of the decoration
 * information.
 */
class decoration_repository_factory final {
private:
    /**
     * @brief Processes a licence.
     */
    void handle_licence(
        const boost::shared_ptr<entities::decoration::licence> l,
        decoration_repository& drp) const;

    /**
     * @brief Processes a generation marker.
     */
    void handle_generation_marker(
        const boost::shared_ptr<entities::decoration::generation_marker> gm,
        decoration_repository& drp) const;

    /**
     * @brief Organises all modelines by modeline group and by
     * technical space.
     */
    void handle_modeline_group(
        const boost::shared_ptr<entities::decoration::modeline_group> mg,
        decoration_repository& drp) const;

public:
    /**
     * @brief Applies the transform to all decoration entities in the
     * model.
     */
    decoration_repository make(const entities::model& m) const;
};

}

#endif
