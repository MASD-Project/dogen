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
#ifndef DOGEN_STITCH_TYPES_PROPERTIES_FACTORY_HPP
#define DOGEN_STITCH_TYPES_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen.annotations/types/annotation.hpp"
#include "dogen.annotations/types/type_repository.hpp"
#include "dogen.formatting/types/repository.hpp"
#include "dogen.formatting/types/decoration_properties.hpp"
#include "dogen.stitch/types/stitching_properties.hpp"
#include "dogen.stitch/types/properties.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Creates the settings bundle.
 */
class properties_factory {
public:
    properties_factory(const annotations::type_repository& atrp,
        const dogen::formatting::repository& frp);

private:
    /**
     * @brief Create the decoration properties.
     */
    boost::optional<formatting::decoration_properties>
    make_decoration_properties(const annotations::annotation& a) const;

    /**
     * @brief Create the stitching settings.
     */
    stitching_properties
    make_stitching_properties(const annotations::annotation& a) const;

public:
    /**
     * @brief Create the settings bundle.
     */
    properties make(const annotations::annotation& a) const;

private:
    const annotations::type_repository& annotations_repository_;
    const dogen::formatting::repository& formatting_repository_;
};

} }

#endif
