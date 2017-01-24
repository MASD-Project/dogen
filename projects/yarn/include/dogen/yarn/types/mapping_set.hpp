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
#ifndef DOGEN_YARN_TYPES_MAPPING_SET_HPP
#define DOGEN_YARN_TYPES_MAPPING_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/hash/languages_hash.hpp"
#include "dogen/yarn/serialization/mapping_set_fwd_ser.hpp"

namespace dogen {
namespace yarn {

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
        const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id,
        const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id,
        const std::unordered_map<std::string, std::string>& upsilon_id_to_lam_id,
        const std::unordered_map<dogen::yarn::languages, std::unordered_set<std::string> >& erasures_by_language);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::mapping_set& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::mapping_set& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id() const;
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id();
    void by_language_agnostic_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& v);
    void by_language_agnostic_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >&& v);

    const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id() const;
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id();
    void by_upsilon_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& v);
    void by_upsilon_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >&& v);

    /**
     * @brief Map to resolve upsilon ID's into LAM IDs.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& upsilon_id_to_lam_id() const;
    std::unordered_map<std::string, std::string>& upsilon_id_to_lam_id();
    void upsilon_id_to_lam_id(const std::unordered_map<std::string, std::string>& v);
    void upsilon_id_to_lam_id(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

    const std::unordered_map<dogen::yarn::languages, std::unordered_set<std::string> >& erasures_by_language() const;
    std::unordered_map<dogen::yarn::languages, std::unordered_set<std::string> >& erasures_by_language();
    void erasures_by_language(const std::unordered_map<dogen::yarn::languages, std::unordered_set<std::string> >& v);
    void erasures_by_language(const std::unordered_map<dogen::yarn::languages, std::unordered_set<std::string> >&& v);

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
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> > by_language_agnostic_id_;
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> > by_upsilon_id_;
    std::unordered_map<std::string, std::string> upsilon_id_to_lam_id_;
    std::unordered_map<dogen::yarn::languages, std::unordered_set<std::string> > erasures_by_language_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::mapping_set& lhs,
    dogen::yarn::mapping_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
