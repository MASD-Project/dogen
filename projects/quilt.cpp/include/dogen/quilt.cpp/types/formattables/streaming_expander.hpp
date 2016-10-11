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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_STREAMING_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_STREAMING_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/annotations/types/field_definition.hpp"
#include "dogen/quilt.cpp/types/formattables/streaming_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class streaming_expander {
private:
    struct field_definitions {
        annotations::field_definition requires_quoting;
        annotations::field_definition string_conversion_method;
        annotations::field_definition remove_unprintable_characters;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const field_definitions& v);

    field_definitions
    make_field_definitions(const annotations::repository& drp) const;

    boost::optional<streaming_properties> make_streaming_properties(
        const field_definitions& fds, const annotations::annotation& a) const;

public:
    void expand(const annotations::repository& drp, model& fm) const;
};

} } } }

#endif
