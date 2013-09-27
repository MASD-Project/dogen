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
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"

namespace dogen {
namespace sml {

tag_adaptor::
tag_adaptor(const std::unordered_map<std::string, std::string>& simple_tags,
    const std::unordered_map<std::string, std::list<std::string> >&
    complex_tags) : simple_tags_(simple_tags), complex_tags_(complex_tags) { }

bool tag_adaptor::has_comment() const {
    const auto i(simple_tags_.find(tags::comment));
    return i != simple_tags_.end();
}

bool tag_adaptor::has_identity() const {
    const auto i(simple_tags_.find(tags::identity_attribute));
    return i != simple_tags_.end();
}


std::list<std::pair<std::string,std::string> > tag_adaptor::odb_pragma() const {
    std::list<std::pair<std::string, std::string> > r;

    const auto i(complex_tags_.find(tags::odb_pragma));
    if (i != complex_tags_.end()) {
        for (const auto& value : i->second)
            r.push_back(std::make_pair(tags::odb_pragma, value));
    }
    return r;
}

} }
