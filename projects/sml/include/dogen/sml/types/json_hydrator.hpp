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
#ifndef DOGEN_SML_TYPES_JSON_HYDRATOR_HPP
#define DOGEN_SML_TYPES_JSON_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/property_tree/ptree.hpp>
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/tag_router.hpp"

namespace dogen {
namespace sml {

class json_hydrator {
public:
    json_hydrator() = default;
    json_hydrator(const json_hydrator&) = default;
    json_hydrator(json_hydrator&&) = default;
    ~json_hydrator() noexcept = default;

private:
    template<typename Taggable>
    void read_tags(const boost::property_tree::ptree& pt, Taggable& t) const {
        const auto i(pt.find("tags"));
        if (i == pt.not_found())
            return;

        auto router(make_tag_router(t));
        for (auto j(i->second.begin()); j != i->second.end(); ++j) {
            const auto field_name(j->first);
            const auto field_value(j->second.get_value<std::string>());
            router.route(field_name, field_value);
        }
    }

    void read_tags(const boost::property_tree::ptree& pt, type& t) const;

    void read_type(const boost::property_tree::ptree& pt, model& m) const;

    model read_stream(std::istream& s) const;

public:
    model hydrate(std::istream& s) const;
};

} }

#endif
