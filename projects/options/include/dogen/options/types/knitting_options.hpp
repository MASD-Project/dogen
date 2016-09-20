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
#ifndef DOGEN_OPTIONS_TYPES_KNITTING_OPTIONS_HPP
#define DOGEN_OPTIONS_TYPES_KNITTING_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/options/types/cpp_options.hpp"
#include "dogen/options/types/input_options.hpp"
#include "dogen/options/types/output_options.hpp"
#include "dogen/options/serialization/knitting_options_fwd_ser.hpp"

namespace dogen {
namespace options {

/**
 * @brief Configuration options related to the knit library.
 */
class knitting_options final {
public:
    knitting_options(const knitting_options&) = default;
    knitting_options(knitting_options&&) = default;
    ~knitting_options() = default;

public:
    knitting_options();

public:
    knitting_options(
        const bool verbose,
        const dogen::options::input_options& input,
        const dogen::options::output_options& output,
        const dogen::options::cpp_options& cpp);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::options::knitting_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::options::knitting_options& v, unsigned int version);

public:
    /**
     * @brief Provide additional diagnostic information in the log file.
     */
    /**@{*/
    bool verbose() const;
    void verbose(const bool v);
    /**@}*/

    /**
     * @brief All options related to inputs.
     */
    /**@{*/
    const dogen::options::input_options& input() const;
    dogen::options::input_options& input();
    void input(const dogen::options::input_options& v);
    void input(const dogen::options::input_options&& v);
    /**@}*/

    /**
     * @brief All options related to outputting.
     */
    /**@{*/
    const dogen::options::output_options& output() const;
    dogen::options::output_options& output();
    void output(const dogen::options::output_options& v);
    void output(const dogen::options::output_options&& v);
    /**@}*/

    /**
     * @brief All options related to the C++ backend.
     */
    /**@{*/
    const dogen::options::cpp_options& cpp() const;
    dogen::options::cpp_options& cpp();
    void cpp(const dogen::options::cpp_options& v);
    void cpp(const dogen::options::cpp_options&& v);
    /**@}*/

public:
    bool operator==(const knitting_options& rhs) const;
    bool operator!=(const knitting_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(knitting_options& other) noexcept;
    knitting_options& operator=(knitting_options other);

private:
    bool verbose_;
    dogen::options::input_options input_;
    dogen::options::output_options output_;
    dogen::options::cpp_options cpp_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::options::knitting_options& lhs,
    dogen::options::knitting_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
