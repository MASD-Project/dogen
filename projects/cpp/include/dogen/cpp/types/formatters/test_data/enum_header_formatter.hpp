/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_TEST_DATA_ENUM_HEADER_FORMATTER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_TEST_DATA_ENUM_HEADER_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/cpp/types/formatters/enum_formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace test_data {

/**
 * @brief Creates the test data header representation for an enumeration.
 */
class enum_header_formatter : public enum_formatter_interface {
public:
    enum_header_formatter() = default;
    enum_header_formatter(const enum_header_formatter&) = delete;
    enum_header_formatter(enum_header_formatter&&) = default;
    ~enum_header_formatter() noexcept = default;

public:
    /**
     * @brief Returns the formatter name.
     */
    static std::string static_formatter_name();

public:
    dynamic::ownership_hierarchy ownership_hierarchy() const override;

    file_types file_type() const override;

    formattables::origin_types formattable_origin_type() const;

    void register_inclusion_dependencies_provider(
        formattables::registrar& rg) const override;

    dogen::formatters::file
    format(const formattables::enum_info& c) const override;
};

} } } }

#endif
