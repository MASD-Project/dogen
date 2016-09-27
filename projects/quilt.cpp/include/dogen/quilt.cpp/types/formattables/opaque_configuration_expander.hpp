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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_OPAQUE_CONFIGURATION_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_OPAQUE_CONFIGURATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_builder.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class opaque_configuration_expander {
private:
    annotations::opaque_annotations_builder
    create_opaque_annotations_builder(const dynamic::repository& drp) const;

private:
    typedef std::unordered_map<std::string, formatter_configuration>
    formatter_configurations_type;

    void populate_opaque_configuration(
        const annotations::opaque_annotations_builder& b,
        const yarn::element& e,
        formatter_configurations_type& fmt_cfgs) const;

    void populate_opaque_configuration(
        const annotations::opaque_annotations_builder& b,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const dynamic::repository& drp,
        std::unordered_map<std::string, formattable>& formattables) const;
};

} } } }

#endif
