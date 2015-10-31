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
#ifndef DOGEN_CPP_TYPES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/backend/types/backend_interface.hpp"
#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/cpp/types/settings/opaque_settings_builder.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the c++ backend workflow.
 */
class workflow final : public backend::backend_interface {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;

public:
    ~workflow() noexcept;

private:
    /**
     * @brief Returns the root object.
     */
    dynamic::object obtain_root_object(const yarn::intermediate_model& m) const;

private:
    /**
     * @brief Creates the formatters' repository.
     */
    dogen::formatters::repository create_formatters_repository(
        const std::forward_list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Create the general settings factory.
     */
    dogen::formatters::general_settings_factory create_general_settings_factory(
        const dogen::formatters::repository& frp,
        const dynamic::object& root_object) const;

    /**
     * @brief Creates the opaque settings builder.
     */
    settings::opaque_settings_builder
        create_opaque_settings_builder(const dynamic::repository& rp) const;

    /**
     * @brief Create the bundle repository
     */
    settings::bundle_repository create_bundle_repository(
        const dynamic::repository& rp, const dynamic::object& root_object,
        const dogen::formatters::general_settings_factory& gsf,
        const settings::opaque_settings_builder& osb,
        const yarn::intermediate_model& m) const;

    /**
     * @brief Create the formattables.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
        create_formattables_activty(const config::cpp_options& opts,
            const dynamic::repository& srp,
            const dynamic::object& root_object,
            const dogen::formatters::general_settings_factory& gsf,
            const formatters::container& fc,
            const settings::opaque_settings_builder& osb,
            const settings::bundle_repository& brp,
            const yarn::intermediate_model& m) const;

    /**
     * @brief Create the files.
     */
    std::forward_list<dogen::formatters::file>
    format_activty(const std::forward_list<
            std::shared_ptr<formattables::formattable>
            >& f) const;

public:
    std::string name() const override;

    std::forward_list<boost::filesystem::path>
    managed_directories(const config::knitting_options& ko,
        const dynamic::repository& rp,
        const yarn::intermediate_model& m) const override;

    std::forward_list<dynamic::ownership_hierarchy> ownership_hierarchy() const;

    std::forward_list<dogen::formatters::file> generate(
        const config::knitting_options& ko,
        const dynamic::repository& rp,
        const yarn::intermediate_model& m) const override;
};

} }

#endif
