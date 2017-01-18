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
#ifndef DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_REPOSITORY_HPP
#define DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/hash/languages_hash.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/serialization/intermediate_model_repository_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class intermediate_model_repository final {
public:
    intermediate_model_repository() = default;
    intermediate_model_repository(const intermediate_model_repository&) = default;
    intermediate_model_repository(intermediate_model_repository&&) = default;
    ~intermediate_model_repository() = default;

public:
    explicit intermediate_model_repository(const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& by_language);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::intermediate_model_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::intermediate_model_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& by_language() const;
    std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& by_language();
    void by_language(const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& v);
    void by_language(const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >&& v);

public:
    bool operator==(const intermediate_model_repository& rhs) const;
    bool operator!=(const intermediate_model_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(intermediate_model_repository& other) noexcept;
    intermediate_model_repository& operator=(intermediate_model_repository other);

private:
    std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> > by_language_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::intermediate_model_repository& lhs,
    dogen::yarn::intermediate_model_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
