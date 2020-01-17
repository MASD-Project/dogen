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
#ifndef DOGEN_GENERATION_CPP_TYPES_FABRIC_REGISTRAR_HPP
#define DOGEN_GENERATION_CPP_TYPES_FABRIC_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"

namespace dogen::generation::cpp::fabric {

class registrar final : public dogen::assets::meta_model::element {
public:
    registrar() = default;
    registrar(const registrar&) = default;
    registrar(registrar&&) = default;

    virtual ~registrar() noexcept { }

public:
    registrar(
        const dogen::assets::meta_model::name& name,
        const std::string& documentation,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
        const std::list<dogen::assets::meta_model::name>& leaves,
        const std::list<dogen::assets::meta_model::name>& model_dependencies,
        const std::list<dogen::assets::meta_model::name>& registrar_dependencies);

public:
    using dogen::assets::meta_model::element::accept;

    virtual void accept(const dogen::assets::meta_model::element_visitor& v) const override;
    virtual void accept(dogen::assets::meta_model::element_visitor& v) const override;
    virtual void accept(const dogen::assets::meta_model::element_visitor& v) override;
    virtual void accept(dogen::assets::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief List of all concrete classes which are part of an inheritance tree.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& leaves() const;
    std::list<dogen::assets::meta_model::name>& leaves();
    void leaves(const std::list<dogen::assets::meta_model::name>& v);
    void leaves(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief List of all models which the model depends on.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& model_dependencies() const;
    std::list<dogen::assets::meta_model::name>& model_dependencies();
    void model_dependencies(const std::list<dogen::assets::meta_model::name>& v);
    void model_dependencies(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Registrars on other models this registrar depends on.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& registrar_dependencies() const;
    std::list<dogen::assets::meta_model::name>& registrar_dependencies();
    void registrar_dependencies(const std::list<dogen::assets::meta_model::name>& v);
    void registrar_dependencies(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

public:
    bool operator==(const registrar& rhs) const;
    bool operator!=(const registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(registrar& other) noexcept;
    registrar& operator=(registrar other);

private:
    std::list<dogen::assets::meta_model::name> leaves_;
    std::list<dogen::assets::meta_model::name> model_dependencies_;
    std::list<dogen::assets::meta_model::name> registrar_dependencies_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::fabric::registrar& lhs,
    dogen::generation::cpp::fabric::registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
