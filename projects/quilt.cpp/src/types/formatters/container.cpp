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
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/helper_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::unordered_map<
    std::type_index,
    std::forward_list<std::shared_ptr<file_formatter_interface>>>&
container::file_formatters_by_type_index() {
    return file_formatters_by_type_index_;
}

std::unordered_map<std::string, std::shared_ptr<file_formatter_interface>>&
container::file_formatters_by_archetype() {
    return file_formatters_by_formatter_name_;
}

std::forward_list<std::shared_ptr<file_formatter_interface>>&
container::file_formatters() {
    return file_formatters_;
}

std::unordered_map<
    std::string, std::unordered_map<
                     std::string,
                     std::list<
                         std::shared_ptr<helper_formatter_interface>>>>&
container::helper_formatters() {
    return helper_formatters_;
}

const std::unordered_map<
    std::type_index,
    std::forward_list<std::shared_ptr<file_formatter_interface>>>&
container::file_formatters_by_type_index() const {
    return file_formatters_by_type_index_;
}

const std::unordered_map<std::string,
                         std::shared_ptr<file_formatter_interface>>&
container::file_formatters_by_archetype() const {
    return file_formatters_by_formatter_name_;
}

const std::forward_list<std::shared_ptr<file_formatter_interface>>&
container::file_formatters() const {
    return file_formatters_;
}

const std::unordered_map<
    std::string, std::unordered_map<
                     std::string,
                     std::list<
                         std::shared_ptr<helper_formatter_interface>>>>&
    container::helper_formatters() const {
    return helper_formatters_;
}

} } } }
