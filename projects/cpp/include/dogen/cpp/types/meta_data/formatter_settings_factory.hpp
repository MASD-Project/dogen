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
#ifndef DOGEN_CPP_TYPES_META_DATA_FORMATTER_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_META_DATA_FORMATTER_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include "dogen/cpp/types/formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace meta_data {

class formatter_settings_factory {
public:
    formatter_settings_factory() = default;
    formatter_settings_factory(const formatter_settings_factory&) = default;
    formatter_settings_factory(formatter_settings_factory&&) = default;
    ~formatter_settings_factory() = default;

private:
    /**
     * @brief Reads the settings from the meta-data for the supplied
     * formatter id.
     *
     * @pre formatter id is not qualified.
     */
    formatter_settings read_settings(const formatter_settings& default_settings,
        const std::string& formatter_id,
        const boost::property_tree::ptree& meta_data) const;

public:
    /**
     * @brief Builds the formatter settings from the meta data.
     */
    std::unordered_map<std::string, formatter_settings> build(
        const std::unordered_map<std::string, formatter_settings>&
        default_formatter_settings_by_formatter_id,
        const boost::property_tree::ptree& meta_data) const;
};

} } }

#endif
