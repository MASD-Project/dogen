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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_TEXT_TO_TEXT_CHAIN_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_TEXT_TO_TEXT_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include "dogen.text/types/entities/model.hpp"
#include "dogen.text/types/transforms/context_fwd.hpp"
#include "dogen.text/types/transforms/text_to_text_transform_registrar.hpp"

namespace dogen::text::transforms {

/**
 * @brief Chain responsible for orchestrating all T2T transforms.
 */
class text_to_text_chain final {
public:
    /**
     * @brief Registrar that keeps track of the available transforms.
     */
    static text_to_text_transform_registrar& registrar();

public:
    static void apply(const text::transforms::context& ctx,
        text::entities::model& m);

private:
    static std::shared_ptr<text_to_text_transform_registrar> registrar_;
};

/*
 * Helper method to register transforms.
 */
template<typename Transform>
inline void register_transform() {
    auto t(std::make_shared<Transform>());
    auto& rg(text_to_text_chain::registrar());
    rg.register_transform(t);
}

}

#endif
