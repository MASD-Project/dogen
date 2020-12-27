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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_OBJECT_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.codec/types/entities/attribute.hpp"

namespace dogen::codec::entities {

/**
 * @brief Represents an "raw" codec object which may or may not contain a modeling element of interest.
 */
class object final {
public:
    object(const object&) = default;
    ~object() = default;

public:
    object();

public:
    object(object&& rhs);

public:
    object(
        const dogen::codec::entities::comment& comment,
        const std::string& id,
        const std::string& name,
        const std::string& object_type,
        const std::string& stereotypes,
        const std::string& container_id,
        const boost::optional<std::pair<std::string, std::string> >& connection,
        const std::list<dogen::codec::entities::attribute>& attributes,
        const bool is_package);

public:
    /**
     * @brief Properties associated with the codec comment.
     */
    /**@{*/
    const dogen::codec::entities::comment& comment() const;
    dogen::codec::entities::comment& comment();
    void comment(const dogen::codec::entities::comment& v);
    void comment(const dogen::codec::entities::comment&& v);
    /**@}*/

    /**
     * @brief Original ID available in the codec representation, if any.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Original name in codec representation. May be qualified or simple; its nature is codec dependent.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Native codec representation for the object type. Its interpretation is codec dependent.
     */
    /**@{*/
    const std::string& object_type() const;
    std::string& object_type();
    void object_type(const std::string& v);
    void object_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Original steoreotypes assigned to the object, if any.
     */
    /**@{*/
    const std::string& stereotypes() const;
    std::string& stereotypes();
    void stereotypes(const std::string& v);
    void stereotypes(const std::string&& v);
    /**@}*/

    /**
     * @brief Codec ID of the container of this object, if any.
     */
    /**@{*/
    const std::string& container_id() const;
    std::string& container_id();
    void container_id(const std::string& v);
    void container_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Connections this object may have with other objects, if any.
     */
    /**@{*/
    const boost::optional<std::pair<std::string, std::string> >& connection() const;
    boost::optional<std::pair<std::string, std::string> >& connection();
    void connection(const boost::optional<std::pair<std::string, std::string> >& v);
    void connection(const boost::optional<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief All attributes associated with this object.
     */
    /**@{*/
    const std::list<dogen::codec::entities::attribute>& attributes() const;
    std::list<dogen::codec::entities::attribute>& attributes();
    void attributes(const std::list<dogen::codec::entities::attribute>& v);
    void attributes(const std::list<dogen::codec::entities::attribute>&& v);
    /**@}*/

    /**
     * @brief If true, the object represents a package.
     */
    /**@{*/
    bool is_package() const;
    void is_package(const bool v);
    /**@}*/

public:
    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(object& other) noexcept;
    object& operator=(object other);

private:
    dogen::codec::entities::comment comment_;
    std::string id_;
    std::string name_;
    std::string object_type_;
    std::string stereotypes_;
    std::string container_id_;
    boost::optional<std::pair<std::string, std::string> > connection_;
    std::list<dogen::codec::entities::attribute> attributes_;
    bool is_package_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::object& lhs,
    dogen::codec::entities::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
