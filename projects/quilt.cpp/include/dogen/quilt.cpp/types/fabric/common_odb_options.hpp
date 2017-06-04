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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_COMMON_ODB_OPTIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_COMMON_ODB_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/serialization/fabric/common_odb_options_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class common_odb_options final : public dogen::yarn::element {
public:
    common_odb_options() = default;
    common_odb_options(const common_odb_options&) = default;
    common_odb_options(common_odb_options&&) = default;

    virtual ~common_odb_options() noexcept { }

public:
    common_odb_options(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const dogen::yarn::element_properties& element_properties,
        const std::string& sql_name_case,
        const std::list<std::string>& databases);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::common_odb_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::common_odb_options& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& sql_name_case() const;
    std::string& sql_name_case();
    void sql_name_case(const std::string& v);
    void sql_name_case(const std::string&& v);

    const std::list<std::string>& databases() const;
    std::list<std::string>& databases();
    void databases(const std::list<std::string>& v);
    void databases(const std::list<std::string>&& v);

public:
    bool operator==(const common_odb_options& rhs) const;
    bool operator!=(const common_odb_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(common_odb_options& other) noexcept;
    common_odb_options& operator=(common_odb_options other);

private:
    std::string sql_name_case_;
    std::list<std::string> databases_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::common_odb_options& lhs,
    dogen::quilt::cpp::fabric::common_odb_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
