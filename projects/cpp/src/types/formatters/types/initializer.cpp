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
#include <memory>
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/initializer.hpp"

namespace {

const std::string default_directory_name("types");
const std::string default_postfix;

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

facet_settings default_settings() {
    facet_settings r;
    r.enabled(true);
    r.directory_name(default_directory_name);
    r.postfix(default_postfix);
    return r;
}

void initializer::initialize(registrar& r) {
    r.register_default_facet_settings(traits::facet_id, default_settings());
    r.register_formatter(std::make_shared<class_header_formatter>());
}

} } } }
