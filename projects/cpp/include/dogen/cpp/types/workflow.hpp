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
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/backend/types/backend_interface.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/formatters/registrar.hpp"
#include "dogen/cpp/types/settings/global_settings.hpp"
#include "dogen/cpp/types/formatters/facet.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formatters/formatter_types.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/types/formattables/file_settings.hpp"
#include "dogen/cpp/types/formattables/includes_builder_interface.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the c++ backend workflow.
 */
class workflow : public backend::backend_interface {
public:
    typedef std::unordered_map<std::string, formattables::file_settings>
    file_settings_by_formatter_type;
    typedef std::unordered_map<std::string, boost::filesystem::path>
    path_by_formatter_type;
    typedef std::unordered_map<std::string,
                               std::shared_ptr<
                                   formattables::includes_builder_interface>
                               > includes_builder_by_formatter_id;

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
     * @brief Given an SML object type, returns its corresponding
     * formatter type.
     */
    formatters::formatter_types
    formatter_type_for_object_type(const sml::object_types ot) const;

    /**
     * @brief Transforms the supplied SML elements into C++ entities.
     */
    template<typename AssociativeContainerOfElement>
    std::forward_list<std::shared_ptr<formattables::entity>>
    transform_sml_elements(
        const std::unordered_map<sml::qname,
        file_settings_by_formatter_type>&
        file_settings_by_qname_by_formatter_type, const sml::model& m,
        const AssociativeContainerOfElement& c) const {
        std::forward_list<std::shared_ptr<formattables::entity> > r;
        formattables::transformer
            t(file_settings_by_qname_by_formatter_type, m);
        for (const auto& pair : c) {
            const auto ng(sml::generation_types::no_generation);
            if (pair.second.generation_type() == ng)
                continue;

            r.push_front(t.transform(pair.second));
        }
        return r;
    }

    /**
     * @brief Formats all files for the entity.
     */
    std::forward_list<dogen::formatters::file> format_entity(
        const formatters::workflow& fw, const formattables::entity& e) const;

private:
    /**
     * @brief Returns the model's module.
     *
     * @pre there must exacly one model module
     */
    sml::module obtain_model_module_activity(const sml::model& m) const;

    /**
     * @brief Create the global settings for all facets.
     */
    std::unordered_map<std::string, settings::global_settings>
    global_settings_for_facet_activty(const sml::module& model_module) const;

    /**
     * @brief Create the formatter container.
     */
    std::unordered_map<std::string, formatters::container>
    formatter_container_for_facet_activty(const formatters::container& c) const;

    /**
     * @brief Creates all the facets
     */
    std::forward_list<formatters::facet>
    create_facets_activty(
        const std::unordered_map<std::string, formatters::container>&
        formatters_by_facet,
        const std::unordered_map<std::string, settings::global_settings>&
        global_settings_for_facet) const;

    /**
     * @brief Creates a map of includes builders by formatter id.
     */
    includes_builder_by_formatter_id
    create_includes_builder_by_formatter_id_activity(
        const formatters::container& c) const;

    /**
     * @brief Gets the relative file name for all path keys.
     */
    std::unordered_map<sml::qname, path_by_formatter_type>
    obtain_relative_file_names_for_key_activity(
        const std::forward_list<formatters::facet>& facets,
        const sml::model& m) const;

    /**
     * @brief Creates all file settings for a model.
     */
    std::unordered_map<sml::qname, file_settings_by_formatter_type>
    obtain_file_settings_activity(
        const includes_builder_by_formatter_id& includes_builders,
        const sml::model& m,
        const std::unordered_map<sml::qname, path_by_formatter_type>&
        relative_file_names_by_formatter_by_qname) const;

    /**
     * @brief Creates all the files for a given container of SML
     * elements.
     */
    template<typename AssociativeContainerOfElement>
    std::forward_list<dogen::formatters::file>
    create_files_from_sml_container_activity(
        const std::unordered_map<sml::qname,
                                 file_settings_by_formatter_type>&
        file_settings_by_qname_by_formatter_type,
        const sml::model& m,
        const formatters::workflow& fw,
        const AssociativeContainerOfElement& c) const {
        const auto entities(transform_sml_elements(
                file_settings_by_qname_by_formatter_type, m, c));
        std::forward_list<dogen::formatters::file> r;
        for (const auto e : entities)
            r.splice_after(r.before_begin(), format_entity(fw, *e));
        return r;
    }

public:
    std::string id() const override;

    std::vector<boost::filesystem::path> managed_directories() const override;

    void validate() const override;

    std::forward_list<dogen::formatters::file>
    generate(const sml::model& m) const override;

private:
    static std::shared_ptr<cpp::formatters::registrar> registrar_;
};

} }

#endif
