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
#include "dogen/cpp/types/formatters/facet.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

std::string facet::id() const { return id_; }
void facet::id(const std::string& v) { id_ = v; }

settings_bundle facet::bundle() const { return bundle_; }
void facet::bundle(const settings_bundle& v) { bundle_ = v; }

const formatters::container& facet::container() const { return container_; }
void facet::container(const formatters::container& v) { container_ = v; }

} } }
