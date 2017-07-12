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
#ifndef DOGEN_YARN_TYPES_HELPERS_REFERENCE_PATHS_EXTRACTOR_HPP
#define DOGEN_YARN_TYPES_HELPERS_REFERENCE_PATHS_EXTRACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class reference_paths_extractor final {
private:
    struct type_group {
        annotations::type reference;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const type_group& v);

    static type_group make_type_group(const annotations::type_repository& atrp);

    static std::list<std::string> make_user_references(const type_group& tg,
        const annotations::annotation& a);

    static std::list<boost::filesystem::path> obtain_paths_to_user_references(
        const transforms::context& ctx, const annotations::annotation& ra);

private:
    static std::vector<boost::filesystem::path> to_library_dirs(
        const std::vector<boost::filesystem::path>& data_dirs);

    static std::list<boost::filesystem::path> obtain_paths_to_system_models(
        const transforms::context& ctx);

public:
    static std::list<boost::filesystem::path>
    extract(const transforms::context& ctx,
        const meta_model::intermediate_model& target);
};

} } }

#endif
