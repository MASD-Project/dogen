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
#ifndef DOGEN_CPP_TYPES_REGISTRAR_INFO_HPP
#define DOGEN_CPP_TYPES_REGISTRAR_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include <string>
#include "dogen/cpp/serialization/registrar_info_fwd_ser.hpp"
#include "dogen/cpp/types/entity.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a serialisation registrar for boost serialisation.
 */
class registrar_info final : public dogen::cpp::entity {
public:
    registrar_info() = default;
    registrar_info(const registrar_info&) = default;
    registrar_info(registrar_info&&) = default;

    virtual ~registrar_info() noexcept { }

public:
    registrar_info(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::unordered_map<std::string, dogen::cpp::file_settings>& file_settings_for_formatter,
        const std::list<std::string>& leaves,
        const std::list<std::string>& model_dependencies);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const registrar_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, registrar_info& v, unsigned int version);

public:
    virtual void accept(const entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const entity_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief List of all concrete classes which are part of an inheritance tree.
     */
    /**@{*/
    const std::list<std::string>& leaves() const;
    std::list<std::string>& leaves();
    void leaves(const std::list<std::string>& v);
    void leaves(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief List of all models which the model depends on.
     */
    /**@{*/
    const std::list<std::string>& model_dependencies() const;
    std::list<std::string>& model_dependencies();
    void model_dependencies(const std::list<std::string>& v);
    void model_dependencies(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const registrar_info& rhs) const;
    bool operator!=(const registrar_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::entity& other) const override;

public:
    void swap(registrar_info& other) noexcept;
    registrar_info& operator=(registrar_info other);

private:
    std::list<std::string> leaves_;
    std::list<std::string> model_dependencies_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::registrar_info& lhs,
    dogen::cpp::registrar_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
