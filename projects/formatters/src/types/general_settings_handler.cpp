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
#include "dogen/formatters/types/general_settings_handler.hpp"

namespace {

const std::string id("formatters.general_settings_handler");
using namespace dogen::utility::log;
auto lg(logger_factory(id));

}
namespace dogen {
namespace formatters {

std::string general_settings_handler::id() const {
    return ::id;
}

unsigned int general_settings_handler::required_passes() const {
    return 1;
}

bool general_settings_handler::consume_last() const {
    return false;
}

void general_settings_handler::
consume(const sml::model& /*model*/, const unsigned int /*pass*/,
    const sml::concept& /*target*/) const {
}

void general_settings_handler::
consume(const sml::model& /*model*/, const unsigned int /*pass*/,
    const sml::module& /*target*/) const {
}

void general_settings_handler::
consume(const sml::model& /*model*/, const unsigned int /*pass*/,
    const sml::enumeration& /*target*/) const {
}

void general_settings_handler::
consume(const sml::model& /*model*/, const unsigned int /*pass*/,
    const sml::primitive& /*target*/) const {
}

void general_settings_handler::
consume(const sml::model& /*model*/, const unsigned int /*pass*/,
    const sml::object& /*target*/) const {
}

} }
