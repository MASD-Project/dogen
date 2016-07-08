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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_WORKFLOW_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <utility>
#include <forward_list>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/file_properties_workflow.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_repository.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/properties/formattable.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_repository.hpp"
#include "dogen/quilt.cpp/types/properties/element_properties_repository.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

/**
 * @brief Generates a list of properties from a given container of
 * Yarn elements.
 */
class workflow {
private:
    /**
     * @brief Creates the path settings.
     */
    std::unordered_map<std::string, settings::path_settings>
    create_path_settings_activity(const dynamic::repository& drp,
        const dynamic::object& root_object,
        const formatters::container& fc) const;

    /**
     * @brief Create the helper settings repository.
     */
    settings::helper_settings_repository create_helper_settings_repository(
        const dynamic::repository& drp, const yarn::model& m) const;

    /**
     * @brief Create the path derivatives repository.
     */
    path_derivatives_repository create_path_derivatives_repository(
        const config::cpp_options& opts,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const yarn::model& m) const;

    /**
     * @brief Creates the formatter properties.
     */
    formatter_properties_repository
    create_formatter_properties(const dynamic::repository& drp,
        const dynamic::object& root_object,
        const settings::element_settings_repository& esrp,
        const path_derivatives_repository& pdrp,
        const formatters::container& fc,
        const yarn::model& m) const;

    /**
     * @brief Generates all of the properties that are sourced from
     * the transformer.
     */
    std::forward_list<std::shared_ptr<properties::formattable> >
    from_transformer_activity(const yarn::model& m) const;

    /**
     * @brief Generates all of the properties that are sourced from
     * the factory.
     */
    std::forward_list<std::shared_ptr<properties::formattable> >
    from_factory_activity(const config::cpp_options& opts,
        const dogen::formatters::file_properties_workflow& fpwf,
        settings::element_settings_repository& esrp,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const properties::path_derivatives_repository& pdrp,
        formatter_properties_repository& fprp,
        const formatters::container& fc,
        const yarn::model& m) const;

    element_properties_repository create_element_properties(
        const dogen::formatters::file_properties_workflow& fpwf,
        const settings::helper_settings_repository& hsrp,
        const formatter_properties_repository& fprp,
        const yarn::model& m) const;

public:
    /**
     * @brief Executes the workflow.
     */
    std::pair<
        element_properties_repository,
        std::forward_list<std::shared_ptr<formattable> >
    >
    execute(const config::cpp_options& opts,
        const dynamic::repository& drp,
        const dynamic::object& root_object,
        const dogen::formatters::file_properties_workflow& fpwf,
        const formatters::container& fc,
        settings::element_settings_repository& esrp,
        const yarn::model& m) const;
};

} } } }

#endif
