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
#ifndef DOGEN_UPSILON_TYPES_SCHEMA_HPP
#define DOGEN_UPSILON_TYPES_SCHEMA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/upsilon/types/tag.hpp"
#include "dogen/upsilon/types/type_fwd.hpp"
#include "dogen/upsilon/types/dependency.hpp"
#include "dogen/upsilon/serialization/schema_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class schema final {
public:
    schema() = default;
    schema(const schema&) = default;
    ~schema() = default;

public:
    schema(schema&& rhs);

public:
    schema(
        const std::string& name,
        const std::string& id_min,
        const std::string& id_max,
        const std::string& base_guid,
        const std::vector<dogen::upsilon::dependency>& dependencies,
        const std::vector<dogen::upsilon::tag>& tags,
        const std::vector<boost::shared_ptr<dogen::upsilon::type> >& types,
        const boost::filesystem::path& file_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::schema& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::schema& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& id_min() const;
    std::string& id_min();
    void id_min(const std::string& v);
    void id_min(const std::string&& v);

    const std::string& id_max() const;
    std::string& id_max();
    void id_max(const std::string& v);
    void id_max(const std::string&& v);

    const std::string& base_guid() const;
    std::string& base_guid();
    void base_guid(const std::string& v);
    void base_guid(const std::string&& v);

    const std::vector<dogen::upsilon::dependency>& dependencies() const;
    std::vector<dogen::upsilon::dependency>& dependencies();
    void dependencies(const std::vector<dogen::upsilon::dependency>& v);
    void dependencies(const std::vector<dogen::upsilon::dependency>&& v);

    const std::vector<dogen::upsilon::tag>& tags() const;
    std::vector<dogen::upsilon::tag>& tags();
    void tags(const std::vector<dogen::upsilon::tag>& v);
    void tags(const std::vector<dogen::upsilon::tag>&& v);

    const std::vector<boost::shared_ptr<dogen::upsilon::type> >& types() const;
    std::vector<boost::shared_ptr<dogen::upsilon::type> >& types();
    void types(const std::vector<boost::shared_ptr<dogen::upsilon::type> >& v);
    void types(const std::vector<boost::shared_ptr<dogen::upsilon::type> >&& v);

    const boost::filesystem::path& file_name() const;
    boost::filesystem::path& file_name();
    void file_name(const boost::filesystem::path& v);
    void file_name(const boost::filesystem::path&& v);

public:
    bool operator==(const schema& rhs) const;
    bool operator!=(const schema& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(schema& other) noexcept;
    schema& operator=(schema other);

private:
    std::string name_;
    std::string id_min_;
    std::string id_max_;
    std::string base_guid_;
    std::vector<dogen::upsilon::dependency> dependencies_;
    std::vector<dogen::upsilon::tag> tags_;
    std::vector<boost::shared_ptr<dogen::upsilon::type> > types_;
    boost::filesystem::path file_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::schema& lhs,
    dogen::upsilon::schema& rhs) {
    lhs.swap(rhs);
}

}

#endif
