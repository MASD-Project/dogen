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
#ifndef DOGEN_OM_TYPES_CPP_ABSTRACT_INSTANCE_HPP
#define DOGEN_OM_TYPES_CPP_ABSTRACT_INSTANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include <string>
#include "dogen/om/serialization/cpp_abstract_instance_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_typeref.hpp"
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

class cpp_abstract_instance : public dogen::om::cpp_feature {
public:
    cpp_abstract_instance() = default;
    cpp_abstract_instance(const cpp_abstract_instance&) = default;
    cpp_abstract_instance(cpp_abstract_instance&&) = default;

    virtual ~cpp_abstract_instance() noexcept = 0;

public:
    cpp_abstract_instance(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_typeref& type,
        const std::string& default_value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_abstract_instance& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_abstract_instance& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::list<dogen::om::doxygen_command>& commands() const;
    std::list<dogen::om::doxygen_command>& commands();
    void commands(const std::list<dogen::om::doxygen_command>& v);
    void commands(const std::list<dogen::om::doxygen_command>&& v);

    const dogen::om::cpp_typeref& type() const;
    dogen::om::cpp_typeref& type();
    void type(const dogen::om::cpp_typeref& v);
    void type(const dogen::om::cpp_typeref&& v);

    const std::string& default_value() const;
    std::string& default_value();
    void default_value(const std::string& v);
    void default_value(const std::string&& v);

protected:
    bool compare(const cpp_abstract_instance& rhs) const;
public:
    virtual bool equals(const dogen::om::cpp_feature& other) const = 0;

protected:
    void swap(cpp_abstract_instance& other) noexcept;

private:
    std::list<dogen::om::doxygen_command> commands_;
    dogen::om::cpp_typeref type_;
    std::string default_value_;
};

inline cpp_abstract_instance::~cpp_abstract_instance() noexcept { }

inline bool operator==(const cpp_abstract_instance& lhs, const cpp_abstract_instance& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
