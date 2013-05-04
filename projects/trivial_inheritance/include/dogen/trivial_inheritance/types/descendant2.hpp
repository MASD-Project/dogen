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
#ifndef DOGEN_TRIVIAL_INHERITANCE_TYPES_DESCENDANT2_HPP
#define DOGEN_TRIVIAL_INHERITANCE_TYPES_DESCENDANT2_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/serialization/descendant2_fwd_ser.hpp"
#include "dogen/trivial_inheritance/types/base.hpp"
#include "dogen/trivial_inheritance/types/base_visitor.hpp"

namespace dogen {
namespace trivial_inheritance {

class descendant2 final : public dogen::trivial_inheritance::base {
public:
    descendant2() = default;
    descendant2(const descendant2&) = default;
    descendant2(descendant2&&) = default;
    descendant2& operator=(const descendant2&) = default;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const descendant2& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, descendant2& v, unsigned int version);

public:
    virtual void accept(const base_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(base_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const base_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(base_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const descendant2& rhs) const;
    bool operator!=(const descendant2& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::trivial_inheritance::base& other) const override;

};

} }

#endif
