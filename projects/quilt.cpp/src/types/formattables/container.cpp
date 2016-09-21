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
#include "dogen/quilt.cpp/types/formattables/container.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

const std::forward_list<boost::shared_ptr<provider_interface<yarn::module>>>&
container::module_providers() const {
    return module_providers_;
}

std::forward_list<boost::shared_ptr<provider_interface<yarn::module>>>&
container::module_providers() {
    return module_providers_;
}

const std::forward_list<boost::shared_ptr<provider_interface<yarn::concept>>>&
container::concept_providers() const {
    return concept_providers_;
}

std::forward_list<boost::shared_ptr<provider_interface<yarn::concept>>>&
container::concept_providers() {
    return concept_providers_;
}

const std::forward_list<boost::shared_ptr<provider_interface<yarn::primitive>>>&
container::primitive_providers() const {
    return primitive_providers_;
}

std::forward_list<boost::shared_ptr<provider_interface<yarn::primitive>>>&
container::primitive_providers() {
    return primitive_providers_;
}

const std::forward_list<boost::shared_ptr<provider_interface<yarn::object>>>&
container::object_providers() const {
    return object_providers_;
}

std::forward_list<boost::shared_ptr<provider_interface<yarn::object>>>&
container::object_providers() {
    return object_providers_;
}

const std::forward_list<
    boost::shared_ptr<provider_interface<yarn::enumeration>>
>&
container::enumeration_providers() const {
    return enumeration_providers_;
}

std::forward_list<
    boost::shared_ptr<provider_interface<yarn::enumeration>>
>&
container::enumeration_providers() {
    return enumeration_providers_;
}

const std::forward_list<boost::shared_ptr<provider_interface<yarn::exception>>>&
container::exception_providers() const {
    return exception_providers_;
}

std::forward_list<boost::shared_ptr<provider_interface<yarn::exception>>>&
    container::exception_providers() {
    return exception_providers_;
}

const std::forward_list<boost::shared_ptr<provider_interface<yarn::visitor>>>&
container::visitor_providers() const {
    return visitor_providers_;
}

std::forward_list<boost::shared_ptr<provider_interface<yarn::visitor>>>&
    container::visitor_providers() {
    return visitor_providers_;
}

const std::forward_list<
    boost::shared_ptr<provider_interface<fabric::registrar>>
>&
container::registrar_providers() const {
    return registrar_providers_;
}

std::forward_list<
    boost::shared_ptr<provider_interface<fabric::registrar>>
>&
container::registrar_providers() {
    return registrar_providers_;
}

const std::forward_list<
    boost::shared_ptr<provider_interface<fabric::master_header>>
>&
container::master_header_providers() const {
    return master_header_providers_;
}

std::forward_list<
    boost::shared_ptr<provider_interface<fabric::master_header>>
>&
container::master_header_providers() {
    return master_header_providers_;
}

const std::forward_list<
    boost::shared_ptr<provider_interface<fabric::forward_declarations>>
    >&
container::forward_declarations_providers() const {
    return forward_declarations_providers_;
}

std::forward_list<
    boost::shared_ptr<provider_interface<fabric::forward_declarations>>
    >&
container::forward_declarations_providers() {
    return forward_declarations_providers_;
}

const std::forward_list<
    boost::shared_ptr<provider_interface<fabric::cmakelists>>
>&
container::cmakelists_providers() const {
    return cmakelists_providers_;
}

std::forward_list<
    boost::shared_ptr<provider_interface<fabric::cmakelists>>
>&
container::cmakelists_providers() {
    return cmakelists_providers_;
}

const std::forward_list<
    boost::shared_ptr<provider_interface<fabric::odb_options>>
>&
container::odb_options_providers() const {
    return odb_options_providers_;
}

std::forward_list<
    boost::shared_ptr<provider_interface<fabric::odb_options>>
>&
container::odb_options_providers() {
    return odb_options_providers_;
}

} } } }
