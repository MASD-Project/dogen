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
#ifndef DOGEN_EXTERNAL_TYPES_TRANSFORMS_MODEL_GENERATION_CHAIN_HPP
#define DOGEN_EXTERNAL_TYPES_TRANSFORMS_MODEL_GENERATION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/external/types/meta_model/model.hpp"
#include "dogen/external/types/transforms/registrar.hpp"
#include "dogen/external/types/transforms/context_fwd.hpp"

namespace dogen {
namespace external {
namespace transforms {

/**
 * @brief Given the location of a supported exogenous model, it
 * obtains it and transforms it into an external model.
 */
class model_generation_chain final {
private:
    /*
     * @brief Given a path to an exogenous model, returns the
     * appropriate decoding transform for it.
     */
    static decoding_transform_interface&
    transform_for_model(const boost::filesystem::path& p);

public:
    /**
     * @brief Registrar that keeps track of the available encoding and
     * decoding transforms.
     */
    static transforms::registrar& registrar();

public:
    /**
     * @brief Apply the transform to the exogenous model at path @e p.
     *
     * @pre @e p must point to a valid file, and contain a supported
     * exogenous model.
     */
    static meta_model::model
    transform(const context& ctx, const boost::filesystem::path& p);

private:
    static std::shared_ptr<transforms::registrar> registrar_;
};

} } }

#endif
