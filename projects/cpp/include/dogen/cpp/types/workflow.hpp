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
#ifndef DOGEN_CPP_TYPES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/backend/types/backend_interface.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/formatters/registrar.hpp"
#include "dogen/cpp/types/settings/settings.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formatters/formatter_types.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"
#include "dogen/cpp/types/formattables/provider_selector_interface.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the c++ backend workflow.
 */
class workflow : public backend::backend_interface {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;

public:
    ~workflow() noexcept;

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::formatters::registrar& registrar();

private:
    /**
     * @brief Create the settings.
     */
    settings::settings create_settings_activty(
        const config::knitting_options& o,
        const std::forward_list<dynamic::field_definition>& fds,
        const sml::model& m) const;

    /**
     * @brief Create the formattables.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
    create_formattables_activty(const settings::selector& s,
        const formattables::provider_selector_interface& ps,
        const sml::model& m) const;

    /**
     * @brief Create the files.
     */
    std::forward_list<dogen::formatters::file>
    format_activty(const settings::selector& s, const formatters::container& c,
        const std::forward_list<std::shared_ptr<formattables::formattable> >&
        f) const;

public:
    std::string id() const override;

    std::vector<boost::filesystem::path> managed_directories() const override;

    void validate() const override;

    std::forward_list<dogen::formatters::file> generate(
        const config::knitting_options& o, const sml::model& m) const override;

private:
    static std::shared_ptr<cpp::formatters::registrar> registrar_;
    const std::forward_list<boost::filesystem::path> data_files_directories_;
};

} }

#endif
