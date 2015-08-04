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
#ifndef DOGEN_TACK_TYPES_FILE_IMPORTER_INTERFACE_HPP
#define DOGEN_TACK_TYPES_FILE_IMPORTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/optional.hpp>
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/preprocessing_settings.hpp"
#include "dogen/tack/types/input_descriptor.hpp"
#include "dogen/dynamic/types/workflow.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Imports a model from a file.
 */
class file_importer_interface {
public:
    file_importer_interface() = default;
    file_importer_interface(const file_importer_interface&) = delete;
    file_importer_interface(file_importer_interface&&) = default;
    virtual ~file_importer_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the importer, for logging
     * purposes.
     */
    virtual std::string id() const = 0;

    /**
     * @brief List of extensions supported by this importer.
     */
    virtual std::list<std::string> supported_extensions() const = 0;

    /**
     * @brief Reads a file pointed to by the input descriptor and
     * transforms it into a model.
     */
    virtual model import(const dynamic::workflow& w,
        const input_descriptor& d,
        const boost::optional<preprocessing_settings>& s =
        boost::optional<preprocessing_settings>()) = 0;
};

} }

#endif
