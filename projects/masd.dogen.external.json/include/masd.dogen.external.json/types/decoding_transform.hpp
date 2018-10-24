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
#ifndef MASD_DOGEN_EXTERNAL_JSON_TYPES_DECODING_TRANSFORM_HPP
#define MASD_DOGEN_EXTERNAL_JSON_TYPES_DECODING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "masd.dogen.external/types/meta_model/model.hpp"
#include "masd.dogen.external/types/transforms/decoding_transform_interface.hpp"

namespace masd::dogen::external::json {

class decoding_transform final
    : public transforms::decoding_transform_interface {
public:
    decoding_transform() = default;
    decoding_transform(const decoding_transform&) = delete;
    ~decoding_transform() noexcept;

public:
    std::string extension() const;

    meta_model::model transform(const transforms::context& ctx,
        const boost::filesystem::path& p);
};

}

#endif
