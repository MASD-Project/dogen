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
#ifndef DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_ARTEFACT_FORMATTER_INTERFACE_HPP
#define DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_ARTEFACT_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <typeindex>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text.csharp/types/formattables/locator.hpp"
#include "dogen.text/types/transforms/model_to_text_transform.hpp"
#include "dogen.text.csharp/types/transforms/context.hpp"

namespace dogen::text::csharp::transforms {

class model_to_text_transform : public text::transforms::model_to_text_transform {
public:
    model_to_text_transform() = default;
    model_to_text_transform(model_to_text_transform&&) = default;
    model_to_text_transform(const model_to_text_transform&) = delete;
    virtual ~model_to_text_transform() noexcept {}

public:
    /**
     * @brief Provides the full path.
     */
    virtual boost::filesystem::path full_path(const formattables::locator& l,
        const logical::entities::name& n) const = 0;

    /**
     * @brief Creates the inclusion dependencies for this formatter
     * against the supplied element.
     */
    virtual std::list<std::string>
    inclusion_dependencies(const logical::entities::element& e) const = 0;

public:
    /**
     * @brief Generate a physical representation of the logical
     * element.
     */
    virtual void apply(const context& ctx, const logical::entities::element& e,
        physical::entities::artefact& a) const = 0;
};

}

#endif
