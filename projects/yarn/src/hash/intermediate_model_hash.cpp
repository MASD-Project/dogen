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
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/hash/module_hash.hpp"
#include "dogen/yarn/hash/object_hash.hpp"
#include "dogen/yarn/hash/builtin_hash.hpp"
#include "dogen/yarn/hash/concept_hash.hpp"
#include "dogen/yarn/hash/element_hash.hpp"
#include "dogen/yarn/hash/indices_hash.hpp"
#include "dogen/yarn/hash/visitor_hash.hpp"
#include "dogen/yarn/hash/exception_hash.hpp"
#include "dogen/yarn/hash/languages_hash.hpp"
#include "dogen/yarn/hash/enumeration_hash.hpp"
#include "dogen/yarn/hash/origin_types_hash.hpp"
#include "dogen/yarn/hash/intermediate_model_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_dogen_yarn_name(const std::unordered_set<dogen::yarn::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_module(const std::unordered_map<std::string, dogen::yarn::module>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_concept(const std::unordered_map<std::string, dogen::yarn::concept>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_builtin(const std::unordered_map<std::string, dogen::yarn::builtin>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_enumeration(const std::unordered_map<std::string, dogen::yarn::enumeration>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_object(const std::unordered_map<std::string, dogen::yarn::object>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_exception(const std::unordered_map<std::string, dogen::yarn::exception>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_yarn_visitor(const std::unordered_map<std::string, dogen::yarn::visitor>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_element(const boost::shared_ptr<dogen::yarn::element>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_element(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_element(i.second));
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_yarn_languages(const std::list<dogen::yarn::languages>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {

std::size_t intermediate_model_hasher::hash(const intermediate_model& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.origin_type());
    combine(seed, hash_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(v.references()));
    combine(seed, hash_std_unordered_set_dogen_yarn_name(v.leaves()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_module(v.modules()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_concept(v.concepts()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_builtin(v.builtins()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_enumeration(v.enumerations()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_object(v.objects()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_exception(v.exceptions()));
    combine(seed, hash_std_unordered_map_std_string_dogen_yarn_visitor(v.visitors()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_element(v.injected_elements()));
    combine(seed, v.has_generatable_types());
    combine(seed, v.indices());
    combine(seed, v.root_module());
    combine(seed, v.input_language());
    combine(seed, hash_std_list_dogen_yarn_languages(v.output_languages()));

    return seed;
}

} }
