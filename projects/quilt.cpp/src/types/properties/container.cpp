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
#include "dogen/quilt.cpp/types/properties/container.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

const std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::object>
        >
    >&
container::object_providers() const {
    return object_providers_;
}

std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::object>
        >
    >&
container::object_providers() {
    return object_providers_;
}

const std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::enumeration>
        >
    >&
container::enumeration_providers() const {
    return enumeration_providers_;
}

std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::enumeration>
        >
    >&
container::enumeration_providers() {
    return enumeration_providers_;
}

const std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::exception>
        >
    >&
container::exception_providers() const {
    return exception_providers_;
}

std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::exception>
        >
    >&
container::exception_providers() {
    return exception_providers_;
}

const std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::visitor>
        >
    >&
container::visitor_providers() const {
    return visitor_providers_;
}

std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::visitor>
        >
    >&
container::visitor_providers() {
    return visitor_providers_;
}

const std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::model>
        >
    >&
container::model_providers() const {
    return model_providers_;
}

std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::model>
        >
    >&
container::model_providers() {
    return model_providers_;
}

} } } }
