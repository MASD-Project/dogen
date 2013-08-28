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
#ifndef DOGEN_OM_TYPES_PREAMBLE_FACTORY_HPP
#define DOGEN_OM_TYPES_PREAMBLE_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/om/types/preamble_field.hpp"
#include "dogen/om/types/preamble.hpp"

namespace dogen {
namespace om {

class preamble_factory {
public:
    preamble_factory() = delete;
    preamble_factory(const preamble_factory&) = default;
    preamble_factory& operator=(const preamble_factory&) = delete;
    preamble_factory(preamble_factory&& rhs) = default;

public:
    explicit preamble_factory(const boost::filesystem::path template_directory);

// private:
//     std::unordered_map<std::string, std::list<preamble_field> > templates_;
};

} }

#endif
