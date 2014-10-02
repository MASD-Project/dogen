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
#ifndef DOGEN_FRONTEND_TYPES_MODEL_PROVIDER_INTERFACE_HPP
#define DOGEN_FRONTEND_TYPES_MODEL_PROVIDER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/sml/types/model.hpp"
#include "dogen/frontend/types/provider_settings.hpp"
#include "dogen/frontend/types/input_descriptor.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Provides partial SML models.
 */
class model_provider_interface {
public:
    model_provider_interface() = default;
    model_provider_interface(const model_provider_interface&) = delete;
    model_provider_interface(model_provider_interface&&) = default;
    virtual ~model_provider_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the provider, for logging
     * purposes.
     */
    virtual std::string id() const = 0;

    /**
     * @brief List of extensions supported by this provider.
     */
    virtual std::list<std::string> supported_extensions() const = 0;

    /**
     * @brief Read an input descriptor and transform it into a partial
     * SML model.
     */
    virtual sml::model
    provide(const input_descriptor& d, const provider_settings& s) = 0;
};

} }

#endif
