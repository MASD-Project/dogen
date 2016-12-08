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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FABRIC_VISUAL_STUDIO_SOLUTION_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FABRIC_VISUAL_STUDIO_SOLUTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.csharp/serialization/fabric/visual_studio_solution_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

class visual_studio_solution final : public dogen::yarn::element {
public:
    visual_studio_solution() = default;
    visual_studio_solution(const visual_studio_solution&) = default;
    visual_studio_solution(visual_studio_solution&&) = default;

    virtual ~visual_studio_solution() noexcept { }

public:
    visual_studio_solution(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const std::string& project_guid,
        const std::string& project_solution_guid,
        const std::string& version,
        const std::string& project_location);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::csharp::fabric::visual_studio_solution& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::csharp::fabric::visual_studio_solution& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& project_guid() const;
    std::string& project_guid();
    void project_guid(const std::string& v);
    void project_guid(const std::string&& v);

    const std::string& project_solution_guid() const;
    std::string& project_solution_guid();
    void project_solution_guid(const std::string& v);
    void project_solution_guid(const std::string&& v);

    const std::string& version() const;
    std::string& version();
    void version(const std::string& v);
    void version(const std::string&& v);

    const std::string& project_location() const;
    std::string& project_location();
    void project_location(const std::string& v);
    void project_location(const std::string&& v);

public:
    bool operator==(const visual_studio_solution& rhs) const;
    bool operator!=(const visual_studio_solution& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(visual_studio_solution& other) noexcept;
    visual_studio_solution& operator=(visual_studio_solution other);

private:
    std::string project_guid_;
    std::string project_solution_guid_;
    std::string version_;
    std::string project_location_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::csharp::fabric::visual_studio_solution& lhs,
    dogen::quilt::csharp::fabric::visual_studio_solution& rhs) {
    lhs.swap(rhs);
}

}

#endif
