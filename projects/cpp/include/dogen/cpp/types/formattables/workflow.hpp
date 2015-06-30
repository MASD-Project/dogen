/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/cpp/types/settings/opaque_settings_builder.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository_factory.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates a list of formattables from a given container of
 * SML elements.
 */
class workflow {
private:
    /**
     * @brief Creates the path settings.
     */
    std::unordered_map<std::string, settings::path_settings>
    create_path_settings_activity(const dynamic::repository& srp,
        const dynamic::object& root_object,
        const formatters::container& fc) const;

    /**
     * @brief Create the path derivatives repository.
     */
    path_derivatives_repository create_path_derivatives_repository(
        const config::cpp_options& opts,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const sml::model& m) const;

    /**
     * @brief Creates the formatter properties.
     */
    formatter_properties_repository
    create_formatter_properties(const dynamic::repository& srp,
        const dynamic::object& root_object,
        const settings::bundle_repository& brp,
        const path_derivatives_repository& pdrp,
        const formatters::container& fc,
        const sml::model& m) const;

    /**
     * @brief Obtains the general settings of the root object
     */
    boost::optional<dogen::formatters::general_settings>
    obtain_root_object_general_settings(
        const settings::bundle_repository& brp,
        const sml::model& m) const;

    /**
     * @brief Generates all of the formattables that are sourced from
     * the transformer.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
    from_transformer_activity(const settings::opaque_settings_builder& osb,
        const settings::bundle_repository& brp,
        const formatter_properties_repository& fprp,
        const sml::model& m) const;

    /**
     * @brief Generates all of the formattables that are sourced from
     * the factory.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
    from_factory_activity(const config::cpp_options& opts,
        const boost::optional<dogen::formatters::general_settings> gs,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const formattables::path_derivatives_repository& pdrp,
        const formatter_properties_repository& fprp,
        const formatters::container& fc,
        const sml::model& m) const;

public:
    /**
     * @brief Executes the workflow.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
    execute(const config::cpp_options& opts,
        const dynamic::repository& srp,
        const dynamic::object& root_object,
        const formatters::container& fc,
        const settings::opaque_settings_builder& osb,
        const settings::bundle_repository& brp,
        const sml::model& m) const;
};

} } }

#endif
