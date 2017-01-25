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
#ifndef DOGEN_YARN_TYPES_MAPPINGS_HYDRATOR_HPP
#define DOGEN_YARN_TYPES_MAPPINGS_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/mapping_actions.hpp"
#include "dogen/yarn/types/mapping.hpp"

namespace dogen {
namespace yarn {

class mappings_hydrator final {
private:
    mapping_actions to_mapping_action(const std::string& s) const;
    languages to_language(const std::string& s) const;

private:
    name read_name(const boost::property_tree::ptree& pt) const;

    std::unordered_map<languages, mapping_value>
    read_mapping_values(const boost::property_tree::ptree& pt) const;

    std::list<mapping> read_stream(std::istream& s) const;

public:
    std::list<mapping> hydrate(std::istream& s) const;
    std::list<mapping> hydrate(const boost::filesystem::path& p) const;
};

} }

#endif
