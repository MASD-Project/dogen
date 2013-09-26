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
#include "dogen/om/types/context.hpp"

namespace dogen {
namespace om {

context::context(std::ostream& s, const sml::property_cache_interface& pc,
    const sml::opaque_parameter_cache_interface& opc,
    cpp_formatters::indenter& ind, cpp_formatters::utility& u)
    : stream_(s), property_cache_(pc), opaque_parameter_cache_(opc),
      indenter_(ind), utility_(u) { }

std::ostream& context::stream() {
    return stream_;
}

cpp_formatters::indenter& context::indenter() {
    return indenter_;
}

cpp_formatters::utility& context::utility() {
    return utility_;
}

const sml::property_cache_interface& context::property_cache() const {
    return property_cache_;
}

const sml::opaque_parameter_cache_interface&
context::opaque_parameter_cache() const {
    return opaque_parameter_cache_;
}

} }
