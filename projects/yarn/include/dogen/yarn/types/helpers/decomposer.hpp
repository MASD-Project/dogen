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
#ifndef DOGEN_YARN_TYPES_HELPERS_DECOMPOSER_HPP
#define DOGEN_YARN_TYPES_HELPERS_DECOMPOSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/helpers/decomposition_result.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class decomposer final {
private:
    void add_name(const std::string& owner, const meta_model::name& n);
    void add_name_tree(const std::string& owner,
        const meta_model::name_tree& nt);
    void add_names(const std::string& owner,
        const std::list<meta_model::name>& names);
    void process_attributes(const std::string& owner,
        const std::list<meta_model::attribute>& attrs);
    void process_element(const meta_model::element& e);

public:
    void decompose(const meta_model::concept& c);
    void decompose(const meta_model::module& m);
    void decompose(const meta_model::enumeration& e);
    void decompose(const meta_model::exception& e);
    void decompose(const meta_model::object& o);
    void decompose(const meta_model::builtin& b);

public:
    const decomposition_result& result() const;

private:
    decomposition_result result_;
};

} } }

#endif
