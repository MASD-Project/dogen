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
#ifndef DOGEN_CPPIM_TYPES_PREAMBLE_HPP
#define DOGEN_CPPIM_TYPES_PREAMBLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include <string>
#include <utility>
#include "dogen/cppim/serialization/preamble_fwd_ser.hpp"
#include "dogen/cppim/types/feature.hpp"

namespace dogen {
namespace cppim {

/**
 * @brief Fields representing editor hints such as emacs and or vi mode, etc.
 *
 * A field is a key-value pair (KVP), where name is the first element and its value
 * the second.
 *
 * Example: -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * In this particular case, both prefix and postfix are @e -*-; @e mode is the first
 * field name and its value is @e c++; the KVP separator is @e : and the field
 * separator is @e ;.
 */
class preamble final : public dogen::cppim::feature {
public:
    preamble() = default;
    preamble(const preamble&) = default;
    preamble(preamble&&) = default;

    virtual ~preamble() noexcept { }

public:
    preamble(
        const std::string& prefix,
        const std::list<std::pair<std::string, std::string> >& fields,
        const std::string& kvp_separator,
        const std::string& field_separator,
        const std::string& postfix);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const preamble& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, preamble& v, unsigned int version);

public:
    virtual void accept(const feature_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(feature_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const feature_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(feature_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Starting field in the preamble.
     */
    /**@{*/
    const std::string& prefix() const;
    std::string& prefix();
    void prefix(const std::string& v);
    void prefix(const std::string&& v);
    /**@}*/

    /**
     * @brief List of all the parameters in the preamble, in order of appearence.
     */
    /**@{*/
    const std::list<std::pair<std::string, std::string> >& fields() const;
    std::list<std::pair<std::string, std::string> >& fields();
    void fields(const std::list<std::pair<std::string, std::string> >& v);
    void fields(const std::list<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief Character or set of characters used to separate multiple key-value pairs.
     */
    /**@{*/
    const std::string& kvp_separator() const;
    std::string& kvp_separator();
    void kvp_separator(const std::string& v);
    void kvp_separator(const std::string&& v);
    /**@}*/

    /**
     * @brief Character or set or characters used to distinguish between a field's name and its value.
     */
    /**@{*/
    const std::string& field_separator() const;
    std::string& field_separator();
    void field_separator(const std::string& v);
    void field_separator(const std::string&& v);
    /**@}*/

    /**
     * @brief Ending field in the preamble.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const preamble& rhs) const;
    bool operator!=(const preamble& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cppim::feature& other) const override;

public:
    void swap(preamble& other) noexcept;
    preamble& operator=(preamble other);

private:
    std::string prefix_;
    std::list<std::pair<std::string, std::string> > fields_;
    std::string kvp_separator_;
    std::string field_separator_;
    std::string postfix_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cppim::preamble& lhs,
    dogen::cppim::preamble& rhs) {
    lhs.swap(rhs);
}

}

#endif
