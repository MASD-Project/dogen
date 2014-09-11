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
#include "dogen/sml/types/meta_data/registrar.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

void registrar::register_root_enricher(std::shared_ptr<enricher_interface> e) {
    root_enricher_ = e;
}

void registrar::
register_ordinary_enricher(std::shared_ptr<enricher_interface> e) {
    ordinary_enrichers_.push_back(e);
}

std::shared_ptr<enricher_interface> registrar::root_enricher() {
    return root_enricher_;
}


std::list<std::shared_ptr<enricher_interface>> registrar::ordinary_enrichers() {
    return ordinary_enrichers_;
}

} } }
