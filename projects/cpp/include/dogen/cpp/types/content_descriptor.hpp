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
#ifndef DOGEN_CPP_TYPES_CONTENT_DESCRIPTOR_HPP
#define DOGEN_CPP_TYPES_CONTENT_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/cpp/serialization/content_descriptor_fwd_ser.hpp"
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Provides a description of the type of contents of a file info.
 */
class content_descriptor final {
public:
    content_descriptor(const content_descriptor&) = default;
    content_descriptor(content_descriptor&&) = default;
    ~content_descriptor() = default;

public:
    content_descriptor();

public:
    content_descriptor(
        const dogen::cpp::file_types& file_type,
        const dogen::config::cpp_facet_types& facet_type,
        const dogen::cpp::aspect_types& aspect_type,
        const dogen::sml::qname& name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const content_descriptor& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, content_descriptor& v, unsigned int version);

public:
    /**
     * @brief Type of the file.
     */
    /**@{*/
    dogen::cpp::file_types file_type() const;
    void file_type(const dogen::cpp::file_types& v);
    /**@}*/

    /**
     * @brief Which facet of the type does this file represent.
     */
    /**@{*/
    dogen::config::cpp_facet_types facet_type() const;
    void facet_type(const dogen::config::cpp_facet_types& v);
    /**@}*/

    /**
     * @brief Which aspect of the type does this file represent.
     */
    /**@{*/
    dogen::cpp::aspect_types aspect_type() const;
    void aspect_type(const dogen::cpp::aspect_types& v);
    /**@}*/

    /**
     * @brief Qualified name of the type contained in file.
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

public:
    bool operator==(const content_descriptor& rhs) const;
    bool operator!=(const content_descriptor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(content_descriptor& other) noexcept;
    content_descriptor& operator=(content_descriptor other);

private:
    dogen::cpp::file_types file_type_;
    dogen::config::cpp_facet_types facet_type_;
    dogen::cpp::aspect_types aspect_type_;
    dogen::sml::qname name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::content_descriptor& lhs,
    dogen::cpp::content_descriptor& rhs) {
    lhs.swap(rhs);
}

}

#endif
