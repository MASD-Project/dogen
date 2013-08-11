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
#ifndef DOGEN_CPP_TYPES_SCOPE_HPP
#define DOGEN_CPP_TYPES_SCOPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <list>
#include "dogen/cpp/serialization/scope_fwd_ser.hpp"
#include "dogen/cpp/types/entity_fwd.hpp"
#include "dogen/cpp/types/scope.hpp"
#include "dogen/cpp/types/scope_types.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief The scope for an identifier.
 *
 *  §3.3.1 Declarative regions and scopes:
 *
 * Every name is introduced in some portion of program text called a
 * declarative region, which is the largest part of the program in
 * which that name is valid, that is, in which that name may be used
 * as an unqualified name to refer to the same entity. In general,
 * each particular name is valid only within some possibly dis-
 * contiguous portion of program text called its scope.
 */
class scope final {
public:
    scope(const scope&) = default;
    scope(scope&&) = default;
    ~scope() = default;

public:
    scope();

public:
    scope(
        const dogen::cpp::scope_types& type,
        const std::list<dogen::cpp::scope>& inner_scopes,
        const std::list<boost::shared_ptr<dogen::cpp::entity> >& entities);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const scope& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, scope& v, unsigned int version);

public:
    /**
     * @brief Type of the scope.
     */
    /**@{*/
    dogen::cpp::scope_types type() const;
    void type(const dogen::cpp::scope_types& v);
    /**@}*/

    /**
     * @brief Any inner scopes this scope may contain.
     */
    /**@{*/
    const std::list<dogen::cpp::scope>& inner_scopes() const;
    std::list<dogen::cpp::scope>& inner_scopes();
    void inner_scopes(const std::list<dogen::cpp::scope>& v);
    void inner_scopes(const std::list<dogen::cpp::scope>&& v);
    /**@}*/

    /**
     * @brief All elements that are contained by this scope.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::cpp::entity> >& entities() const;
    std::list<boost::shared_ptr<dogen::cpp::entity> >& entities();
    void entities(const std::list<boost::shared_ptr<dogen::cpp::entity> >& v);
    void entities(const std::list<boost::shared_ptr<dogen::cpp::entity> >&& v);
    /**@}*/

public:
    bool operator==(const scope& rhs) const;
    bool operator!=(const scope& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(scope& other) noexcept;
    scope& operator=(scope other);

private:
    dogen::cpp::scope_types type_;
    std::list<dogen::cpp::scope> inner_scopes_;
    std::list<boost::shared_ptr<dogen::cpp::entity> > entities_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::scope& lhs,
    dogen::cpp::scope& rhs) {
    lhs.swap(rhs);
}

}

#endif
