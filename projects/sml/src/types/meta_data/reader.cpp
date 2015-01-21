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
#include "dogen/sml/types/meta_data/reader.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace sml {
namespace meta_data {

reader::reader(const boost::property_tree::ptree& meta_data)
    : meta_data_(meta_data) { }

bool reader::has_key(const std::string& key) const {
    const auto node(meta_data_.get_optional<std::string>(key));
    return node;
}

bool reader::is_true(const std::string& key) const {
    const auto value(get(key));
    return value == tags::bool_true;
}

bool reader::is_false(const std::string& key) const {
    return !is_true(key);
}

std::string reader::get(const std::string& key) const {
    const auto v(meta_data_.get_optional<std::string>(key));
    if (v)
        return *v;

    return empty;
}

bool reader::is_supported(const std::string& key) const {
    const auto value(get(key));
    return value == tags::status_supported;
}

std::list<std::pair<std::string,std::string> > reader::odb_pragma() const {
    std::list<std::pair<std::string, std::string> > r;

    using boost::property_tree::ptree;
    const auto child(meta_data_.get_child_optional(tags::odb_pragma));
    if (!child)
        return r;

    for (auto i(child->begin()); i != child->end(); ++i)
        r.push_back(std::make_pair(tags::odb_pragma, i->second.data()));

    return r;
}

} } }
