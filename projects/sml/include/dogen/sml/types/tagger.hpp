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
#ifndef DOGEN_SML_TYPES_TAGGER_HPP
#define DOGEN_SML_TYPES_TAGGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include "dogen/config/types/cpp_settings.hpp"

#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Generate all meta data tags across the model.
 */
class tagger {
public:
    tagger() = default;
    ~tagger() noexcept = default;
    tagger(const tagger&) = default;
    tagger(tagger&&) = default;

private:
    /**
     * @brief Tag the model with all the options chosen in the
     * application settings.
     *
     * This ensures backwards compatibility until we remove these
     * options from the configuration model.
     */
    void from_settings(const config::cpp_settings& s, model& m) const;

    /**
     * @brief Returns true if the facet is enabled in the settings,
     * false otherwise.
     */
    bool is_facet_enabled(
        const std::set<config::cpp_facet_types> enabled_facets,
        const config::cpp_facet_types facet) const;

    /**
     * @brief Returns the file name for the given qname and facet.
     */
    std::string filename_for_qname(const model& m,
        const bool split_project,
        const bool is_header, const qname& qn,
        const std::string& facet_directory,
        const std::string& facet_postfix,
        const std::string& additional_postfix,
        const std::string& extension) const;

    /**
     * @brief Adds meta-data to the type supplied.
     */
    void tag_type(type& t) const;

public:
    /**
     * @brief Adds meta-data to the model supplied.
     */
    void tag(model& m) const;

    /**
     * @brief Adds meta-data to the model supplied.
     *
     * @deprecated This method is only made available for backwards
     * compatibility.
     */
    void tag(const config::cpp_settings& s, model& m) const;
};

} }

#endif
