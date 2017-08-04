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

#include <string>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/meta_model/origin_types.hpp"
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/upsilon/types/name.hpp"
#include "dogen/upsilon/types/model.hpp"
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/types/compound.hpp"
#include "dogen/upsilon/types/collection.hpp"
#include "dogen/upsilon/types/enumeration.hpp"

namespace dogen {
namespace yarn {
namespace upsilon {

class transformer final {
public:
    explicit transformer(const yarn::meta_model::name& target_model_name);

    transformer(
        const yarn::meta_model::name& target_model_name,
        const std::unordered_map<std::string, yarn::meta_model::name>&
        schema_name_to_model_name,
        const std::unordered_map<std::string,
        dogen::upsilon::name>& collection_names);

private:
    std::string to_unparsed_type(const dogen::upsilon::name& tn) const;

    void populate_element_properties(const dogen::upsilon::type& t,
        yarn::meta_model::element& e) const;

public:
    boost::shared_ptr<yarn::meta_model::builtin>
    to_builtin(const dogen::upsilon::primitive& p) const;

    boost::shared_ptr<yarn::meta_model::object>
    to_object(const dogen::upsilon::compound& c) const;

    boost::shared_ptr<yarn::meta_model::enumeration>
    to_enumeration(const dogen::upsilon::enumeration& e) const;

private:
    const yarn::meta_model::name& target_model_name_;
    const std::unordered_map<std::string, dogen::yarn::meta_model::name>
    schema_name_to_model_name_;
    const std::unordered_map<std::string, dogen::upsilon::name>
    collection_names_;
};

} } }

#endif
