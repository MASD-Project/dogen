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
#ifndef DOGEN_STITCH_TYPES_TEXT_TEMPLATE_HPP
#define DOGEN_STITCH_TYPES_TEXT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/variant.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/stitch/types/scriptlet_block.hpp"
#include "dogen/stitch/types/settings_bundle.hpp"
#include "dogen/stitch/types/mixed_content_block.hpp"
#include "dogen/stitch/serialization/text_template_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class text_template final {
public:
    text_template() = default;
    text_template(const text_template&) = default;
    text_template(text_template&&) = default;
    ~text_template() = default;

public:
    text_template(
        const dogen::stitch::settings_bundle& settings,
        const dogen::dynamic::schema::object& extensions,
        const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const text_template& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, text_template& v, unsigned int version);

public:
    const dogen::stitch::settings_bundle& settings() const;
    dogen::stitch::settings_bundle& settings();
    void settings(const dogen::stitch::settings_bundle& v);
    void settings(const dogen::stitch::settings_bundle&& v);

    const dogen::dynamic::schema::object& extensions() const;
    dogen::dynamic::schema::object& extensions();
    void extensions(const dogen::dynamic::schema::object& v);
    void extensions(const dogen::dynamic::schema::object&& v);

    const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& content() const;
    std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& content();
    void content(const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& v);
    void content(const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >&& v);

public:
    bool operator==(const text_template& rhs) const;
    bool operator!=(const text_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_template& other) noexcept;
    text_template& operator=(text_template other);

private:
    dogen::stitch::settings_bundle settings_;
    dogen::dynamic::schema::object extensions_;
    std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> > content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::text_template& lhs,
    dogen::stitch::text_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
