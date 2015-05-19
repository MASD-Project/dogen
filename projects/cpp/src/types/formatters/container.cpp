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
#include "dogen/cpp/types/formatters/container.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

const std::forward_list<std::shared_ptr<formatters::class_formatter_interface>>&
container::class_formatters() const {
    return class_formatters_;
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

const std::forward_list<std::shared_ptr<formatters::formatter_interface>>&
container::all_formatters() const {
    return all_formatters_;
}

} } }
