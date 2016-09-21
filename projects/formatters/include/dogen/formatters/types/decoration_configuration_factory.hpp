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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_CONFIGURATION_FACTORY_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_CONFIGURATION_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/decoration_annotations.hpp"
#include "dogen/formatters/types/decoration_configuration.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Creates the file configuration by extracting information from
 * meta-data and then post-processing it.
 */
class decoration_configuration_factory {
public:
    decoration_configuration_factory() = delete;
    decoration_configuration_factory(
        const decoration_configuration_factory&) = default;
    decoration_configuration_factory(
        decoration_configuration_factory&&) = default;
    ~decoration_configuration_factory() = default;

public:
    explicit decoration_configuration_factory(const repository& rp);
    decoration_configuration_factory(const repository& rp,
        const decoration_annotations& fallback);

private:
    /**
     * @brief Obtains the licence text.
     */
    boost::optional<std::string>
    get_licence_text(const decoration_annotations& fa) const;

    /**
     * @brief Obtains a licence.
     */
    boost::optional<licence>
    get_licence(const decoration_annotations& fa) const;

    /**
     * @brief Obtains the modeline group name.
     */
    boost::optional<modeline_group>
    get_modeline_group(const decoration_annotations& fa) const;

    /**
     * @brief Returns the modeline for the supplied modeline name.
     *
     * @pre Modeline name must exist.
     */
    modeline get_modeline_from_group(const std::string& modeline_name,
        const modeline_group& mg) const;

    /**
     * @brief Obtains the modeline given a modeline name.
     */
    boost::optional<modeline>
    get_modeline(const std::string& modeline_name,
        const decoration_annotations& fa) const;

    /**
     * @brief Obtains a code generation marker.
     */
    boost::optional<std::string>
    get_marker(const decoration_annotations& fa) const;

    /**
     * @brief Obtains the marker from the file annotations; if none is
     * found, uses the default.
     */
    std::string get_marker_or_default(const decoration_annotations& fa) const;

    /**
     * @brief Obtains the generate preamble; if none is found, uses
     * the default value.
     */
    bool
    get_generate_preamble_or_default(const decoration_annotations& fa) const;

public:
    /**
     * @brief Generates the file configuration.
     */
    decoration_configuration make(const std::string& modeline_name,
        const decoration_annotations& fa) const;

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
