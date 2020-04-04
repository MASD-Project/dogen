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
#ifndef DOGEN_M2T_CSHARP_TYPES_MODEL_TO_TEXT_CSHARP_CHAIN_HPP
#define DOGEN_M2T_CSHARP_TYPES_MODEL_TO_TEXT_CSHARP_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.m2t/types/entities/model.hpp"
#include "dogen.m2t/types/transforms/context.hpp"
#include "dogen.m2t/types/transforms/model_to_text_technical_space_chain.hpp"
#include "dogen.m2t.csharp/types/transforms/repository.hpp"
#include "dogen.m2t.csharp/types/formattables/locator.hpp"
#include "dogen.m2t.csharp/types/formattables/model.hpp"

namespace dogen::m2t::csharp {

/**
 * @brief Manages the c# backend.
 */
class model_to_text_csharp_chain final
    : public m2t::transforms::model_to_text_technical_space_chain {
public:
    model_to_text_csharp_chain() = default;
    model_to_text_csharp_chain(
        const model_to_text_csharp_chain&) = delete;
    model_to_text_csharp_chain(
        model_to_text_csharp_chain&&) = default;

public:
    ~model_to_text_csharp_chain() noexcept;

private:
    formattables::model create_formattables_model(
        const variability::entities::feature_model& feature_model,
        const transforms::repository& frp, const formattables::locator & l,
        const m2t::entities::model& m) const;

    std::list<physical::entities::artefact>
    apply(const formattables::model& fm) const;

public:
    std::string description() const override;
    std::string id() const override;

    const std::forward_list<physical::entities::meta_name>&
    physical_names() const override;

    const std::unordered_map<std::string,
                             physical::entities::meta_name_group>&
    physical_names_by_meta_name() const override;

    const std::unordered_map<std::string,
                             std::list<physical::entities::meta_name>>&
    physical_names_by_family() const override;

    const physical::entities::meta_name_repository_parts&
    physical_name_repository_parts() const override;

    logical::entities::technical_space technical_space() const override;

    physical::entities::model
    apply(const m2t::transforms::context& ctx,
        const bool enable_backend_directories,
        const m2t::entities::model& m) const override;
};

}

#endif
