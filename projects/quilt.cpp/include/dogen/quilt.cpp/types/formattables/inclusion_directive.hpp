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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/formattables/inclusion_directive_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Represents the inclusion directive associated with a name and an archetype.
 */
class inclusion_directive final {
public:
    inclusion_directive() = default;
    inclusion_directive(const inclusion_directive&) = default;
    inclusion_directive(inclusion_directive&&) = default;
    ~inclusion_directive() = default;

public:
    inclusion_directive(
        const std::string& principal,
        const std::list<std::string>& auxiliary);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::inclusion_directive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::inclusion_directive& v, unsigned int version);

public:
    /**
     * @brief The main inclusion directive needed for this element.
     */
    /**@{*/
    const std::string& principal() const;
    std::string& principal();
    void principal(const std::string& v);
    void principal(const std::string&& v);
    /**@}*/

    /**
     * @brief Any other directives that are also needed for this element.
     */
    /**@{*/
    const std::list<std::string>& auxiliary() const;
    std::list<std::string>& auxiliary();
    void auxiliary(const std::list<std::string>& v);
    void auxiliary(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const inclusion_directive& rhs) const;
    bool operator!=(const inclusion_directive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_directive& other) noexcept;
    inclusion_directive& operator=(inclusion_directive other);

private:
    std::string principal_;
    std::list<std::string> auxiliary_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::inclusion_directive& lhs,
    dogen::quilt::cpp::formattables::inclusion_directive& rhs) {
    lhs.swap(rhs);
}

}

#endif
