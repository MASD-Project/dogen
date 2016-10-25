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
#ifndef DOGEN_WALE_TYPES_TEXT_TEMPLATE_HPP
#define DOGEN_WALE_TYPES_TEXT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/wale/types/properties.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/wale/serialization/text_template_fwd_ser.hpp"

namespace dogen {
namespace wale {

class text_template final {
public:
    text_template() = default;
    text_template(const text_template&) = default;
    ~text_template() = default;

public:
    text_template(text_template&& rhs);

public:
    text_template(
        const boost::optional<dogen::annotations::annotation>& annotation,
        const dogen::wale::properties& properties,
        const std::string& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::wale::text_template& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::wale::text_template& v, unsigned int version);

public:
    const boost::optional<dogen::annotations::annotation>& annotation() const;
    boost::optional<dogen::annotations::annotation>& annotation();
    void annotation(const boost::optional<dogen::annotations::annotation>& v);
    void annotation(const boost::optional<dogen::annotations::annotation>&& v);

    const dogen::wale::properties& properties() const;
    dogen::wale::properties& properties();
    void properties(const dogen::wale::properties& v);
    void properties(const dogen::wale::properties&& v);

    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);

public:
    bool operator==(const text_template& rhs) const;
    bool operator!=(const text_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_template& other) noexcept;
    text_template& operator=(text_template other);

private:
    boost::optional<dogen::annotations::annotation> annotation_;
    dogen::wale::properties properties_;
    std::string content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::wale::text_template& lhs,
    dogen::wale::text_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
