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
#ifndef DOGEN_CPP_TYPES_VIEW_MODELS_REGISTRAR_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_VIEW_MODELS_REGISTRAR_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/view_models/registrar_view_model_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class registrar_view_model final {
public:
    registrar_view_model() = default;
    registrar_view_model(const registrar_view_model&) = default;
    registrar_view_model(registrar_view_model&&) = default;
    ~registrar_view_model() = default;

public:
    registrar_view_model(
        const std::list<std::string>& namespaces,
        const std::list<std::string>& leaves,
        const std::list<std::string>& model_dependencies);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const registrar_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, registrar_view_model& v, unsigned int version);

public:
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);

    const std::list<std::string>& leaves() const;
    std::list<std::string>& leaves();
    void leaves(const std::list<std::string>& v);
    void leaves(const std::list<std::string>&& v);

    const std::list<std::string>& model_dependencies() const;
    std::list<std::string>& model_dependencies();
    void model_dependencies(const std::list<std::string>& v);
    void model_dependencies(const std::list<std::string>&& v);

public:
    bool operator==(const registrar_view_model& rhs) const;
    bool operator!=(const registrar_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(registrar_view_model& other) noexcept;
    registrar_view_model& operator=(registrar_view_model other);

private:
    std::list<std::string> namespaces_;
    std::list<std::string> leaves_;
    std::list<std::string> model_dependencies_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::view_models::registrar_view_model& lhs,
    dogen::cpp::view_models::registrar_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
