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
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/filesystem/file_not_found.hpp"
#include "masd.dogen.utility/types/test_data/resolver.hpp"
#include "masd.dogen.utility/types/test_data/validating_resolver.hpp"

namespace masd::dogen::utility::test_data {

boost::filesystem::path
validating_resolver::resolve(boost::filesystem::path relative) {
    boost::filesystem::path r(resolver::resolve(relative));
    if (boost::filesystem::exists(r))
        return r;

    using dogen::utility::filesystem::file_not_found;
    BOOST_THROW_EXCEPTION(file_not_found(r.string()));
}

}
