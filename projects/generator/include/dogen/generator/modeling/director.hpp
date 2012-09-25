/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_MODELING_DIRECTOR_HPP
#define DOGEN_GENERATOR_MODELING_DIRECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/generator/config/settings.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/dia/domain/diagram.hpp"

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
    explicit director(config::settings settings);

private:
    /**
     * @brief Given an archive type and a model name, returns the
     * appropriate file extension.
     *
     * @param archive_type one of the supported boost archive types.
     * @param model a textual representation for either SML or Dia.
     */
    std::string extension(utility::serialization::archive_types archive_type,
        std::string model) const;

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
    void save_diagram(dia::diagram d, std::string file_name) const;

    /**
     * @brief Reads a Dia diagram from the filesystem.
     *
     * @param path location of the diagram to read.
     */
    dia::diagram hydrate_diagram(boost::filesystem::path path) const;

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
    void save_model(sml::model m, std::string prefix) const;

    /**
     * @brief Converts a Dia diagram to its SML representation.
     */
    sml::model
    to_sml(dia::diagram d, std::string file_name, bool is_target) const;

    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(sml::model m) const;

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
