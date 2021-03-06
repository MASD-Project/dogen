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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_COMMA_SEPARATED_COLLECTION_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_COMMA_SEPARATED_COLLECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.variability/types/entities/value.hpp"

namespace dogen::variability::entities {

/**
 * @brief Represents a collection of CSV input that is split into a collection of text values.
 */
class comma_separated_collection final : public dogen::variability::entities::value {
public:
    comma_separated_collection() = default;
    comma_separated_collection(const comma_separated_collection&) = default;
    comma_separated_collection(comma_separated_collection&&) = default;

    virtual ~comma_separated_collection() noexcept { }

public:
    explicit comma_separated_collection(const std::list<std::list<std::string> >& content);

public:
    using value::accept;

    virtual void accept(const value_visitor& v) const override;
    virtual void accept(value_visitor& v) const override;
    virtual void accept(const value_visitor& v) override;
    virtual void accept(value_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<std::list<std::string> >& content() const;
    std::list<std::list<std::string> >& content();
    void content(const std::list<std::list<std::string> >& v);
    void content(const std::list<std::list<std::string> >&& v);

public:
    bool operator==(const comma_separated_collection& rhs) const;
    bool operator!=(const comma_separated_collection& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::entities::value& other) const override;

public:
    void swap(comma_separated_collection& other) noexcept;
    comma_separated_collection& operator=(comma_separated_collection other);

private:
    std::list<std::list<std::string> > content_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::comma_separated_collection& lhs,
    dogen::variability::entities::comma_separated_collection& rhs) {
    lhs.swap(rhs);
}

}

#endif
