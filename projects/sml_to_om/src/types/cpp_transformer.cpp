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
#include "dogen/om/types/cpp_file.hpp"
#include "dogen/sml_to_om/types/cpp_transformer.hpp"

namespace dogen {
namespace sml_to_om {

cpp_transformer::
cpp_transformer(const std::set<config::cpp_facet_types>& /*enabled_facets*/,
    const sml::model& /*m*/, context& /*c*/)
// : enabled_facets_(enabled_facets), model_(m), context_(c)
{ }

void cpp_transformer::properties_for_concept(const sml::qname& /*qn*/,
    std::list<sml::property>& /*properties*/,
    std::unordered_set<sml::qname>& /*processed_qnames*/) const {
    
}

void cpp_transformer::visit(const dogen::sml::service& /*s*/) {
    
}

void cpp_transformer::visit(const dogen::sml::factory& /*f*/) {
    
}

void cpp_transformer::visit(const dogen::sml::repository& /*r*/) {
    
}

void cpp_transformer::visit(const dogen::sml::enumeration& /*e*/) {
    
}

void cpp_transformer::visit(const dogen::sml::value_object& /*vo*/) {
    
}

void cpp_transformer::visit(const dogen::sml::keyed_entity& /*ke*/) {
    
}

void cpp_transformer::visit(const dogen::sml::entity& /*e*/) {
    
}

void cpp_transformer::from_type(const sml::type& t) {
    t.accept(*this);
}

void cpp_transformer::from_module(const sml::module& /*m*/) {
    
}

} }
