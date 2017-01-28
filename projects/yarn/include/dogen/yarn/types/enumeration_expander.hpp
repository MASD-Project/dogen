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
#ifndef DOGEN_YARN_TYPES_ENUMERATION_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ENUMERATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

class enumeration_expander final {
private:
    struct enumeration_type_group {
        annotations::type use_implementation_defined_underlying_element;
        annotations::type underlying_element;
        annotations::type use_implementation_defined_enumerator_values;
        annotations::type add_invalid_enumerator;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const enumeration_type_group& v);

    struct enumerator_type_group {
        annotations::type value;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const enumerator_type_group& v);

    struct type_group {
        enumeration_type_group enumeration;
        enumerator_type_group enumerator;
    };
    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    enumeration_type_group make_enumeration_type_group(
        const annotations::type_repository& atrp) const;

    enumerator_type_group make_enumerator_type_group(
        const annotations::type_repository& atrp) const;

    type_group make_type_group(const annotations::type_repository& atrp) const;

private:
    void populate_from_annotations(const enumeration_type_group& tg,
        enumeration& e) const;
    void populate_from_annotations(const enumerator_type_group& tg,
        enumerator& e) const;

private:
    name obtain_enumeration_default_underlying_element_name(
        const intermediate_model& im) const;
    std::string obtain_invalid_enumerator_simple_name(const languages l) const;
    enumerator make_invalid_enumerator(
        const name& n, const languages l) const;

    void expand_default_underlying_element(
        const name& default_underlying_element_name, enumeration& e);
    void expand_enumerators(const languages l, enumeration& e) const;

public:
    /**
     * @brief Expands all enumerations in model.
     */
    void expand(const annotations::type_repository& atrp,
        intermediate_model& im);
};

} }

#endif
