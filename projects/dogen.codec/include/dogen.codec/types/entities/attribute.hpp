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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_ATTRIBUTE_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.identification/types/entities/name.hpp"
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.identification/types/entities/tagged_value.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/codec_provenance.hpp"

namespace dogen::codec::entities {

class attribute final {
public:
    attribute() = default;
    attribute(const attribute&) = default;
    attribute(attribute&&) = default;
    ~attribute() = default;

public:
    attribute(
        const std::list<dogen::identification::entities::tagged_value>& tagged_values,
        const std::list<dogen::identification::entities::stereotype>& stereotypes,
        const dogen::identification::entities::name& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::codec_provenance& provenance,
        const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides,
        const dogen::codec::entities::comment& comment,
        const std::string& type,
        const std::string& value);

public:
    const std::list<dogen::identification::entities::tagged_value>& tagged_values() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values();
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v);

    const std::list<dogen::identification::entities::stereotype>& stereotypes() const;
    std::list<dogen::identification::entities::stereotype>& stereotypes();
    void stereotypes(const std::list<dogen::identification::entities::stereotype>& v);
    void stereotypes(const std::list<dogen::identification::entities::stereotype>&& v);

    /**
     * @brief Name of the codec element.
     */
    /**@{*/
    const dogen::identification::entities::name& name() const;
    dogen::identification::entities::name& name();
    void name(const dogen::identification::entities::name& v);
    void name(const dogen::identification::entities::name&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::entities::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v);
    /**@}*/

    /**
     * @brief Provenance details of this codec element.
     */
    /**@{*/
    const dogen::identification::entities::codec_provenance& provenance() const;
    dogen::identification::entities::codec_provenance& provenance();
    void provenance(const dogen::identification::entities::codec_provenance& v);
    void provenance(const dogen::identification::entities::codec_provenance&& v);
    /**@}*/

    /**
     * @brief Meta-data sourced externally that can be used to override meta-data in model.
     */
    /**@{*/
    const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides();
    void tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>&& v);
    /**@}*/

    /**
     * @brief Properties associated with the codec comment.
     */
    /**@{*/
    const dogen::codec::entities::comment& comment() const;
    dogen::codec::entities::comment& comment();
    void comment(const dogen::codec::entities::comment& v);
    void comment(const dogen::codec::entities::comment&& v);
    /**@}*/

    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);

    /**
     * @brief Default value for this attribute, if any.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const attribute& rhs) const;
    bool operator!=(const attribute& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(attribute& other) noexcept;
    attribute& operator=(attribute other);

private:
    std::list<dogen::identification::entities::tagged_value> tagged_values_;
    std::list<dogen::identification::entities::stereotype> stereotypes_;
    dogen::identification::entities::name name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::codec_provenance provenance_;
    std::list<dogen::identification::entities::tagged_value> tagged_values_overrides_;
    dogen::codec::entities::comment comment_;
    std::string type_;
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::attribute& lhs,
    dogen::codec::entities::attribute& rhs) {
    lhs.swap(rhs);
}

}

#endif
