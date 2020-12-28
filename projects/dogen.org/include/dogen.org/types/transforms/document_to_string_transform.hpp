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
#ifndef DOGEN_ORG_TYPES_TRANSFORMS_DOCUMENT_TO_STRING_TRANSFORM_HPP
#define DOGEN_ORG_TYPES_TRANSFORMS_DOCUMENT_TO_STRING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.org/types/entities/drawer.hpp"
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.org/types/entities/document.hpp"

namespace dogen::org::transforms {

/**
 * @brief Converts an org model document into a string.
 */
class document_to_string_transform final {
private:
    static void render_drawers(std::ostream& os,
        const unsigned int level,
        const std::list<entities::drawer>& ds);
    static void render_section(std::ostream& os,
        const entities::section& sec);
    static void render_headline(std::ostream& os, const entities::headline& h);

public:
    static std::string apply(boost::shared_ptr<tracing::tracer> tracer,
        const entities::document& doc);
};

}

#endif
