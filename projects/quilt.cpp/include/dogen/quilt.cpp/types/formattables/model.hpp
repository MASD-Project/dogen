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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_MODEL_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/facet_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/streaming_properties.hpp"
#include "dogen/quilt.cpp/serialization/formattables/model_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const dogen::yarn::name& name,
        const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& streaming_properties,
        const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& formattables,
        const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& facet_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::model& v, unsigned int version);

public:
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);

    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& streaming_properties() const;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& streaming_properties();
    void streaming_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>& v);
    void streaming_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties>&& v);

    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& formattables() const;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& formattables();
    void formattables(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>& v);
    void formattables(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable>&& v);

    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& facet_properties() const;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>& v);
    void facet_properties(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::yarn::name name_;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::streaming_properties> streaming_properties_;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable> formattables_;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_properties> facet_properties_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::model& lhs,
    dogen::quilt::cpp::formattables::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
