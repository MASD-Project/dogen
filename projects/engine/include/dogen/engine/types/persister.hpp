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
#ifndef DOGEN_ENGINE_TYPES_PERSISTER_HPP
#define DOGEN_ENGINE_TYPES_PERSISTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/model.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/config/types/settings.hpp"
#include "dogen/config/types/archive_types.hpp"

namespace dogen {
namespace engine {

class persister {
public:
    persister() = delete;
    persister(const persister&) = default;
    persister(persister&&) = default;
    persister& operator=(const persister&) = default;

public:
    explicit persister(const config::settings& settings);

private:
    /**
     * @brief Given an archive type and a model name, returns the
     * appropriate file extension.
     *
     * @param archive_type one of the supported boost archive types.
     * @param model a textual representation for either SML or Dia.
     */
    std::string extension(config::archive_types archive_type,
        const std::string& model) const;

    /**
     * @brief Returns true if configured to save Dia models, false
     * otherwise.
     */
    bool is_save_dia_model_enabled() const;

    /**
     * @brief Returns true if configured to save SML models, false
     * otherwise.
     */
    bool is_save_sml_model_enabled() const;

public:
    /**
     * @brief Saves a Dia model to the filesystem.
     *
     * @param d Dia model to save.
     * @param file_name name of the file to save.
     */
    void save_diagram(const dia::diagram& d, const std::string& name) const;

    /**
     * @brief Saves an SML model to the filesystem.
     *
     * @param m SML model to save.
     */
    void save_model(const sml::model& m, const std::string& prefix) const;

private:
    const config::settings settings_;
};

} }

#endif
