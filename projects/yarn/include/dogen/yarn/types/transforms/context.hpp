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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class context final {
public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const options::knitting_options& options,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    const options::knitting_options& options() const;
    const annotations::type_repository& type_repository() const;
    const annotations::annotation_groups_factory& groups_factory() const;

public:

private:
    const std::vector<boost::filesystem::path> data_directories_;
    const dogen::options::knitting_options options_;
    const annotations::archetype_location_repository location_repository_;
    const dogen::annotations::type_repository type_repository_;
    const annotations::annotation_groups_factory groups_factory_;
};

} } }

#endif
