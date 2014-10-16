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
#ifndef DOGEN_CPP_TYPES_CLASS_ASPECTS_HPP
#define DOGEN_CPP_TYPES_CLASS_ASPECTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/class_aspects_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Aspects for C++ classes.
 */
class class_aspects final {
public:
    class_aspects(const class_aspects&) = default;
    class_aspects(class_aspects&&) = default;
    ~class_aspects() = default;

public:
    class_aspects();

public:
    class_aspects(
        const bool enable_complete_constructor,
        const bool generate_defaulted_functions,
        const bool generate_explicit_default_constructor,
        const bool generate_explicit_move_constructor,
        const bool generate_explicit_destructor,
        const bool destructor_is_pure_virtual,
        const bool generate_explicit_assignment_operator,
        const bool generate_complete_constructor,
        const bool generate_equality);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_aspects& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_aspects& v, unsigned int version);

public:
    /**
     * @brief If false, do not generate a constructor that takes as arguments as member
     * variables.
     */
    /**@{*/
    bool enable_complete_constructor() const;
    void enable_complete_constructor(const bool v);
    /**@}*/

    /**
     * @brief If set to true, all special defaulted functions will be generated.
     */
    /**@{*/
    bool generate_defaulted_functions() const;
    void generate_defaulted_functions(const bool v);
    /**@}*/

    /**
     * @brief If set to true, a default constructor will be generated.
     */
    /**@{*/
    bool generate_explicit_default_constructor() const;
    void generate_explicit_default_constructor(const bool v);
    /**@}*/

    /**
     * @brief If set to true, a move constructor will be generated.
     */
    /**@{*/
    bool generate_explicit_move_constructor() const;
    void generate_explicit_move_constructor(const bool v);
    /**@}*/

    /**
     * @brief If set to true, a destructor will be generated.
     */
    /**@{*/
    bool generate_explicit_destructor() const;
    void generate_explicit_destructor(const bool v);
    /**@}*/

    /**
     * @brief If set to true, the destructor will be a pure virtual function.
     */
    /**@{*/
    bool destructor_is_pure_virtual() const;
    void destructor_is_pure_virtual(const bool v);
    /**@}*/

    /**
     * @brief If set to true, an assignment operator will be generated.
     */
    /**@{*/
    bool generate_explicit_assignment_operator() const;
    void generate_explicit_assignment_operator(const bool v);
    /**@}*/

    bool generate_complete_constructor() const;
    void generate_complete_constructor(const bool v);

    /**
     * @brief If set to true, the equality operator will be generated.
     */
    /**@{*/
    bool generate_equality() const;
    void generate_equality(const bool v);
    /**@}*/

public:
    bool operator==(const class_aspects& rhs) const;
    bool operator!=(const class_aspects& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_aspects& other) noexcept;
    class_aspects& operator=(class_aspects other);

private:
    bool enable_complete_constructor_;
    bool generate_defaulted_functions_;
    bool generate_explicit_default_constructor_;
    bool generate_explicit_move_constructor_;
    bool generate_explicit_destructor_;
    bool destructor_is_pure_virtual_;
    bool generate_explicit_assignment_operator_;
    bool generate_complete_constructor_;
    bool generate_equality_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::class_aspects& lhs,
    dogen::cpp::class_aspects& rhs) {
    lhs.swap(rhs);
}

}

#endif
