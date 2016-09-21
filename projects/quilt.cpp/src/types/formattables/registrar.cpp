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
#include "dogen/quilt.cpp/types/formattables/registrar_error.hpp"
#include "dogen/quilt.cpp/types/formattables/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.registrar"));

const std::string null_provider("Provider cannot be null.");
const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

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

const formattables::container& registrar::container() const {
    return container_;
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::object>> p) {
    validate(p);
    container_.object_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::enumeration>> p) {
    validate(p);
    container_.enumeration_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::exception>> p) {
    validate(p);
    container_.exception_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::visitor>> p) {
    validate(p);
    container_.visitor_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::primitive>> p) {
    validate(p);
    container_.primitive_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<yarn::module>> p) {
    validate(p);
    container_.module_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::registrar>> p) {
    validate(p);
    container_.registrar_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::master_header>> p) {
    validate(p);
    container_.master_header_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::forward_declarations>> p) {
    validate(p);
    container_.forward_declarations_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::cmakelists>> p) {
    validate(p);
    container_.cmakelists_providers().push_front(p);
}

void registrar::register_provider(
    boost::shared_ptr<provider_interface<fabric::odb_options>> p) {
    validate(p);
    container_.odb_options_providers().push_front(p);
}

} } } }
