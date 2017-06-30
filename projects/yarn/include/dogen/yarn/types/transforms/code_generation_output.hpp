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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_CODE_GENERATION_OUTPUT_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_CODE_GENERATION_OUTPUT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/yarn/serialization/transforms/code_generation_output_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class code_generation_output final {
public:
    code_generation_output() = default;
    code_generation_output(const code_generation_output&) = default;
    code_generation_output(code_generation_output&&) = default;
    ~code_generation_output() = default;

public:
    code_generation_output(
        const std::list<dogen::formatters::artefact>& artefacts,
        const std::list<boost::filesystem::path>& managed_directories);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::transforms::code_generation_output& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::transforms::code_generation_output& v, unsigned int version);

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
    bool operator==(const code_generation_output& rhs) const;
    bool operator!=(const code_generation_output& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(code_generation_output& other) noexcept;
    code_generation_output& operator=(code_generation_output other);

private:
    std::list<dogen::formatters::artefact> artefacts_;
    std::list<boost::filesystem::path> managed_directories_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::transforms::code_generation_output& lhs,
    dogen::yarn::transforms::code_generation_output& rhs) {
    lhs.swap(rhs);
}

}

#endif
