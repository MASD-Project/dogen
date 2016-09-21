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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_CONFIGURATION_WORKFLOW_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_CONFIGURATION_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/decoration_configuration.hpp"
#include "dogen/formatters/types/decoration_annotations_factory.hpp"
#include "dogen/formatters/types/decoration_configuration_factory.hpp"

namespace dogen {
namespace formatters {

class decoration_configuration_workflow {
public:
    /**
     * @brief Initialise a new file configuration workflow, without
     * access to fallbacks. This constructor is used by stitch.
     *
     * @param rp where to look up reference data.
     */
    explicit decoration_configuration_workflow(const dynamic::repository& drp,
        const repository& rp);

    /**
     * @brief Initialise a new file configuration workflow, with access
     * to fallbacks. This constructor is used by quilt.cpp.
     *
     * @param rp where to look up reference data.
     * @param fallback object to use to construct defaults, if any.
     */
    decoration_configuration_workflow(const dynamic::repository& drp,
        const repository& rp,
        const dynamic::object& fallback);

public:
    /**
     * @brief Generates file configuration from the dynamic object.
     */
    /**@{*/
    decoration_configuration execute(const std::string& modeline_name) const;
    decoration_configuration execute(const std::string& modeline_name,
        const dynamic::object& o) const;
    /**@}*/

private:
    const decoration_annotations_factory annotations_factory_;
    const decoration_configuration_factory configuration_factory_;
};

} }

#endif
