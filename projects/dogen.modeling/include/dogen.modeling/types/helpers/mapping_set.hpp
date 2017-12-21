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
#ifndef DOGEN_MODELING_TYPES_HELPERS_MAPPING_SET_HPP
#define DOGEN_MODELING_TYPES_HELPERS_MAPPING_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen.modeling/types/meta_model/name.hpp"
#include "dogen.modeling/types/meta_model/languages.hpp"
#include "dogen.modeling/hash/meta_model/languages_hash.hpp"
#include "dogen.modeling/serialization/helpers/mapping_set_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

/**
 * @brief Consistent unit of mapping that can be used to translate a model from a language to
 * another.
 */
class mapping_set final {
public:
    mapping_set() = default;
    mapping_set(const mapping_set&) = default;
    mapping_set(mapping_set&&) = default;
    ~mapping_set() = default;

public:
    mapping_set(
        const std::string& name,
        const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_map<std::string, dogen::modeling::meta_model::name> >& by_language_agnostic_id,
        const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_set<std::string> >& erasures_by_language);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::helpers::mapping_set& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::helpers::mapping_set& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_map<std::string, dogen::modeling::meta_model::name> >& by_language_agnostic_id() const;
    std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_map<std::string, dogen::modeling::meta_model::name> >& by_language_agnostic_id();
    void by_language_agnostic_id(const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_map<std::string, dogen::modeling::meta_model::name> >& v);
    void by_language_agnostic_id(const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_map<std::string, dogen::modeling::meta_model::name> >&& v);

    const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_set<std::string> >& erasures_by_language() const;
    std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_set<std::string> >& erasures_by_language();
    void erasures_by_language(const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_set<std::string> >& v);
    void erasures_by_language(const std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_set<std::string> >&& v);

public:
    bool operator==(const mapping_set& rhs) const;
    bool operator!=(const mapping_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_set& other) noexcept;
    mapping_set& operator=(mapping_set other);

private:
    std::string name_;
    std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_map<std::string, dogen::modeling::meta_model::name> > by_language_agnostic_id_;
    std::unordered_map<dogen::modeling::meta_model::languages, std::unordered_set<std::string> > erasures_by_language_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::helpers::mapping_set& lhs,
    dogen::modeling::helpers::mapping_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
