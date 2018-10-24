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
#ifndef MASD_DOGEN_ANNOTATIONS_TYPES_NUMBER_HPP
#define MASD_DOGEN_ANNOTATIONS_TYPES_NUMBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "masd.dogen.annotations/types/value.hpp"

namespace masd::dogen::annotations {

/**
 * @brief Field can hold numbers.
 */
class number final : public masd::dogen::annotations::value {
public:
    number(const number&) = default;
    number(number&&) = default;

public:
    number();

    virtual ~number() noexcept { }

public:
    explicit number(const int content);

public:
    using value::accept;

    virtual void accept(const value_visitor& v) const override;
    virtual void accept(value_visitor& v) const override;
    virtual void accept(const value_visitor& v) override;
    virtual void accept(value_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    int content() const;
    void content(const int v);

public:
    bool operator==(const number& rhs) const;
    bool operator!=(const number& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::annotations::value& other) const override;

public:
    void swap(number& other) noexcept;
    number& operator=(number other);

private:
    int content_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::annotations::number& lhs,
    masd::dogen::annotations::number& rhs) {
    lhs.swap(rhs);
}

}

#endif
