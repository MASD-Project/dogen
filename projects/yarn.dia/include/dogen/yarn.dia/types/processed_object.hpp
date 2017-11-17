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
#ifndef DOGEN_YARN_DIA_TYPES_PROCESSED_OBJECT_HPP
#define DOGEN_YARN_DIA_TYPES_PROCESSED_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn.dia/types/dia_object_types.hpp"
#include "dogen/yarn.dia/types/processed_comment.hpp"
#include "dogen/yarn.dia/types/yarn_element_types.hpp"
#include "dogen/yarn.dia/types/processed_attribute.hpp"
#include "dogen/yarn/types/meta_model/well_known_stereotypes.hpp"
#include "dogen/yarn.dia/serialization/processed_object_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Representation of a dia object after first stage processing.
 */
class processed_object final {
public:
    processed_object(const processed_object&) = default;
    ~processed_object() = default;

public:
    processed_object();

public:
    processed_object(processed_object&& rhs);

public:
    processed_object(
        const std::string& id,
        const std::string& name,
        const dogen::yarn::dia::dia_object_types dia_object_type,
        const dogen::yarn::dia::yarn_element_types yarn_element_type,
        const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
        const std::vector<std::string>& unknown_stereotypes,
        const dogen::yarn::dia::processed_comment& comment,
        const std::string& child_node_id,
        const boost::optional<std::pair<std::string, std::string> >& connection,
        const std::list<dogen::yarn::dia::processed_attribute>& attributes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::dia::processed_object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::dia::processed_object& v, unsigned int version);

public:
    /**
     * @brief Dia object id.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the object in dia format.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the dia object.
     */
    /**@{*/
    dogen::yarn::dia::dia_object_types dia_object_type() const;
    void dia_object_type(const dogen::yarn::dia::dia_object_types v);
    /**@}*/

    dogen::yarn::dia::yarn_element_types yarn_element_type() const;
    void yarn_element_type(const dogen::yarn::dia::yarn_element_types v);

    const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes() const;
    std::vector<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes();
    void well_known_stereotypes(const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& v);
    void well_known_stereotypes(const std::vector<dogen::yarn::meta_model::well_known_stereotypes>&& v);

    const std::vector<std::string>& unknown_stereotypes() const;
    std::vector<std::string>& unknown_stereotypes();
    void unknown_stereotypes(const std::vector<std::string>& v);
    void unknown_stereotypes(const std::vector<std::string>&& v);

    /**
     * @brief Any comments associated with the object.
     *
     * On the case of a UML note, represents the text of the note.
     */
    /**@{*/
    const dogen::yarn::dia::processed_comment& comment() const;
    dogen::yarn::dia::processed_comment& comment();
    void comment(const dogen::yarn::dia::processed_comment& v);
    void comment(const dogen::yarn::dia::processed_comment&& v);
    /**@}*/

    /**
     * @brief If the object is contained in another object, its node id.
     */
    /**@{*/
    const std::string& child_node_id() const;
    std::string& child_node_id();
    void child_node_id(const std::string& v);
    void child_node_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Connections this object may have with other objects.
     */
    /**@{*/
    const boost::optional<std::pair<std::string, std::string> >& connection() const;
    boost::optional<std::pair<std::string, std::string> >& connection();
    void connection(const boost::optional<std::pair<std::string, std::string> >& v);
    void connection(const boost::optional<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief All attributes associated with dia object.
     */
    /**@{*/
    const std::list<dogen::yarn::dia::processed_attribute>& attributes() const;
    std::list<dogen::yarn::dia::processed_attribute>& attributes();
    void attributes(const std::list<dogen::yarn::dia::processed_attribute>& v);
    void attributes(const std::list<dogen::yarn::dia::processed_attribute>&& v);
    /**@}*/

public:
    bool operator==(const processed_object& rhs) const;
    bool operator!=(const processed_object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(processed_object& other) noexcept;
    processed_object& operator=(processed_object other);

private:
    std::string id_;
    std::string name_;
    dogen::yarn::dia::dia_object_types dia_object_type_;
    dogen::yarn::dia::yarn_element_types yarn_element_type_;
    std::vector<dogen::yarn::meta_model::well_known_stereotypes> well_known_stereotypes_;
    std::vector<std::string> unknown_stereotypes_;
    dogen::yarn::dia::processed_comment comment_;
    std::string child_node_id_;
    boost::optional<std::pair<std::string, std::string> > connection_;
    std::list<dogen::yarn::dia::processed_attribute> attributes_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::dia::processed_object& lhs,
    dogen::yarn::dia::processed_object& rhs) {
    lhs.swap(rhs);
}

}

#endif
