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
#ifndef DOGEN_STITCH_TYPES_SCRIPTLET_BLOCK_HPP
#define DOGEN_STITCH_TYPES_SCRIPTLET_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen/stitch/types/block.hpp"
#include "dogen/stitch/types/scriptlet_line.hpp"
#include "dogen/stitch/serialization/scriptlet_block_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class scriptlet_block final : public dogen::stitch::block {
public:
    scriptlet_block() = default;
    scriptlet_block(const scriptlet_block&) = default;
    scriptlet_block(scriptlet_block&&) = default;

    virtual ~scriptlet_block() noexcept { }

public:
    explicit scriptlet_block(const std::list<dogen::stitch::scriptlet_line>& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const scriptlet_block& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, scriptlet_block& v, unsigned int version);

public:
    virtual void accept(const block_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(block_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const block_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(block_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<dogen::stitch::scriptlet_line>& content() const;
    std::list<dogen::stitch::scriptlet_line>& content();
    void content(const std::list<dogen::stitch::scriptlet_line>& v);
    void content(const std::list<dogen::stitch::scriptlet_line>&& v);

public:
    bool operator==(const scriptlet_block& rhs) const;
    bool operator!=(const scriptlet_block& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::stitch::block& other) const override;

public:
    void swap(scriptlet_block& other) noexcept;
    scriptlet_block& operator=(scriptlet_block other);

private:
    std::list<dogen::stitch::scriptlet_line> content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::scriptlet_block& lhs,
    dogen::stitch::scriptlet_block& rhs) {
    lhs.swap(rhs);
}

}

#endif
