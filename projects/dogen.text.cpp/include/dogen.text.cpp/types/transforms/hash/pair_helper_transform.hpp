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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_HASH_PAIR_HELPER_TRANSFORM_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_HASH_PAIR_HELPER_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.text.cpp/types/transforms/helper_transform.hpp"

namespace dogen::text::cpp::transforms::hash {

class pair_helper_transform final : public helper_transform {
public:
    std::string id() const override;
    std::string family() const override;
    std::list<std::string> owning_formatters() const override;
    std::list<std::string> owning_facets() const override;
    std::string helper_name() const override;
    bool is_enabled(const assistant& a,
        const logical::entities::helper_properties& hc) const override;
    void apply(assistant& a,
        const logical::entities::helper_properties& hc) const override;
};

}

#endif
