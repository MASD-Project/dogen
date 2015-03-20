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
#include <boost/make_shared.hpp>
#include "dogen/cpp/types/settings/odb_settings.hpp"
#include "dogen/cpp/types/formatters/odb/settings_factory.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

settings_factory::~settings_factory() noexcept { }

std::string settings_factory::settings_key() const {
    static const std::string key("odb_settings");
    return key;
}

boost::shared_ptr<settings::opaque_settings>
settings_factory::make(const dynamic::schema::object& /*o*/) const {
    auto r(boost::make_shared<settings::odb_settings>());
    return r;
}

} } } }
