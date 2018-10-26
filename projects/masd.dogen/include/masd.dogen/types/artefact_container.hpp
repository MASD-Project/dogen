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
#ifndef MASD_DOGEN_TYPES_ARTEFACT_CONTAINER_HPP
#define MASD_DOGEN_TYPES_ARTEFACT_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "masd.dogen/types/artefact.hpp"
#include "masd.dogen/types/artefact_group_type.hpp"

namespace masd::dogen {

class artefact_container final {
public:
    artefact_container(const artefact_container&) = default;
    artefact_container(artefact_container&&) = default;
    ~artefact_container() = default;

public:
    artefact_container();

public:
    artefact_container(
        const std::string& name,
        const masd::dogen::artefact_group_type type,
        const std::list<masd::dogen::artefact>& artefacts,
        const bool has_diffs);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    masd::dogen::artefact_group_type type() const;
    void type(const masd::dogen::artefact_group_type v);

    const std::list<masd::dogen::artefact>& artefacts() const;
    std::list<masd::dogen::artefact>& artefacts();
    void artefacts(const std::list<masd::dogen::artefact>& v);
    void artefacts(const std::list<masd::dogen::artefact>&& v);

    /**
     * @brief If true, one or more artefacts are different.
     */
    /**@{*/
    bool has_diffs() const;
    void has_diffs(const bool v);
    /**@}*/

public:
    bool operator==(const artefact_container& rhs) const;
    bool operator!=(const artefact_container& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact_container& other) noexcept;
    artefact_container& operator=(artefact_container other);

private:
    std::string name_;
    masd::dogen::artefact_group_type type_;
    std::list<masd::dogen::artefact> artefacts_;
    bool has_diffs_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::artefact_container& lhs,
    masd::dogen::artefact_container& rhs) {
    lhs.swap(rhs);
}

}

#endif
