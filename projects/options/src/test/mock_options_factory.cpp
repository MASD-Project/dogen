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
#include "dogen/options/test/mock_options_factory.hpp"

namespace dogen {
namespace options {
namespace test {

knitting_options mock_options_factory::make_knitting_options(
    const boost::filesystem::path& target,
    const boost::filesystem::path project_dir,
    const bool verbose) {

    knitting_options r;
    r.verbose(verbose);
    r.target(target);
    r.delete_extra_files(true);
    r.force_write(false);
    r.project_directory_path(project_dir);
    return r;
}

} } }
