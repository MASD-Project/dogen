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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FILE_NAME_BUILDER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FILE_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Builds file names.
 */
class file_name_builder {
public:
    file_name_builder();

public:
    /**
     * @brief If true, the project is split between source and
     * headers.
     */
    file_name_builder& split_project(bool v);

    /**
     * @brief Type of the file
     */
    file_name_builder& file_type(file_types v);

    /**
     * @brief Directory for the facet.
     */
    file_name_builder& facet_directory(const std::string& v);

    /**
     * @brief Postfix for the facet.
     */
    file_name_builder& facet_postfix(const std::string& v);

    /**
     * @brief Postfix for the formatter.
     */
    file_name_builder& formatter_postfix(const std::string& v);

    /**
     * @brief Extension for the file.
     */
    file_name_builder& extension(const std::string& v);

    /**
     * @brief Qualified name for which to build the file name.
     */
    file_name_builder& qname(const sml::qname& v);

public:
    /**
     * @brief Builds a file name for the supplied qualified name.
     */
    boost::filesystem::path build() const;

private:
    bool split_project_;
    file_types file_type_;
    std::string facet_directory_;
    std::string facet_postfix_;
    std::string formatter_postfix_;
    std::string extension_;
    sml::qname qname_;
};

} } }

#endif
