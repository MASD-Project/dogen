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
#ifndef DOGEN_SML_TYPES_CONCEPT_HPP
#define DOGEN_SML_TYPES_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/sml/serialization/concept_fwd_ser.hpp"
#include "dogen/sml/types/model_element.hpp"
#include "dogen/sml/types/model_element_visitor.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a concept, similar to the C++ definition.
 */
class concept final : public dogen::sml::model_element {
public:
    concept() = default;
    concept(const concept&) = default;
    concept(concept&&) = default;

    virtual ~concept() noexcept { }

public:
    concept(
        const dogen::sml::qname& name,
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::generation_types& generation_type,
        const std::list<dogen::sml::property>& properties,
        const std::list<dogen::sml::qname>& refines);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const concept& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, concept& v, unsigned int version);

public:
    virtual void accept(const model_element_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(model_element_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const model_element_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(model_element_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Attributes that belong to this type.
     *
     * Does not include inherited attributes.
     */
    /**@{*/
    const std::list<dogen::sml::property>& properties() const;
    std::list<dogen::sml::property>& properties();
    void properties(const std::list<dogen::sml::property>& v);
    void properties(const std::list<dogen::sml::property>&& v);
    /**@}*/

    /**
     * @brief List of concepts that this concept is a refinement of.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& refines() const;
    std::list<dogen::sml::qname>& refines();
    void refines(const std::list<dogen::sml::qname>& v);
    void refines(const std::list<dogen::sml::qname>&& v);
    /**@}*/

public:
    bool operator==(const concept& rhs) const;
    bool operator!=(const concept& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::model_element& other) const override;

public:
    void swap(concept& other) noexcept;
    concept& operator=(concept other);

private:
    std::list<dogen::sml::property> properties_;
    std::list<dogen::sml::qname> refines_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::concept& lhs,
    dogen::sml::concept& rhs) {
    lhs.swap(rhs);
}

}

#endif
