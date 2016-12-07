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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_ASSISTANT_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/csharp/scoped_boilerplate_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/context.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

class assistant final {
public:
    assistant(const context& ctx, const annotations::archetype_location& al,
        const std::string& id);

private:
    const formattables::artefact_properties&
    obtain_artefact_properties(const std::string& archetype) const;

public:
    /**
     * @brief Returns a scoped boilerplate formatter.
     */
    dogen::formatters::csharp::scoped_boilerplate_formatter
    make_scoped_boilerplate_formatter();

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    dogen::formatters::artefact make_artefact() const;

private:
    std::ostringstream stream_;
    const std::string element_id_;
    const context& context_;
    formattables::artefact_properties artefact_properties_;
    const annotations::archetype_location archetype_location_;
};

} } } }

#endif
