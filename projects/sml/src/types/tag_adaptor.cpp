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

namespace {

const std::string empty;

}

namespace dogen {
namespace sml {

tag_adaptor::
tag_adaptor(const std::unordered_map<std::string, std::string>& simple_tags,
    const std::unordered_map<std::string, std::list<std::string> >&
    complex_tags) : simple_tags_(simple_tags), complex_tags_(complex_tags) { }

bool tag_adaptor::get_bool_with_false_default(const std::string& key) const {
    const auto i(simple_tags_.find(key));
    if (i != simple_tags_.end())
        return i->second == tags::bool_true;

    return false;
}

bool tag_adaptor::has_comment() const {
    const auto i(simple_tags_.find(tags::comment));
    return i != simple_tags_.end();
}

bool tag_adaptor::has_identity() const {
    const auto i(simple_tags_.find(tags::identity_attribute));
    return i != simple_tags_.end();
}

std::string tag_adaptor::original_parent_name() const {
    const auto i(simple_tags_.find(tags::original_parent_name));
    if (i != simple_tags_.end())
        return i->second;
    return empty;
}

bool tag_adaptor::is_original_parent_visitable() const {
    const auto& key(tags::is_original_parent_visitable);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::generate_explicitly_defaulted_functions() const {
    const auto& key(tags::cpp::domain::generate_explicitly_defaulted_functions);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::generate_complete_constructor() const {
    const auto& key(tags::cpp::domain::generate_complete_constructor);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::generate_equality() const {
    const auto& key(tags::cpp::domain::generate_equality);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::generate_swap() const {
    const auto& key(tags::cpp::domain::generate_swap);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::requires_manual_default_constructor() const {
    const auto& key(tags::cpp::domain::requires_manual_default_constructor);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::requires_manual_move_constructor() const {
    const auto& key(tags::cpp::domain::requires_manual_move_constructor);
    return get_bool_with_false_default(key);
}

bool tag_adaptor::generate_preamble() const {
    return get_bool_with_false_default(tags::generate_preamble);
}

bool tag_adaptor::is_simple_type() const {
    return get_bool_with_false_default(tags::cpp::type::is_simple_type);
}

std::string tag_adaptor::qualified_name() const {
    const auto i(simple_tags_.find(tags::cpp::type::qualified_name));
    if (i != simple_tags_.end())
        return i->second;
    return empty;
}

std::string tag_adaptor::qualified_original_parent_name() const {
    const auto i(simple_tags_.find(tags::cpp::type::qualified_name));
    if (i != simple_tags_.end())
        return i->second;
    return empty;
}

std::string tag_adaptor::complete_name() const {
    const auto i(simple_tags_.find(tags::cpp::type::complete_name));
    if (i != simple_tags_.end())
        return i->second;
    return empty;
}

bool tag_adaptor::is_boost_serialization_enabled() const {
    const auto& key(tags::cpp::serialization::boost::status);
    const auto i(simple_tags_.find(key));
    if (i != simple_tags_.end())
        return i->second == tags::status_supported;

    return false;
}

bool tag_adaptor::is_io_enabled() const {
    const auto& key(tags::cpp::io::status);
    const auto i(simple_tags_.find(key));
    if (i != simple_tags_.end())
        return i->second == tags::status_supported;

    return false;
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
