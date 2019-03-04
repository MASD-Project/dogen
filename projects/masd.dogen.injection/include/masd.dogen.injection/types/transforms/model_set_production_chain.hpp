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
#ifndef MASD_DOGEN_INJECTION_TYPES_TRANSFORMS_MODEL_SET_PRODUCTION_CHAIN_HPP
#define MASD_DOGEN_INJECTION_TYPES_TRANSFORMS_MODEL_SET_PRODUCTION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.injection/types/meta_model/model_set.hpp"
#include "masd.dogen.injection/types/transforms/context_fwd.hpp"
#include "masd.dogen.injection/types/helpers/references_resolver.hpp"

namespace masd::dogen::injection::transforms {

class model_set_production_chain final {
private:
    static std::list<boost::filesystem::path>
    obtain_directory_list(const context& ctx,
        const boost::filesystem::path& target_path);

    static std::list<meta_model::model>
    transform(const context& ctx, const helpers::references_resolver& res,
        const boost::filesystem::path& p,
        std::unordered_set<std::string>& processed_models);

public:
    static meta_model::model_set
    transform(const context& ctx, const boost::filesystem::path& p);
};

}

#endif
