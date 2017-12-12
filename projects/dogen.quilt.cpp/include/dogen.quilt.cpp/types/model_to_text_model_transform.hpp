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
#ifndef DOGEN_QUILT_CPP_TYPES_MODEL_TO_TEXT_MODEL_TRANSFORM_HPP
#define DOGEN_QUILT_CPP_TYPES_MODEL_TO_TEXT_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.annotations/types/annotation.hpp"
#include "dogen.annotations/types/type_repository.hpp"
#include "dogen.annotations/types/annotation_factory.hpp"
#include "dogen.yarn/types/meta_model/model.hpp"
#include "dogen.yarn/types/transforms/model_to_text_model_transform_interface.hpp"
#include "dogen.quilt.cpp/types/formatters/repository.hpp"
#include "dogen.quilt.cpp/types/formattables/locator.hpp"
#include "dogen.quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {

/**
 * @brief Implements a C++ model to text transform.
 */
class model_to_text_model_transform final :
        public yarn::transforms::model_to_text_model_transform_interface {
public:
    model_to_text_model_transform() = default;
    model_to_text_model_transform(
        const model_to_text_model_transform&) = delete;
    model_to_text_model_transform(model_to_text_model_transform&&) = default;

public:

    ~model_to_text_model_transform() noexcept;

private:
    /**
     * @brief Get the formatters repository.
     */
    const formatters::repository& formatters_repository() const;

    /**
     * @brief Create the formattables representation of the yarn model.
     */
    formattables::model create_formattables_model(
        const annotations::type_repository& atrp,
        const annotations::annotation& ra,
        const formatters::repository& frp, const formattables::locator& l,
        const yarn::meta_model::model& m) const;

    /**
     * @brief Creates a file locator.
     */
    formattables::locator make_locator(const yarn::transforms::options& o,
        const annotations::type_repository& atrp,
        const annotations::annotation& ra, const formatters::repository& frp,
        const bool enable_backend_directories,
        const yarn::meta_model::model& m) const;

    /**
     * @brief Create the files representation of the formattables model.
     */
    std::list<yarn::meta_model::artefact>
    format(const std::unordered_set<yarn::meta_model::element_archetype>&
        enabled_archetype_for_element, const annotations::type_repository& atrp,
        const annotations::annotation_factory& af,
        const dogen::formatters::repository& drp,
        const formattables::model& fm) const;

    /**
     * @brief Creates a list of all the managed directories.
     */
    std::list<boost::filesystem::path>
    managed_directories(const formattables::locator& l) const;

public:
    std::string id() const override;

    const std::forward_list<annotations::archetype_location>&
    archetype_locations() const override;

    const std::unordered_map<std::string,
                             annotations::archetype_locations_group>&
    archetype_locations_by_meta_name() const override;

    const std::unordered_map<std::string,
                             std::list<annotations::archetype_location>>&
    archetype_locations_by_family() const override;

    const annotations::archetype_location_repository_parts&
    archetype_location_repository_parts() const override;

    yarn::meta_model::languages language() const override;

    std::unordered_map<std::string,
                       yarn::meta_model::intra_backend_segment_properties>
    intra_backend_segment_properties(
        const yarn::transforms::options& o) const override;

    yarn::meta_model::text_model
    transform(const yarn::transforms::context& ctx,
        const bool enable_backend_directories,
        const yarn::meta_model::model& m) const override;
};

} } }

#endif
