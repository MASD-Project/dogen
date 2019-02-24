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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_CHAIN_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"
#include "masd.dogen.extraction/types/decoration_properties_factory.hpp"
#include "masd.dogen.extraction/types/meta_model/model.hpp"
#include "masd.dogen.generation/types/transforms/model_to_text_model_transform_registrar.hpp"

namespace masd::dogen::generation::transforms {

class model_to_text_model_chain final {
public:
    /**
     * @brief Registrar that keeps track of the available transforms.
     */
    static model_to_text_model_transform_registrar& registrar();

private:
    /*
     * Merges source into destination.
     */
    static void merge(extraction::meta_model::model&& src,
        extraction::meta_model::model& dst);

public:
    static extraction::meta_model::model
    transform(const coding::transforms::context& ctx,
        const coding::meta_model::model& m);
    static extraction::meta_model::model
    transform(const coding::transforms::context& ctx,
        const std::list<coding::meta_model::model>& models);

private:
    static std::shared_ptr<model_to_text_model_transform_registrar> registrar_;
};

/*
 * Helper method to register transforms.
 */
template<typename Transform>
inline void register_transform() {
    auto t(std::make_shared<Transform>());
    auto& rg(model_to_text_model_chain::registrar());
    rg.register_transform(t);
}

}

#endif
