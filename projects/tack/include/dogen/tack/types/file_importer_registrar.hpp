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
#ifndef DOGEN_TACK_TYPES_FILE_IMPORTER_REGISTRAR_HPP
#define DOGEN_TACK_TYPES_FILE_IMPORTER_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include "dogen/tack/types/file_importer_interface.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Keeps track of all the available file importers.
 */
class file_importer_registrar {
public:
    /**
     * @brief Returns all available file importers for each extension.
     *
     * Only used for debug purposes.
     */
    const std::unordered_map<std::string,
                             std::shared_ptr<file_importer_interface>>&
        file_importers_by_extension() const;

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

    /*
     * @brief Registers a given file importer against a file
     * extension.
     *
     * @pre Extension is not yet registered.
     */
    void register_file_importer_for_extension(const std::string& extension,
        std::shared_ptr<file_importer_interface> fi);

    /**
     * @brief Returns the file importer that handles the supplied
     * extension.
     *
     * @pre A file importer must have been registered for this
     * extension.
     */
    file_importer_interface&
    file_importer_for_extension(const std::string& extension);

private:
    std::unordered_map<std::string, std::shared_ptr<file_importer_interface>>
    file_importers_by_extension_;
};

} }

#endif
