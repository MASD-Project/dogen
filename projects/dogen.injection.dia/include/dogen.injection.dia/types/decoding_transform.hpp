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
#ifndef DOGEN_INJECTION_DIA_TYPES_DECODING_TRANSFORM_HPP
#define DOGEN_INJECTION_DIA_TYPES_DECODING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.dia/types/diagram_fwd.hpp"
#include "dogen.injection/types/meta_model/model.hpp"
#include "dogen.injection.dia/types/grapher.hpp"
#include "dogen.injection.dia/types/validator.hpp"
#include "dogen.injection.dia/types/processed_object.hpp"
#include "dogen.injection/types/transforms/decoding_transform.hpp"

namespace dogen::injection::dia {

class decoding_transform final
    : public injection::transforms::decoding_transform {
public:
    decoding_transform() = default;
    decoding_transform(const decoding_transform&) = delete;
    ~decoding_transform() noexcept;

private:
    /**
     * @brief Converts the Dia diagram into an
     */

    std::list<processed_object>
    obtain_processed_objects(const dogen::dia::diagram& d) const;

    /**
     * @brief Transforms the entire graph of processed objects into an
     * injection model.
     */
    meta_model::model obtain_model(const std::string& name,
        const std::list<processed_object>& pos) const;

public:
    virtual std::string id() const override;
    virtual std::string description() const override;
    virtual std::string extension() const override;

    meta_model::model apply(const transforms::context& ctx,
        const boost::filesystem::path& p) override;
};

}

#endif
