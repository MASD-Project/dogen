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
#ifndef MASD_DOGEN_TYPES_ARTEFACT_HPP
#define MASD_DOGEN_TYPES_ARTEFACT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "masd.dogen/types/operation.hpp"

namespace masd::dogen {

class artefact final {
public:
    artefact() = default;
    artefact(const artefact&) = default;
    artefact(artefact&&) = default;
    ~artefact() = default;

public:
    artefact(
        const std::string& name,
        const std::string& content,
        const std::string& diff,
        const masd::dogen::operation& operation);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);

    const std::string& diff() const;
    std::string& diff();
    void diff(const std::string& v);
    void diff(const std::string&& v);

    const masd::dogen::operation& operation() const;
    masd::dogen::operation& operation();
    void operation(const masd::dogen::operation& v);
    void operation(const masd::dogen::operation&& v);

public:
    bool operator==(const artefact& rhs) const;
    bool operator!=(const artefact& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact& other) noexcept;
    artefact& operator=(artefact other);

private:
    std::string name_;
    std::string content_;
    std::string diff_;
    masd::dogen::operation operation_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::artefact& lhs,
    masd::dogen::artefact& rhs) {
    lhs.swap(rhs);
}

}

#endif
