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
#ifndef DOGEN_STITCH_TYPES_TEXT_BLOCK_HPP
#define DOGEN_STITCH_TYPES_TEXT_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen/stitch/types/block.hpp"
#include "dogen/stitch/types/text_line.hpp"
#include "dogen/stitch/serialization/text_block_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class text_block final : public dogen::stitch::block {
public:
    text_block() = default;
    text_block(const text_block&) = default;
    text_block(text_block&&) = default;

    virtual ~text_block() noexcept { }

public:
    explicit text_block(const std::list<dogen::stitch::text_line>& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const text_block& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, text_block& v, unsigned int version);

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
    const std::list<dogen::stitch::text_line>& content() const;
    std::list<dogen::stitch::text_line>& content();
    void content(const std::list<dogen::stitch::text_line>& v);
    void content(const std::list<dogen::stitch::text_line>&& v);

public:
    bool operator==(const text_block& rhs) const;
    bool operator!=(const text_block& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::stitch::block& other) const override;

public:
    void swap(text_block& other) noexcept;
    text_block& operator=(text_block other);

private:
    std::list<dogen::stitch::text_line> content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::text_block& lhs,
    dogen::stitch::text_block& rhs) {
    lhs.swap(rhs);
}

}

#endif
