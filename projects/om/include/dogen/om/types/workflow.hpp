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
#ifndef DOGEN_OM_TYPES_WORKFLOW_HPP
#define DOGEN_OM_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/property_cache.hpp"
#include "dogen/om/types/file.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/modeline_group.hpp"

namespace dogen {
namespace om {

/**
 * @brief Executes a complete workflow for the output model.
 */
class workflow {
public:
    workflow(const workflow&) = default;
    workflow(workflow&&) = default;
    ~workflow() = default;

public:
    explicit
    workflow(const std::list<boost::filesystem::path>& data_files_directories);

private:
    class context {
    public:
        sml::property_cache& property_cache() { return property_cache_; }

        const std::unordered_map<std::string, modeline_group>&
        modeline_groups() { return modeline_groups_; }

        void modeline_groups(
            const std::unordered_map<std::string, modeline_group>& v) {
            modeline_groups_ = v;
        }

        const std::unordered_map<std::string, licence>& licences() const {
            return licences_;
        }

        void licences(const std::unordered_map<std::string, licence>& v) {
            licences_ = v;
        }

        std::string code_generation_marker() { return code_generation_marker_; }

        void code_generation_marker(const std::string& v) {
            code_generation_marker_ = v;
        }

        std::list<file>& files() { return files_; }

    private:
        sml::property_cache property_cache_;
        std::unordered_map<std::string, modeline_group> modeline_groups_;
        std::unordered_map<std::string, licence> licences_;
        std::string code_generation_marker_;
        std::list<file> files_;
    };

    /**
     * @brief Throws if context is null.
     */
    void ensure_non_null_context() const;

private:
    /**
     * @brief Throws an exception due to a missing item.
     *
     * Required because the template functions do not have access to
     * the logger.
     */
    void throw_missing_item(const std::string& msg, const std::string& n) const;

    /**
     * @brief Extracts a licence using meta-data in the Taggable.
     */
    template<typename Taggable>
    licence extract_licence(const Taggable& t) const {
        ensure_non_null_context();
        auto adaptor(sml::make_tag_adaptor(t));

        const auto licence_name(adaptor.get(sml::tags::licence_name));
        const auto i(context_->licences().find(licence_name));
        if (i == context_->licences().end())
            throw_missing_item("Licence not found: ", licence_name);

        auto licence(i->second);
        if (adaptor.has_key(sml::tags::copyright_holder)) {
            const auto copyright_holder(adaptor.get(sml::tags::copyright_holder));
            licence.copyright_holders().push_back(copyright_holder);
        }
        return licence;
    }

    /**
     * @brief Extracts a modeline using meta-data in the Taggable.
     */
    template<typename Taggable>
    modeline extract_modeline(const Taggable& t) const {
        ensure_non_null_context();
        auto adaptor(sml::make_tag_adaptor(t));

        const auto name(adaptor.get(sml::tags::modeline_group_name));
        const auto i(context_->modeline_groups().find(name));
        if (i == context_->modeline_groups().end())
            throw_missing_item("Modeline group not found: ", name);

        const auto modeline_group(i->second);
        const auto j(modeline_group.modelines().find("c++"));
        if (j == modeline_group.modelines().end())
            throw_missing_item("Modeline not found: ", name);

        return j->second;
    }

    /**
     * @brief Extracts a code generation marker using meta-data in the
     * Taggable.
     */
    template<typename Taggable>
    std::string extract_marker(const Taggable& t) const {
        auto adaptor(sml::make_tag_adaptor(t));

        if (adaptor.has_key(sml::tags::code_generation_marker))
            return adaptor.get(sml::tags::code_generation_marker);

        return context_->code_generation_marker();
    }

private:
    /**
     * @brief Creates the actual list of directories used by hydrators
     * to load data.
     */
    std::list<boost::filesystem::path>
    create_directories(const std::string for_whom) const;

    /**
     * @brief Hydrates all the modelines available in the library.
     */
    void hydrate_modelines_activity();

    /**
     * @brief Hydrates all the licences available in the library.
     */
    void hydrate_licences_activity();

    /**
     * @brief Creates the code generation marker.
     */
    void create_marker_activity(const sml::model& m);

    /**
     * @brief Loads all external data such as modelines, licences, etc
     * and sets up any required data structures.
     */
    void setup_reference_data_subworkflow(const sml::model& m);

public:
    /**
     * @brief Process types.
     */
    void operator()(const sml::type& t) const;

    /**
     * @brief Process modules.
     */
    void operator()(const sml::module& m) const;

    /**
     * @brief Process concepts.
     */
    void operator()(const sml::concept& c) const;

public:
    /**
     * @brief Handle the model itself as a module.
     *
     * @deprecated this is required only until we generate a module
     * for the model.
     */
    void model_file_subworkflow(const sml::model& model);

public:
    /**
     * @brief Run the entire output model workflow.
     */
    std::list<file> execute(const sml::model& m);

private:
    const std::list<boost::filesystem::path> data_files_directories_;
    mutable std::unique_ptr<context> context_;
};

} }

#endif
