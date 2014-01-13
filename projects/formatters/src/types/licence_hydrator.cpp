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
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/types/licence_hydrator.hpp"

namespace dogen {
namespace formatters {

licence_hydrator::
licence_hydrator(const std::list<std::string>& copyright_holders)
    : copyright_holders_(copyright_holders) { }

licence_hydrator::value_type licence_hydrator::hydrate(std::istream& s) const {
    value_type r;
    r.text(dogen::utility::filesystem::read_file_content(s));
    r.copyright_holders(copyright_holders_);
    return r;
}

} }
