/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_YARN_JSON_TYPES_DEHYDRATOR_HPP
#define DOGEN_YARN_JSON_TYPES_DEHYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <unordered_map>
#include <string>
#include <ostream>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace json {

class dehydrator final {
private:
    std::string tidy_up_string(std::string s) const;
    bool has_elements(const intermediate_model& im) const;

    template<typename Element>
    std::map<std::string, Element>
    to_map(const std::unordered_map<std::string, Element>& original) const {
        std::map<std::string, Element> r;
        for (const auto& pair : original)
            r.insert(pair);
        return r;
    }

private:
    void dehydrate_name(const name& n, std::ostream& s) const;
    void dehydrate_annotations(const intermediate_model& im,
        const std::string& id, std::ostream& s) const;
    void dehydrate_element(const intermediate_model& im, const element& e,
        const std::string& meta_type, std::ostream& s) const;
    void dehydrate_attributes(const std::list<attribute>& attrs,
        std::ostream& s) const;
    void dehydrate_objects(const intermediate_model& im, std::ostream& s) const;
    void dehydrate_concepts(const intermediate_model& im,
        std::ostream& s) const;
    void dehydrate_modules(const intermediate_model& im, std::ostream& s) const;
    void dehydrate_enumerations(
        const intermediate_model& im, std::ostream& s) const;
    void dehydrate_exceptions(
        const intermediate_model& im, std::ostream& s) const;

public:
    std::string dehydrate(const intermediate_model& im) const;
    void dehydrate(const intermediate_model& im,
        const boost::filesystem::path& p) const;
};

} } }

#endif
