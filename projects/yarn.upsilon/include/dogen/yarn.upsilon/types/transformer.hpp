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
#ifndef DOGEN_YARN_UPSILON_TYPES_TRANSFORMER_HPP
#define DOGEN_YARN_UPSILON_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/upsilon/types/type_name.hpp"
#include "dogen/upsilon/types/model.hpp"
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/types/compound.hpp"
#include "dogen/upsilon/types/collection.hpp"
#include "dogen/upsilon/types/enumeration.hpp"

namespace dogen {
namespace yarn {
namespace upsilon {

class transformer final {
private:
    std::string to_unparsed_type(const dogen::upsilon::type_name& tn) const;

    void populate_element_properties(const yarn::origin_types ot,
        const yarn::name& model_name, const dogen::upsilon::type& t,
        yarn::element& e) const;

public:
    yarn::primitive to_primitive(const yarn::origin_types ot,
        const yarn::name& model_name, const dogen::upsilon::primitive& p) const;
    yarn::object to_object(const yarn::origin_types ot,
        const yarn::name& model_name, const dogen::upsilon::compound& c) const;
    yarn::object to_object(const yarn::origin_types ot,
        const yarn::name& model_name, const dogen::upsilon::collection& c) const;
    yarn::enumeration
    to_enumeration(const yarn::origin_types ot,
        const yarn::name& model_name, const dogen::upsilon::enumeration& e) const;
};

} } }

#endif
