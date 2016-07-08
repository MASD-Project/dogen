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
#ifndef DOGEN_FORMATTERS_TYPES_FILE_PROPERTIES_WORKFLOW_HPP
#define DOGEN_FORMATTERS_TYPES_FILE_PROPERTIES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/file_properties.hpp"
#include "dogen/formatters/types/file_settings_factory.hpp"
#include "dogen/formatters/types/file_properties_factory.hpp"

namespace dogen {
namespace formatters {

class file_properties_workflow {
public:
    /**
     * @brief Initialise a new file properties workflow, without
     * access to fallbacks. This constructor is used by stitch.
     *
     * @param rp where to look up reference data.
     */
    explicit file_properties_workflow(const dynamic::repository& drp,
        const repository& rp);

    /**
     * @brief Initialise a new file properties workflow, with access
     * to fallbacks. This constructor is used by quilt.cpp.
     *
     * @param rp where to look up reference data.
     * @param fallback object to use to construct defaults, if any.
     */
    file_properties_workflow(const dynamic::repository& drp,
        const repository& rp,
        const dynamic::object& fallback);

public:
    /**
     * @brief Generates file properties from the dynamic object.
     */
    /**@{*/
    file_properties execute(const std::string& modeline_name) const;
    file_properties execute(const std::string& modeline_name,
        const dynamic::object& o) const;
    /**@}*/

private:
    const file_settings_factory settings_factory_;
    const file_properties_factory properties_factory_;
};

} }

#endif
