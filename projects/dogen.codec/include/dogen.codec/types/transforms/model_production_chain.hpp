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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_PRODUCTION_CHAIN_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_PRODUCTION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/transforms/registrar.hpp"
#include "dogen.codec/types/transforms/context_fwd.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Given the location of a supported external model, it obtains
 * it and transforms it into an codec model.
 */
class model_production_chain final {
private:
    /*
     * @brief Given a path to an external model, returns the
     * appropriate decoding transform for it.
     */
    static decoding_transform&
    transform_for_model(const boost::filesystem::path& p);

public:
    /**
     * @brief Registrar that keeps track of the available encoding and
     * decoding transforms.
     */
    static transforms::registrar& registrar();

public:
    /**
     * @brief Apply the transform to the external model at path @e p.
     *
     * @pre @e p must point to a valid file, and contain a supported
     * external model.
     */
    static entities::model
    apply(const context& ctx, const boost::filesystem::path& p);

private:
    static std::shared_ptr<transforms::registrar> registrar_;
};


/*
 * Helper method to register encoding transforms.
 */
template<typename EncodingTransform>
inline void register_encoding_transform() {
    auto& rg(model_production_chain::registrar());
    auto t(std::make_shared<EncodingTransform>());
    rg.register_encoding_transform(t);
}

/*
 * Helper method to register decoding transforms.
 */
template<typename DecodingTransform>
inline void register_decoding_transform() {
    auto& rg(model_production_chain::registrar());
    auto t(std::make_shared<DecodingTransform>());
    rg.register_decoding_transform(t);
}


}

#endif
