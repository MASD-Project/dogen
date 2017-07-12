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
#ifndef DOGEN_YARN_TYPES_HELPERS_IDENTIFIABLE_AND_QUALIFIED_BUILDER_HPP
#define DOGEN_YARN_TYPES_HELPERS_IDENTIFIABLE_AND_QUALIFIED_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/name_tree.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/helpers/pretty_printer.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class identifiable_and_qualified_builder final {
public:
    identifiable_and_qualified_builder();

private:
    std::string obtain_qualified(
        const std::map<meta_model::languages, std::string>& map,
        const meta_model::languages& l) const;

public:
    void add(const meta_model::name& n);
    void add(const meta_model::name_tree& nt);

public:
    std::pair<std::string, std::map<meta_model::languages, std::string>>
    build();

    std::pair<std::string, std::map<meta_model::languages, std::string>>
    build(const meta_model::name& n, const bool model_name_mode);

private:
    pretty_printer csharp_pp_;
    pretty_printer cpp_pp_;
};

} } }

#endif
