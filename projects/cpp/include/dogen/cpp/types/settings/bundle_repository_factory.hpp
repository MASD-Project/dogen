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
#ifndef DOGEN_CPP_TYPES_SETTINGS_BUNDLE_REPOSITORY_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_BUNDLE_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/cpp/types/settings/opaque_settings_builder.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Creates the bundle repository.
 */
class bundle_repository_factory {
public:
    /**
     * @brief Create the bundle repository.
     */
    bundle_repository make(const dynamic::repository& rp,
        const dynamic::object& root_object,
        const dogen::formatters::general_settings_factory& gsf,
        const opaque_settings_builder& osb,
        const sml::model& m) const;
};

} } }

#endif
