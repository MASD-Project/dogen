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
#include "dogen/yarn/hash/meta_model/name_hash.hpp"
#include "dogen/yarn/hash/meta_model/module_hash.hpp"
#include "dogen/yarn/hash/meta_model/object_hash.hpp"
#include "dogen/yarn/hash/meta_model/builtin_hash.hpp"
#include "dogen/yarn/hash/meta_model/element_hash.hpp"
#include "dogen/yarn/hash/meta_model/visitor_hash.hpp"
#include "dogen/yarn/hash/meta_model/endomodel_hash.hpp"
#include "dogen/yarn/hash/meta_model/exception_hash.hpp"
#include "dogen/yarn/hash/meta_model/languages_hash.hpp"
#include "dogen/yarn/hash/meta_model/primitive_hash.hpp"
#include "dogen/yarn/hash/meta_model/enumeration_hash.hpp"
#include "dogen/yarn/hash/meta_model/origin_types_hash.hpp"
#include "dogen/yarn/hash/meta_model/object_template_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_model_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_dogen_yarn_meta_model_name_dogen_yarn_meta_model_origin_types(const std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_dogen_yarn_meta_model_name(const std::unordered_set<dogen::yarn::meta_model::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_module(const boost::shared_ptr<dogen::yarn::meta_model::module>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_module(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_module(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_object_template(const boost::shared_ptr<dogen::yarn::meta_model::object_template>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_object_template(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object_template> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_object_template(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_builtin(const boost::shared_ptr<dogen::yarn::meta_model::builtin>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_builtin(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::builtin> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_builtin(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_enumeration(const boost::shared_ptr<dogen::yarn::meta_model::enumeration>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_enumeration(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_enumeration(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_primitive(const boost::shared_ptr<dogen::yarn::meta_model::primitive>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_primitive(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::primitive> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_primitive(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_object(const boost::shared_ptr<dogen::yarn::meta_model::object>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_object(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_object(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_exception(const boost::shared_ptr<dogen::yarn::meta_model::exception>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_exception(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::exception> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_exception(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_visitor(const boost::shared_ptr<dogen::yarn::meta_model::visitor>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_visitor(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::visitor> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_visitor(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_meta_model_element(const boost::shared_ptr<dogen::yarn::meta_model::element>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_boost_shared_ptr_dogen_yarn_meta_model_element(const std::list<boost::shared_ptr<dogen::yarn::meta_model::element> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_element(i));
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_yarn_meta_model_languages(const std::list<dogen::yarn::meta_model::languages>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_yarn_meta_model_orm_model_properties(const boost::optional<dogen::yarn::meta_model::orm_model_properties>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

std::size_t endomodel_hasher::hash(const endomodel& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, v.meta_name());
    combine(seed, v.origin_type());
    combine(seed, hash_std_unordered_map_dogen_yarn_meta_model_name_dogen_yarn_meta_model_origin_types(v.references()));
    combine(seed, hash_std_unordered_set_dogen_yarn_meta_model_name(v.leaves()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_module(v.modules()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_object_template(v.object_templates()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_builtin(v.builtins()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_enumeration(v.enumerations()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_primitive(v.primitives()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_object(v.objects()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_exception(v.exceptions()));
    combine(seed, hash_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_meta_model_visitor(v.visitors()));
    combine(seed, hash_std_list_boost_shared_ptr_dogen_yarn_meta_model_element(v.injected_elements()));
    combine(seed, v.has_generatable_types());
    combine(seed, hash_boost_shared_ptr_dogen_yarn_meta_model_module(v.root_module()));
    combine(seed, v.input_language());
    combine(seed, hash_std_list_dogen_yarn_meta_model_languages(v.output_languages()));
    combine(seed, hash_boost_optional_dogen_yarn_meta_model_orm_model_properties(v.orm_properties()));

    return seed;
}

} } }
