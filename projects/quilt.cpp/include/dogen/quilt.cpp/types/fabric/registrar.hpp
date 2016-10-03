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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_REGISTRAR_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/serialization/fabric/registrar_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class registrar final : public dogen::yarn::element {
public:
    registrar() = default;
    registrar(const registrar&) = default;
    registrar(registrar&&) = default;

    virtual ~registrar() noexcept { }

public:
    registrar(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const bool is_element_extension,
        const std::list<dogen::yarn::name>& leaves,
        const std::list<dogen::yarn::name>& model_dependencies,
        const std::list<dogen::yarn::name>& registrar_dependencies);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::registrar& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::registrar& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief List of all concrete classes which are part of an inheritance tree.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& leaves() const;
    std::list<dogen::yarn::name>& leaves();
    void leaves(const std::list<dogen::yarn::name>& v);
    void leaves(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief List of all models which the model depends on.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& model_dependencies() const;
    std::list<dogen::yarn::name>& model_dependencies();
    void model_dependencies(const std::list<dogen::yarn::name>& v);
    void model_dependencies(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Registrars on other models this registrar depends on.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& registrar_dependencies() const;
    std::list<dogen::yarn::name>& registrar_dependencies();
    void registrar_dependencies(const std::list<dogen::yarn::name>& v);
    void registrar_dependencies(const std::list<dogen::yarn::name>&& v);
    /**@}*/

public:
    bool operator==(const registrar& rhs) const;
    bool operator!=(const registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(registrar& other) noexcept;
    registrar& operator=(registrar other);

private:
    std::list<dogen::yarn::name> leaves_;
    std::list<dogen::yarn::name> model_dependencies_;
    std::list<dogen::yarn::name> registrar_dependencies_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::registrar& lhs,
    dogen::quilt::cpp::fabric::registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
