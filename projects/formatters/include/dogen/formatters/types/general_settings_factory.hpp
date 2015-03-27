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
#ifndef DOGEN_FORMATTERS_TYPES_GENERAL_SETTINGS_FACTORY_HPP
#define DOGEN_FORMATTERS_TYPES_GENERAL_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/repository.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Creates the general settings by extracting information from
 * meta-data.
 */
class general_settings_factory {
public:
    general_settings_factory() = delete;
    general_settings_factory(const general_settings_factory&) = default;
    general_settings_factory(general_settings_factory&&) = default;
    ~general_settings_factory() = default;

public:
    /**
     * @brief Initialise a new general settings factory.
     *
     * @param rp where to look up reference data.
     */
    explicit general_settings_factory(const repository& rp);

private:
    /*
     * @brief Throws an exception due to a missing item.
     */
    void throw_missing_item(const std::string& msg, const std::string& n) const;

private:
    /**
     * @brief Extracts a licence from the dynamic object.
     */
    boost::optional<licence>
    extract_licence(const dynamic::schema::object& o) const;

    /**
     * @brief Extracts a modeline the dynamic object.
     */
    boost::optional<modeline>
    extract_modeline(const dynamic::schema::object& o) const;

    /**
     * @brief Extracts a code generation marker the dynamic object.
     */
    std::string extract_marker(const dynamic::schema::object& o) const;

public:
    /**
     * @brief Generates general settings from the dynamic object.
     *
     * @pre load reference data must have been called.
     */
    general_settings make(const dynamic::schema::object& o) const;

private:
    const repository& repository_;
};

} }

#endif
