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
#ifndef DOGEN_UPSILON_TYPES_COLLECTION_HPP
#define DOGEN_UPSILON_TYPES_COLLECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/upsilon/types/type.hpp"
#include "dogen/upsilon/types/type_name.hpp"
#include "dogen/upsilon/serialization/collection_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class collection final : public dogen::upsilon::type {
public:
    collection() = default;
    collection(const collection&) = default;
    collection(collection&&) = default;

    virtual ~collection() noexcept { }

public:
    collection(
        const std::string& name,
        const std::string& extends,
        const std::string& comment,
        const std::list<std::string>& tag_refs,
        const std::string& pof_id,
        const dogen::upsilon::type_name& type_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::collection& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::collection& v, unsigned int version);

public:
    using type::accept;

    virtual void accept(const type_visitor& v) const override;
    virtual void accept(type_visitor& v) const override;
    virtual void accept(const type_visitor& v) override;
    virtual void accept(type_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const dogen::upsilon::type_name& type_name() const;
    dogen::upsilon::type_name& type_name();
    void type_name(const dogen::upsilon::type_name& v);
    void type_name(const dogen::upsilon::type_name&& v);

public:
    bool operator==(const collection& rhs) const;
    bool operator!=(const collection& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::upsilon::type& other) const override;

public:
    void swap(collection& other) noexcept;
    collection& operator=(collection other);

private:
    dogen::upsilon::type_name type_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::collection& lhs,
    dogen::upsilon::collection& rhs) {
    lhs.swap(rhs);
}

}

#endif
