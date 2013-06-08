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
#ifndef DOGEN_SML_TYPES_MODEL_ELEMENT_HPP
#define DOGEN_SML_TYPES_MODEL_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include <utility>
#include <vector>
#include "dogen/sml/serialization/model_element_fwd_ser.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/model_element_visitor.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Fundamental unit of modeling.
 *
 * This roughly corresponds to the often mentioned "thing" in Domain
 * Driven Design. Its a unit of modeling in the sense that it distils
 * what is common to all the things that belong to a domain model.
 */
class model_element {
public:
    model_element(const model_element&) = default;
    model_element(model_element&&) = default;

public:
    model_element();

    virtual ~model_element() noexcept = 0;

public:
    model_element(
        const dogen::sml::qname& name,
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::generation_types& generation_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const model_element& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, model_element& v, unsigned int version);

public:
    virtual void accept(const model_element_visitor& v) const = 0;
    virtual void accept(model_element_visitor& v) const = 0;
    virtual void accept(const model_element_visitor& v) = 0;
    virtual void accept(model_element_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Qualified name for the element.
     *
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief Modeling specification of this element.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Parameters associated with the element which are opaque to SML.
     */
    /**@{*/
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief What type of code generation to perform for model element.
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types& v);
    /**@}*/

protected:
    bool compare(const model_element& rhs) const;
public:
    virtual bool equals(const model_element& other) const = 0;

protected:
    void swap(model_element& other) noexcept;

private:
    dogen::sml::qname name_;
    std::string documentation_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
    dogen::sml::generation_types generation_type_;
};

inline model_element::~model_element() noexcept { }

inline bool operator==(const model_element& lhs, const model_element& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
