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
#ifndef DOGEN_SML_TYPES_MODULE_HPP
#define DOGEN_SML_TYPES_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/sml/serialization/module_fwd_ser.hpp"
#include "dogen/sml/types/model_element.hpp"
#include "dogen/sml/types/model_element_visitor.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Packaging unit.
 *
 * Aggregates a group of logically related types into a unit.
 */
class module final : public dogen::sml::model_element {
public:
    module() = default;
    module(const module&) = default;
    module(module&&) = default;

    virtual ~module() noexcept { }

public:
    module(
        const dogen::sml::qname& name,
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::generation_types& generation_type,
        const std::list<dogen::sml::qname>& members);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const module& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, module& v, unsigned int version);

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
     * @brief All the model elements contained in this module.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& members() const;
    std::list<dogen::sml::qname>& members();
    void members(const std::list<dogen::sml::qname>& v);
    void members(const std::list<dogen::sml::qname>&& v);
    /**@}*/

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::model_element& other) const override;

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::list<dogen::sml::qname> members_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::module& lhs,
    dogen::sml::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
