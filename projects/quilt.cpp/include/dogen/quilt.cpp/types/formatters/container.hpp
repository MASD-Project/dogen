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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_CONTAINER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/helper_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class registrar;

/**
 * @brief Simple container for all formatter types.
 */
class container final {
private:
    friend class registrar;

public:
    /**
     * @brief Returns all available object formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    object_formatters() const;

    /**
     * @brief Returns all available enumeration formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    enumeration_formatters() const;

    /**
     * @brief Returns all available exception formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    exception_formatters() const;

    /**
     * @brief Returns all available module formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    module_formatters() const;

    /**
     * @brief Returns all available namespace formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    visitor_formatters() const;

    /**
     * @brief Returns all available forward declarations formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    forward_declarations_formatters() const;

    /**
     * @brief Returns all available odb options formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    odb_options_formatters() const;

    /**
     * @brief Returns all available CMakeLists formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    cmakelists_formatters() const;

    /**
     * @brief Returns all available registrar formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    registrar_formatters() const;

    /**
     * @brief Returns all available master header formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    master_header_formatters() const;

public:
    /**
     * @brief Returns all available file formatters.
     */
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    all_file_formatters() const;

public:
    const std::unordered_map<
    std::string,
    std::unordered_map<std::string,
                       std::list<
                           std::shared_ptr<helper_formatter_interface>>>>&
        helper_formatters() const;

private:
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    object_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    enumeration_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    exception_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    module_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    visitor_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    forward_declarations_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    odb_options_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    cmakelists_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    registrar_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    master_header_formatters_;
    std::forward_list<std::shared_ptr<file_formatter_interface>>
    all_file_formatters_;
    std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::list<
                               std::shared_ptr<helper_formatter_interface>>>>
        helper_formatters_;
};

} } } }

#endif
