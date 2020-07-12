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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_SERIALIZATION_TYPE_REGISTRAR_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_SERIALIZATION_TYPE_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"

namespace dogen::logical::entities::serialization {

/**
 * @brief Responsible for registering types for serialisation purposes.
 *
 * Certain libraries in certain technical spaces - such as Boost Serialisation, in C++ -
 * require types that are in an inheritance relationship to be made known to the
 * serialisation infrastructure in order for the deserialisation of base and derived
 * types to work. The type registrar is aware of all types with such requirements and
 * generates the registration code as needed.
 */
class type_registrar final : public dogen::logical::entities::element {
public:
    type_registrar() = default;
    type_registrar(const type_registrar&) = default;
    type_registrar(type_registrar&&) = default;

    virtual ~type_registrar() noexcept { }

public:
    type_registrar(
        const dogen::logical::entities::name& name,
        const std::string& documentation,
        const dogen::logical::entities::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::logical::entities::name& meta_name,
        const dogen::logical::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::logical::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::logical::entities::name>& leaves,
        const std::list<dogen::logical::entities::name>& registrar_dependencies);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief List of all concrete classes which are part of an inheritance tree.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& leaves() const;
    std::list<dogen::logical::entities::name>& leaves();
    void leaves(const std::list<dogen::logical::entities::name>& v);
    void leaves(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

    /**
     * @brief Registrars on other models this registrar depends on.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& registrar_dependencies() const;
    std::list<dogen::logical::entities::name>& registrar_dependencies();
    void registrar_dependencies(const std::list<dogen::logical::entities::name>& v);
    void registrar_dependencies(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

public:
    bool operator==(const type_registrar& rhs) const;
    bool operator!=(const type_registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(type_registrar& other) noexcept;
    type_registrar& operator=(type_registrar other);

private:
    std::list<dogen::logical::entities::name> leaves_;
    std::list<dogen::logical::entities::name> registrar_dependencies_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::serialization::type_registrar& lhs,
    dogen::logical::entities::serialization::type_registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
