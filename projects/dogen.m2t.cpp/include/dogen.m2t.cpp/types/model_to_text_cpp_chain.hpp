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
#ifndef DOGEN_M2T_CPP_TYPES_MODEL_TO_TEXT_CPP_CHAIN_HPP
#define DOGEN_M2T_CPP_TYPES_MODEL_TO_TEXT_CPP_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.m2t/types/entities/model.hpp"
#include "dogen.m2t/types/transforms/model_to_text_technical_space_chain.hpp"
#include "dogen.m2t.cpp/types/transforms/repository.hpp"
#include "dogen.m2t.cpp/types/formattables/locator.hpp"
#include "dogen.m2t.cpp/types/formattables/model.hpp"

namespace dogen::m2t::cpp {

/**
 * @brief Implements a C++ model to text transform.
 */
class model_to_text_cpp_chain final
    : public m2t::transforms::model_to_text_technical_space_chain {
public:
    model_to_text_cpp_chain() = default;
    model_to_text_cpp_chain(
        const model_to_text_cpp_chain&) = delete;
    model_to_text_cpp_chain(
        model_to_text_cpp_chain&&) = default;

public:
    ~model_to_text_cpp_chain() noexcept;

private:
    /**
     * @brief Get the formatters repository.
     */
    const transforms::repository& formatters_repository() const;

    /**
     * @brief Create the formattables representation of the yarn model.
     */
    formattables::model create_formattables_model(
        const variability::entities::feature_model& feature_model,
        const variability::entities::configuration& rcfg,
        const transforms::repository& frp, const formattables::locator& l,
        const m2t::entities::model& m) const;

    /**
     * @brief Creates a file locator.
     */
    formattables::locator make_locator(
        const boost::filesystem::path& output_directory_path,
        const variability::entities::feature_model& fm,
        const variability::entities::configuration& cfg,
        const transforms::repository& frp,
        const bool enable_backend_directories,
        const m2t::entities::model& m) const;

    /**
     * @brief Create the files representation of the formattables model.
     */
    void apply(const std::unordered_set<m2t::entities::element_archetype>&
        enabled_archetype_for_element, const formattables::locator& l,
        const variability::entities::feature_model& feature_model,
        const variability::helpers::configuration_factory& cf,
        formattables::model& fm) const;

    /**
     * @brief Creates a list of all the managed directories.
     */
    std::list<boost::filesystem::path>
    managed_directories(const formattables::locator& l) const;

public:
    std::string id() const override;
    std::string description() const override;

public:
    const std::forward_list<physical::entities::meta_name>&
    physical_meta_names() const override;

    const std::unordered_map<std::string,
                             physical::entities::meta_name_group>&
    physical_meta_names_by_logical_meta_name() const override;

    const std::unordered_map<std::string,
                             std::list<physical::entities::meta_name>>&
    physical_meta_names_by_family() const override;

    const physical::entities::meta_name_repository_parts&
    physical_meta_name_repository_parts() const override;

public:
    logical::entities::technical_space technical_space() const override;

    void apply(const m2t::transforms::context& ctx,
        const bool enable_backend_directories,
        m2t::entities::model& m) const override;
};

}

#endif
