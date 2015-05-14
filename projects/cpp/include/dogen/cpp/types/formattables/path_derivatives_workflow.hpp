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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PATH_DERIVATIVES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PATH_DERIVATIVES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"
#include "dogen/cpp/types/formattables/path_derivatives.hpp"
#include "dogen/cpp/types/formatters/container.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Executes the path derivatives workflow.
 */
class path_derivatives_workflow {
public:
    explicit path_derivatives_workflow(const formatters::container& c);

private:
    /**
     * @brief Obtains the root object for the model.
     */
    dynamic::schema::object
    obtain_root_object_activity(const sml::model& m) const;

    /**
     * @brief Creates the path settings.
     */
    std::unordered_map<std::string, settings::path_settings>
    create_path_settings_activity(const config::cpp_options& opts,
        const dynamic::schema::repository& rp,
        const dynamic::schema::object& o) const;

    /**
     * @brief Obtains all path derivatives for the supplied model.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, path_derivatives>
    >
    obtain_path_derivatives_activity(
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const sml::model& m) const;

public:
    /**
     * @brief Execute the workflow.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, path_derivatives>
    >
    execute(const config::cpp_options& opts,
        const dynamic::schema::repository& rp, const sml::model& m) const;

private:
    const formatters::container& container_;
};

} } }

#endif
