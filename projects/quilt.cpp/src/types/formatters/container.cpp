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
#include "dogen/quilt.cpp/types/formatters/container.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

const std::forward_list<
    std::shared_ptr<formatters::new_class_formatter_interface>
>&
container::new_class_formatters() const {
    return new_class_formatters_;
}

const std::forward_list<std::shared_ptr<formatters::enum_formatter_interface>>&
container::enum_formatters() const {
    return enum_formatters_;
}

const std::forward_list<std::shared_ptr<
    formatters::exception_formatter_interface>>&
container::exception_formatters() const {
    return exception_formatters_;
}

const std::forward_list<std::shared_ptr<
    formatters::namespace_formatter_interface>>&
container::namespace_formatters() const {
    return namespace_formatters_;
}

const std::forward_list<std::shared_ptr<
    formatters::visitor_formatter_interface>>&
container::visitor_formatters() const {
    return visitor_formatters_;
}

const std::forward_list<
    std::shared_ptr<formatters::forward_declarations_formatter_interface>
    >& container::forward_declarations_formatters() const {
    return forward_declarations_formatters_;
}

const std::forward_list<
    std::shared_ptr<formatters::odb_options_formatter_interface>
    >& container::odb_options_formatters() const {
    return odb_options_formatters_;
}

const std::forward_list<
    std::shared_ptr<formatters::cmakelists_formatter_interface>
    >& container::cmakelists_formatters() const {
    return cmakelists_formatters_;
}

const std::forward_list<
    std::shared_ptr<formatters::registrar_formatter_interface>
    >& container::registrar_formatters() const {
    return registrar_formatters_;
}

const std::forward_list<
    std::shared_ptr<formatters::includers_formatter_interface>
    >& container::includers_formatters() const {
    return includers_formatters_;
}

const std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>&
container::all_file_formatters() const {
    return all_file_formatters_;
}

const std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>&
container::all_internal_file_formatters() const {
    return all_internal_file_formatters_;
}

const std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>&
container::all_external_file_formatters() const {
    return all_external_file_formatters_;
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
