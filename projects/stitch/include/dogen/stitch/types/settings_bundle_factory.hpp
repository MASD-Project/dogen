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
#ifndef DOGEN_STITCH_TYPES_SETTINGS_BUNDLE_FACTORY_HPP
#define DOGEN_STITCH_TYPES_SETTINGS_BUNDLE_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/stitch/types/settings_bundle.hpp"
#include "dogen/stitch/types/stitching_settings.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Creates the settings bundle.
 */
class settings_bundle_factory {
public:
    settings_bundle_factory(
        const dynamic::schema::repository& schema_repository,
        const dogen::formatters::repository& formatters_repository);

private:
    /**
     * @brief Create the general settings.
     */
    boost::optional<formatters::general_settings>
    make_general_settings(const dynamic::schema::object& o) const;

    /**
     * @brief Create the stitching settings.
     */
    stitching_settings
    make_stitching_settings(const dynamic::schema::object& o) const;

public:
    /**
     * @brief Create the settings bundle.
     */
    settings_bundle make(const dynamic::schema::object& o) const;

private:
    const dynamic::schema::repository& schema_repository_;
    const dogen::formatters::repository& formatters_repository_;
};

} }

#endif
