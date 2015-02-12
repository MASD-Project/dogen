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
#ifndef DOGEN_CPP_TYPES_SETTINGS_LOCAL_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_LOCAL_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/indexer.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/local_settings.hpp"
#include "dogen/cpp/types/settings/local_formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Generates the local settings for all types in a model.
 */
class local_settings_factory {
public:
    local_settings_factory() = default;
    local_settings_factory(const local_settings_factory&) = default;
    local_settings_factory(local_settings_factory&&) = default;
    ~local_settings_factory() = default;

public:
    /**
     * @brief Generate local settings.
     */
    std::unordered_map<std::string, local_settings>
    make(const dogen::formatters::general_settings_factory&
        general_settings_factory, const dynamic::indexer& idx,
        const sml::model& m) const;
};

} } }

#endif
