/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/config/hash/cpp_facet_types_hash.hpp"
#include "dogen/cpp/hash/aspect_types_hash.hpp"
#include "dogen/cpp/hash/file_types_hash.hpp"
#include "dogen/cpp/hash/view_models/class_view_model_hash.hpp"
#include "dogen/cpp/hash/view_models/enumeration_view_model_hash.hpp"
#include "dogen/cpp/hash/view_models/exception_view_model_hash.hpp"
#include "dogen/cpp/hash/view_models/file_view_model_hash.hpp"
#include "dogen/cpp/hash/view_models/namespace_view_model_hash.hpp"
#include "dogen/cpp/hash/view_models/registrar_view_model_hash.hpp"
#include "dogen/cpp/hash/view_models/visitor_view_model_hash.hpp"
#include "dogen/sml/hash/category_types_hash.hpp"
#include "dogen/sml/hash/meta_types_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_dogen_cpp_view_models_class_view_model(const boost::optional<dogen::cpp::view_models::class_view_model>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_view_models_enumeration_view_model(const boost::optional<dogen::cpp::view_models::enumeration_view_model>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_view_models_exception_view_model(const boost::optional<dogen::cpp::view_models::exception_view_model>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_view_models_registrar_view_model(const boost::optional<dogen::cpp::view_models::registrar_view_model>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_view_models_namespace_view_model(const boost::optional<dogen::cpp::view_models::namespace_view_model>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_boost_optional_dogen_cpp_view_models_visitor_view_model(const boost::optional<dogen::cpp::view_models::visitor_view_model>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace cpp {
namespace view_models {

std::size_t file_view_model_hasher::hash(const file_view_model&v) {
    std::size_t seed(0);

    combine(seed, v.facet_type());
    combine(seed, v.file_type());
    combine(seed, v.aspect_type());
    combine(seed, v.category_type());
    combine(seed, v.meta_type());
    combine(seed, hash_boost_optional_dogen_cpp_view_models_class_view_model(v.class_vm()));
    combine(seed, hash_boost_optional_dogen_cpp_view_models_enumeration_view_model(v.enumeration_vm()));
    combine(seed, hash_boost_optional_dogen_cpp_view_models_exception_view_model(v.exception_vm()));
    combine(seed, hash_boost_optional_dogen_cpp_view_models_registrar_view_model(v.registrar_vm()));
    combine(seed, v.header_guard());
    combine(seed, hash_std_list_std_string(v.system_includes()));
    combine(seed, hash_std_list_std_string(v.user_includes()));
    combine(seed, v.file_path().generic_string());
    combine(seed, hash_boost_optional_dogen_cpp_view_models_namespace_view_model(v.namespace_vm()));
    combine(seed, hash_boost_optional_dogen_cpp_view_models_visitor_view_model(v.visitor_vm()));

    return seed;
}

} } }
