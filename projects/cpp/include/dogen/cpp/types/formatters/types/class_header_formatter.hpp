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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_TYPES_CLASS_HEADER_FORMATTER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_TYPES_CLASS_HEADER_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

/**
 * @brief Creates the C++ domain representation for a class.
 */
class class_header_formatter : public formatters::class_formatter_interface {
public:
    class_header_formatter() = default;
    class_header_formatter(const class_header_formatter&) = delete;
    class_header_formatter(class_header_formatter&&) = default;
    ~class_header_formatter() noexcept = default;

private:
    /**
     * @brief Gets the inclusion path for the current formatter.
     */
    boost::filesystem::path
    get_inclusion_path(const formattables::class_info& c) const;

    /**
     * @brief Gets the file path for the current formatter.
     */
    boost::filesystem::path
    get_file_path(const formattables::class_info& c) const;

public:
    std::string facet_name() const override;

    std::string formatter_name() const override;

public:
    file_types file_type() const override;

public:
    dogen::formatters::file
    format(const formattables::class_info& c) const override;
};

} } } }

#endif
