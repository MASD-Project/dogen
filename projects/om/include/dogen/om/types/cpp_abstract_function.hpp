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
#ifndef DOGEN_OM_TYPES_CPP_ABSTRACT_FUNCTION_HPP
#define DOGEN_OM_TYPES_CPP_ABSTRACT_FUNCTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/cpp_abstract_function_fwd_ser.hpp"
#include "dogen/om/types/cpp_argument.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_instance_typeref.hpp"
#include "dogen/om/types/cpp_representation_types.hpp"
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

class cpp_abstract_function : public dogen::om::cpp_feature {
public:
    cpp_abstract_function(const cpp_abstract_function&) = default;
    cpp_abstract_function(cpp_abstract_function&&) = default;

public:
    cpp_abstract_function();

    virtual ~cpp_abstract_function() noexcept = 0;

public:
    cpp_abstract_function(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_representation_types& representation_type,
        const bool is_inline,
        const dogen::om::cpp_instance_typeref& return_type,
        const std::list<dogen::om::cpp_argument>& arguments,
        const bool is_friend);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_abstract_function& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_abstract_function& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::list<dogen::om::doxygen_command>& commands() const;
    std::list<dogen::om::doxygen_command>& commands();
    void commands(const std::list<dogen::om::doxygen_command>& v);
    void commands(const std::list<dogen::om::doxygen_command>&& v);

    dogen::om::cpp_representation_types representation_type() const;
    void representation_type(const dogen::om::cpp_representation_types& v);

    bool is_inline() const;
    void is_inline(const bool v);

    const dogen::om::cpp_instance_typeref& return_type() const;
    dogen::om::cpp_instance_typeref& return_type();
    void return_type(const dogen::om::cpp_instance_typeref& v);
    void return_type(const dogen::om::cpp_instance_typeref&& v);

    const std::list<dogen::om::cpp_argument>& arguments() const;
    std::list<dogen::om::cpp_argument>& arguments();
    void arguments(const std::list<dogen::om::cpp_argument>& v);
    void arguments(const std::list<dogen::om::cpp_argument>&& v);

    bool is_friend() const;
    void is_friend(const bool v);

protected:
    bool compare(const cpp_abstract_function& rhs) const;
public:
    virtual bool equals(const dogen::om::cpp_feature& other) const = 0;

protected:
    void swap(cpp_abstract_function& other) noexcept;

private:
    std::list<dogen::om::doxygen_command> commands_;
    dogen::om::cpp_representation_types representation_type_;
    bool is_inline_;
    dogen::om::cpp_instance_typeref return_type_;
    std::list<dogen::om::cpp_argument> arguments_;
    bool is_friend_;
};

inline cpp_abstract_function::~cpp_abstract_function() noexcept { }

inline bool operator==(const cpp_abstract_function& lhs, const cpp_abstract_function& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
