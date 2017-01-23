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
#ifndef DOGEN_QUILT_TYPES_KERNEL_OUTPUT_HPP
#define DOGEN_QUILT_TYPES_KERNEL_OUTPUT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/quilt/serialization/kernel_output_fwd_ser.hpp"

namespace dogen {
namespace quilt {

class kernel_output final {
public:
    kernel_output() = default;
    kernel_output(const kernel_output&) = default;
    kernel_output(kernel_output&&) = default;
    ~kernel_output() = default;

public:
    kernel_output(
        const std::list<dogen::formatters::artefact>& artefacts,
        const std::list<boost::filesystem::path>& managed_directories);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::kernel_output& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::kernel_output& v, unsigned int version);

public:
    const std::list<dogen::formatters::artefact>& artefacts() const;
    std::list<dogen::formatters::artefact>& artefacts();
    void artefacts(const std::list<dogen::formatters::artefact>& v);
    void artefacts(const std::list<dogen::formatters::artefact>&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

public:
    bool operator==(const kernel_output& rhs) const;
    bool operator!=(const kernel_output& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(kernel_output& other) noexcept;
    kernel_output& operator=(kernel_output other);

private:
    std::list<dogen::formatters::artefact> artefacts_;
    std::list<boost::filesystem::path> managed_directories_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::quilt::kernel_output& lhs,
    dogen::quilt::kernel_output& rhs) {
    lhs.swap(rhs);
}

}

#endif
