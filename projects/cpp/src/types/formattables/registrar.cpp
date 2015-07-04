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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formattables/registrar_error.hpp"
#include "dogen/cpp/types/formattables/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.registrar"));

const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace cpp {
namespace formattables {

const formattables::container& registrar::container() const {
    return container_;
}

void registrar::register_provider(boost::shared_ptr<
    inclusion_dependencies_provider_interface<sml::object>
    > p) {

    if (p->formatter_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_formatter_name;
        BOOST_THROW_EXCEPTION(registrar_error(empty_formatter_name));
    }
    container_.object_providers().push_front(p);
}

void registrar::register_provider(boost::shared_ptr<
    inclusion_dependencies_provider_interface<sml::enumeration>
    > p) {

    if (p->formatter_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_formatter_name;
        BOOST_THROW_EXCEPTION(registrar_error(empty_formatter_name));
    }
    container_.enumeration_providers().push_front(p);
}

void registrar::register_provider(boost::shared_ptr<
    inclusion_dependencies_provider_interface<sml::model>
    > p) {

    if (p->formatter_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_formatter_name;
        BOOST_THROW_EXCEPTION(registrar_error(empty_formatter_name));
    }
    container_.model_providers().push_front(p);
}

} } }
