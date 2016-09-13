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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/properties/registrar_error.hpp"
#include "dogen/quilt.cpp/types/properties/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.properties.registrar"));

const std::string null_provider("Provider cannot be null.");
const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

template<typename Element>
inline void validate(boost::shared_ptr<provider_interface<Element>> p) {
    if (!p) {
        BOOST_LOG_SEV(lg, error) << null_provider;
        BOOST_THROW_EXCEPTION(registrar_error(null_provider));
    }

    if (p->formatter_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_formatter_name;
        BOOST_THROW_EXCEPTION(registrar_error(empty_formatter_name));
    }
}

const properties::container& registrar::container() const {
    return container_;
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::object>> p) {
    validate(p);
    container_.object_providers_.push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::enumeration>> p) {
    validate(p);
    container_.enumeration_providers_.push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::exception>> p) {
    validate(p);
    container_.exception_providers_.push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::visitor>> p) {
    validate(p);
    container_.visitor_providers_.push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::registrar>> p) {
    validate(p);
    container_.registrar_providers_.push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::master_header>> p) {
    validate(p);
    container_.master_header_providers_.push_front(p);
}

} } } }
