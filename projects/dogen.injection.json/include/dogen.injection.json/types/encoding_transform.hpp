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
#ifndef DOGEN_INJECTION_JSON_TYPES_ENCODING_TRANSFORM_HPP
#define DOGEN_INJECTION_JSON_TYPES_ENCODING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.injection/types/meta_model/model.hpp"
#include "dogen.injection/types/transforms/encoding_transform.hpp"

namespace dogen::injection::json {

class encoding_transform final : public transforms::encoding_transform {
public:
    encoding_transform() = default;
    encoding_transform(const encoding_transform&) = delete;
    ~encoding_transform() noexcept;

public:
    virtual std::string id() const override;
    virtual std::string description() const override;
    std::string extension() const override;

    void apply(const transforms::context& ctx,
        const meta_model::model& m, const boost::filesystem::path& p) override;
};

}

#endif
