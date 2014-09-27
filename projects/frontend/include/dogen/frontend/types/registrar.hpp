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
#include "dogen/frontend/types/source_interface.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Keeps track of all the available sources.
 */
class registrar {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

    /*
     * @brief Registers a given source for a file extension.
     *
     * @pre Extension is not yet registered.
     */
    void register_source_for_extension(const std::string& ext,
        std::shared_ptr<source_interface> s);

    /**
     * @brief Return the source that handles the supplied extension.
     *
     * @pre A source must have been registered for this extension.
     */
    std::shared_ptr<source_interface>
    source_for_extension(const std::string& ext);

private:
    std::unordered_map<std::string, std::shared_ptr<source_interface>>
        source_for_extension_;
};

} }

#endif
