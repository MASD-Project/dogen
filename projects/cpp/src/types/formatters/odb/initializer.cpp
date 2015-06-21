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
#include "dogen/cpp/types/settings/bundle_repository_factory.hpp"
#include "dogen/cpp/types/formatters/odb/settings_factory.hpp"
#include "dogen/cpp/types/formatters/odb/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/initializer.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

template<typename Formatter>
inline void initialise_formatter(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_formatter(f);
}

void register_opaque_settings_factories() {
    auto& rg(settings::bundle_repository_factory::registrar());
    rg.register_opaque_settings_factory(boost::make_shared<settings_factory>());
}

void initializer::initialize(registrar& rg) {
    initialise_formatter<class_header_formatter>(rg);
    initialise_formatter<odb_options_formatter>(rg);
    register_opaque_settings_factories();
}

} } } }
