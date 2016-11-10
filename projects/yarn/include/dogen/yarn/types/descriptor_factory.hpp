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
#ifndef DOGEN_YARN_TYPES_DESCRIPTOR_FACTORY_HPP
#define DOGEN_YARN_TYPES_DESCRIPTOR_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/input_options.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/yarn/types/descriptor.hpp"

namespace dogen {
namespace yarn {

class descriptor_factory {
private:
    struct type_group {
        annotations::type reference;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const type_group& v);

    type_group make_type_group(const annotations::type_repository& atrp) const;

    std::list<std::string> make_references(const type_group& tg,
        const annotations::annotation& a) const;

private:
    std::vector<boost::filesystem::path> to_library_dirs(
        const std::vector<boost::filesystem::path>& data_dirs) const;

private:
    std::list<descriptor>
    make(const std::vector<boost::filesystem::path>& library_dirs) const;

    std::list<descriptor> make(const annotations::type_repository& atrp,
        const boost::filesystem::path& references_dir,
        const annotations::annotation& a) const;

public:
    descriptor make(const boost::filesystem::path& target) const;

    std::list<descriptor>
    make(const std::vector<boost::filesystem::path>& data_dirs,
        const boost::filesystem::path& references_dir,
        const annotations::type_repository& atrp,
        const annotations::annotation& a) const;
};

} }

#endif
