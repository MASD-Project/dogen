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
#ifndef DOGEN_ENGINE_TYPES_MODELING_DIRECTOR_HPP
#define DOGEN_ENGINE_TYPES_MODELING_DIRECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen/dia/types/diagram.hpp"
#include "dogen/config/types/settings.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/engine/types/persister.hpp"

namespace dogen {
namespace engine {

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

public:
    /**
     * @brief Creates the combined SML model given the configuration
     * the director was initialised with.
     */
    boost::optional<sml::model> create_model() const;

private:
    const config::settings settings_;
    const bool verbose_;
    const persister persister_;
};

} }

#endif
