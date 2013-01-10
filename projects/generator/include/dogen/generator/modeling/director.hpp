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
#ifndef DOGEN_GENERATOR_MODELING_DIRECTOR_HPP
#define DOGEN_GENERATOR_MODELING_DIRECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/generator/config/settings.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dia/types/diagram.hpp"

namespace dogen {
namespace generator {
namespace modeling {

/**
 * @brief Responsible for enacting the modeling workflow.
 *
 * Reads a set of Dia diagrams and combines them into a single SML
 * model for code generation.
 */
class director {
public:
    director() = default;
    director(const director&) = default;
    ~director() = default;
    director(director&&) = default;
    director& operator=(const director&) = default;

public:
    explicit director(const config::settings& settings);

private:
    /**
     * @brief Given an archive type and a model name, returns the
     * appropriate file extension.
     *
     * @param archive_type one of the supported boost archive types.
     * @param model a textual representation for either SML or Dia.
     */
    std::string extension(utility::serialization::archive_types archive_type,
        const std::string& model) const;

    /**
     * @brief Returns true if configured to save Dia models, false
     * otherwise.
     */
    bool is_save_dia_model_enabled() const;

    /**
     * @brief Saves a Dia model to the filesystem.
     *
     * @param d Dia model to save.
     * @param file_name name of the file to save.
     */
    void save_diagram(const dia::diagram& d, const std::string& file_name) const;

    /**
     * @brief Reads a Dia diagram from the filesystem.
     *
     * @param path location of the diagram to read.
     */
    dia::diagram hydrate_diagram(const boost::filesystem::path& path) const;

    /**
     * @brief Returns true if configured to save SML models, false
     * otherwise.
     */
    bool is_save_sml_model_enabled() const;

    /**
     * @brief Saves an SML model to the filesystem.
     *
     * @param m SML model to save.
     */
    void save_model(const sml::model& m, const std::string& prefix) const;

    /**
     * @brief Creates a versioned or unversioned key system pod.
     */
    sml::pod create_key_system_pod(const sml::pod& p,
        const bool is_versioned) const;

    /**
     * @brief Inject system defined types into the model.
     *
     * @param m SML model to operate on.
     */
    void inject_system_types(sml::model& m) const;

    /**
     * @brief Converts a Dia diagram to its SML representation.
     */
    sml::model to_sml(const dia::diagram& d, config::reference ref,
        const bool is_target) const;

    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const sml::model& m) const;

public:
    /**
     * @brief Creates the combined SML model given the configuration
     * the director was initialised with.
     */
    boost::optional<sml::model> create_model() const;

private:
    const config::settings settings_;
    const bool verbose_;
};

} } }

#endif
