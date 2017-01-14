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
#ifndef DOGEN_UPSILON_TYPES_CONFIG_HPP
#define DOGEN_UPSILON_TYPES_CONFIG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/upsilon/types/output.hpp"
#include "dogen/upsilon/types/directory.hpp"
#include "dogen/upsilon/types/schema_ref.hpp"
#include "dogen/upsilon/serialization/config_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class config final {
public:
    config() = default;
    config(const config&) = default;
    ~config() = default;

public:
    config(config&& rhs);

public:
    config(
        const dogen::upsilon::directory& directory,
        const std::vector<dogen::upsilon::schema_ref>& schema_refs,
        const std::vector<dogen::upsilon::output>& outputs,
        const boost::filesystem::path& file_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::config& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::config& v, unsigned int version);

public:
    const dogen::upsilon::directory& directory() const;
    dogen::upsilon::directory& directory();
    void directory(const dogen::upsilon::directory& v);
    void directory(const dogen::upsilon::directory&& v);

    const std::vector<dogen::upsilon::schema_ref>& schema_refs() const;
    std::vector<dogen::upsilon::schema_ref>& schema_refs();
    void schema_refs(const std::vector<dogen::upsilon::schema_ref>& v);
    void schema_refs(const std::vector<dogen::upsilon::schema_ref>&& v);

    const std::vector<dogen::upsilon::output>& outputs() const;
    std::vector<dogen::upsilon::output>& outputs();
    void outputs(const std::vector<dogen::upsilon::output>& v);
    void outputs(const std::vector<dogen::upsilon::output>&& v);

    const boost::filesystem::path& file_name() const;
    boost::filesystem::path& file_name();
    void file_name(const boost::filesystem::path& v);
    void file_name(const boost::filesystem::path&& v);

public:
    bool operator==(const config& rhs) const;
    bool operator!=(const config& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(config& other) noexcept;
    config& operator=(config other);

private:
    dogen::upsilon::directory directory_;
    std::vector<dogen::upsilon::schema_ref> schema_refs_;
    std::vector<dogen::upsilon::output> outputs_;
    boost::filesystem::path file_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::config& lhs,
    dogen::upsilon::config& rhs) {
    lhs.swap(rhs);
}

}

#endif
