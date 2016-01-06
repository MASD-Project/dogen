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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_CONCEPT_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_CONCEPT_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp/serialization/formattables/concept_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class concept_info final : public dogen::cpp::formattables::entity {
public:
    concept_info() = default;
    concept_info(const concept_info&) = default;
    concept_info(concept_info&&) = default;

    virtual ~concept_info() noexcept { }

public:
    concept_info(
        const std::string& identity,
        const dogen::cpp::formattables::origin_types origin_type,
        const std::string& id,
        const std::string& name,
        const std::string& qualified_name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::list<dogen::cpp::formattables::property_info>& properties,
        const std::list<dogen::cpp::formattables::property_info>& all_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const concept_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, concept_info& v, unsigned int version);

public:
    virtual void accept(const formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const formattable_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Properties of the type itself (e.g. excludes inherited properties).
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::property_info>& properties() const;
    std::list<dogen::cpp::formattables::property_info>& properties();
    void properties(const std::list<dogen::cpp::formattables::property_info>& v);
    void properties(const std::list<dogen::cpp::formattables::property_info>&& v);
    /**@}*/

    /**
     * @brief All properties of the type including inherited.
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::property_info>& all_properties() const;
    std::list<dogen::cpp::formattables::property_info>& all_properties();
    void all_properties(const std::list<dogen::cpp::formattables::property_info>& v);
    void all_properties(const std::list<dogen::cpp::formattables::property_info>&& v);
    /**@}*/

public:
    bool operator==(const concept_info& rhs) const;
    bool operator!=(const concept_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(concept_info& other) noexcept;
    concept_info& operator=(concept_info other);

private:
    std::list<dogen::cpp::formattables::property_info> properties_;
    std::list<dogen::cpp::formattables::property_info> all_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::concept_info& lhs,
    dogen::cpp::formattables::concept_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
