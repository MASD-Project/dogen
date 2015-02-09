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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FILE_PROPERTIES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FILE_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/cpp/types/formatters/file_details.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Builds file properties.
 */
class file_properties_factory {
private:
    /**
     * @brief Creates the relative path for the details and qualified name.
     */
    boost::filesystem::path
    create_relative_path(const file_details& d, const sml::qname& qn) const;

    /**
     * @brief Creates the absolute path for the details and qualified name.
     */
    boost::filesystem::path
    create_absolute_path(const file_details& d, const sml::qname& qn) const;

public:
    /**
     * @brief Builds a file name for the supplied qualified name.
     */
    formattables::file_properties
    make(const file_details& d, const sml::qname& qn) const;
};

} } }

#endif
