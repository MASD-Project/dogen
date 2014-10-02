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
#ifndef DOGEN_FRONTEND_TYPES_REGISTRAR_HPP
#define DOGEN_FRONTEND_TYPES_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include "dogen/frontend/types/model_provider_interface.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Keeps track of all the available providers.
 */
class registrar {
public:
    /**
     * @brief Returns all available providers for each extension.
     *
     * Only used for debug purposes.
     */
    const std::unordered_map<std::string,
                             std::shared_ptr<model_provider_interface>>&
        providers_by_extension() const;

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

    /*
     * @brief Registers a given provider for a file extension.
     *
     * @pre Extension is not yet registered.
     */
    void register_provider_for_extension(const std::string& ext,
        std::shared_ptr<model_provider_interface> s);

    /**
     * @brief Returns the provider that handles the supplied
     * extension.
     *
     * @pre A provider must have been registered for this extension.
     */
    model_provider_interface& provider_for_extension(const std::string& ext);

private:
    std::unordered_map<std::string, std::shared_ptr<model_provider_interface>>
        providers_by_extension_;
};

} }

#endif
