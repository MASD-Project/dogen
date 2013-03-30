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
#ifndef DOGEN_ENGINE_TYPES_MODEL_SOURCE_FWD_HPP
#define DOGEN_ENGINE_TYPES_MODEL_SOURCE_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/model.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/config/types/settings.hpp"
#include "dogen/config/types/archive_types.hpp"
#include "dogen/engine/types/persister.hpp"
#include "dogen/sml/types/model_source_interface.hpp"

namespace dogen {
namespace engine {

class model_source : public dogen::sml::model_source_interface {
public:
    model_source() = delete;
    model_source(const model_source&) = delete;
    model_source(model_source&&) = default;
    model_source& operator=(const model_source&) = delete;

public:
    explicit model_source(const config::settings& settings);
    virtual ~model_source() noexcept {}

private:
    /**
     * @brief Reads a Dia diagram from the filesystem.
     *
     * @param path location of the diagram to read.
     */
    dia::diagram hydrate_diagram(const boost::filesystem::path& path) const;

    /**
     * @brief Converts a Dia diagram to its SML representation.
     */
    sml::model to_sml(const dia::diagram& d, config::reference ref,
        const bool is_target) const;

public:
    virtual std::list<sml::model> references() const override;
    virtual sml::model target() const override;

private:
    const config::settings settings_;
    const persister persister_;
};

} }

#endif
