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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_FAKE_OPAQUE_PROPERTIES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_FAKE_OPAQUE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "masd.dogen.coding/types/meta_model/opaque_properties.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Temporary class used only to trigger inheritance generation.
 */
class fake_opaque_properties final : public masd::dogen::coding::meta_model::opaque_properties {
public:
    fake_opaque_properties() = default;
    fake_opaque_properties(const fake_opaque_properties&) = default;
    fake_opaque_properties(fake_opaque_properties&&) = default;
    fake_opaque_properties& operator=(const fake_opaque_properties&) = default;

    virtual ~fake_opaque_properties() noexcept { }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const fake_opaque_properties& rhs) const;
    bool operator!=(const fake_opaque_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::coding::meta_model::opaque_properties& other) const override;

};

}

#endif
