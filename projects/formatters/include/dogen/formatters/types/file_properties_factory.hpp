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
#ifndef DOGEN_FORMATTERS_TYPES_FILE_PROPERTIES_FACTORY_HPP
#define DOGEN_FORMATTERS_TYPES_FILE_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/formatters/types/file_properties.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/repository.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Creates the file properties by extracting information from
 * meta-data and then post-processing it.
 */
class file_properties_factory {
public:
    file_properties_factory() = delete;
    file_properties_factory(const file_properties_factory&) = default;
    file_properties_factory(file_properties_factory&&) = default;
    ~file_properties_factory() = default;

public:
    /**
     * @brief Initialise a new file properties factory.
     *
     * @param rp where to look up reference data.
     */
    explicit file_properties_factory(const repository& rp);

    /**
     * @brief Initialise a new file properties factory.
     *
     * @param rp where to look up reference data.
     * @param fallback object to use to construct defaults, if any.
     */
    file_properties_factory(const repository& rp,
        const dynamic::object& fallback);

private:
    /**
     * @brief Extracts the licence text from the dynamic object.
     */
    boost::optional<std::string>
    extract_licence_text(const dynamic::object& o) const;

    /**
     * @brief Extracts the copyright notices from the dynamic object.
     */
    boost::optional<std::list<std::string>>
    extract_copyright_notices(const dynamic::object& o) const;

    /**
     * @brief Extracts a licence from the dynamic object.
     */
    boost::optional<licence>
    extract_licence(const dynamic::object& o) const;

    /**
     * @brief Extracts the modeline group name from the dynamic object.
     */
    boost::optional<modeline_group>
    extract_modeline_group(const dynamic::object& o) const;

    /**
     * @brief Returns the modeline for the supplied modeline name.
     *
     * @pre Modeline name must exist.
     */
    modeline get_modeline_from_group(const std::string& modeline_name,
        const modeline_group& mg) const;

    /**
     * @brief Extracts a modeline the dynamic object.
     */
    boost::optional<modeline>
    extract_modeline(const std::string& modeline_name,
        const dynamic::object& o) const;

    /**
     * @brief Extracts a code generation marker the dynamic object.
     */
    boost::optional<std::string>
    extract_marker(const dynamic::object& o) const;

    /**
     * @brief Extracts the marker from the supplied dynamic object; if
     * none is found, uses the default marker.
     */
    std::string
    extract_marker_or_default(const dynamic::object& o) const;

    /**
     * @brief Extracts the generate preamble field.
     */
    boost::optional<bool>
    extract_generate_preamble(const dynamic::object& o) const;

    /**
     * @brief Extracts the generate preamble; if none is found, uses
     * the default value.
     */
    bool extract_generate_preamble_or_default(
        const dynamic::object& o) const;

public:
    /**
     * @brief Generates file properties from the dynamic object.
     */
    file_properties make(const std::string& modeline_name,
        const dynamic::object& o) const;

private:
    const repository& repository_;
    const boost::optional<std::string> default_licence_text_;
    const boost::optional<std::list<std::string>> default_copyright_notices_;
    const boost::optional<modeline_group> default_modeline_group_;
    const boost::optional<std::string> default_marker_;
    const boost::optional<bool> default_generate_preamble_;
};

} }

#endif
