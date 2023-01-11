/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.logical/hash/entities/structural/module_hash.hpp"
#include "dogen.logical/hash/entities/structural/object_hash.hpp"
#include "dogen.logical/hash/entities/structural/builtin_hash.hpp"
#include "dogen.logical/hash/entities/structural/visitor_hash.hpp"
#include "dogen.logical/hash/entities/structural/assistant_hash.hpp"
#include "dogen.logical/hash/entities/structural/exception_hash.hpp"
#include "dogen.logical/hash/entities/structural/primitive_hash.hpp"
#include "dogen.logical/hash/entities/structural/entry_point_hash.hpp"
#include "dogen.logical/hash/entities/structural/enumeration_hash.hpp"
#include "dogen.logical/hash/entities/structural/object_template_hash.hpp"
#include "dogen.logical/hash/entities/structural/element_repository_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_module(const boost::shared_ptr<dogen::logical::entities::structural::module>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_module(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::module> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_module(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_object_template(const boost::shared_ptr<dogen::logical::entities::structural::object_template>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_object_template(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object_template> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_object_template(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_builtin(const boost::shared_ptr<dogen::logical::entities::structural::builtin>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_builtin(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::builtin> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_builtin(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_enumeration(const boost::shared_ptr<dogen::logical::entities::structural::enumeration>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_enumeration(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::enumeration> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_enumeration(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_primitive(const boost::shared_ptr<dogen::logical::entities::structural::primitive>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_primitive(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::primitive> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_primitive(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_object(const boost::shared_ptr<dogen::logical::entities::structural::object>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_object(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_object(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_exception(const boost::shared_ptr<dogen::logical::entities::structural::exception>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_exception(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::exception> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_exception(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_visitor(const boost::shared_ptr<dogen::logical::entities::structural::visitor>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_visitor(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::visitor> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_visitor(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_entry_point(const boost::shared_ptr<dogen::logical::entities::structural::entry_point>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_entry_point(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::entry_point> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_entry_point(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_logical_entities_structural_assistant(const boost::shared_ptr<dogen::logical::entities::structural::assistant>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_assistant(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::assistant> >& v) {
    std::size_t seed(0);
    for (const auto& i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_logical_entities_structural_assistant(i.second));
    }
    return seed;
}

}

namespace dogen::logical::entities::structural {

std::size_t element_repository_hasher::hash(const element_repository& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_module(v.modules()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_object_template(v.object_templates()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_builtin(v.builtins()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_enumeration(v.enumerations()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_primitive(v.primitives()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_object(v.objects()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_exception(v.exceptions()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_visitor(v.visitors()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_entry_point(v.entry_points()));
    combine(seed, hash_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_structural_assistant(v.assistants()));

    return seed;
}

}
