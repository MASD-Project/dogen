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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/quilt.cpp/types/formattables/facet_profile.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_types.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_profile.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_profile.hpp"
#include "dogen/quilt.cpp/serialization/formattables/profile_group_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class profile_group final {
public:
    profile_group(const profile_group&) = default;
    ~profile_group() = default;

public:
    profile_group();

public:
    profile_group(profile_group&& rhs);

public:
    profile_group(
        const std::string& name,
        const std::list<std::string>& parent,
        const dogen::quilt::cpp::formattables::profile_types profile_type,
        const std::string& bind_to_stereotype,
        const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& decoration_profile,
        const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& default_facet_profile,
        const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& default_formatter_profile,
        const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& facet_profiles,
        const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& formatter_profiles);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::profile_group& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::profile_group& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& parent() const;
    std::list<std::string>& parent();
    void parent(const std::list<std::string>& v);
    void parent(const std::list<std::string>&& v);

    dogen::quilt::cpp::formattables::profile_types profile_type() const;
    void profile_type(const dogen::quilt::cpp::formattables::profile_types v);

    const std::string& bind_to_stereotype() const;
    std::string& bind_to_stereotype();
    void bind_to_stereotype(const std::string& v);
    void bind_to_stereotype(const std::string&& v);

    const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& decoration_profile() const;
    boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& decoration_profile();
    void decoration_profile(const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>& v);
    void decoration_profile(const boost::optional<dogen::quilt::cpp::formattables::decoration_profile>&& v);

    const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& default_facet_profile() const;
    boost::optional<dogen::quilt::cpp::formattables::facet_profile>& default_facet_profile();
    void default_facet_profile(const boost::optional<dogen::quilt::cpp::formattables::facet_profile>& v);
    void default_facet_profile(const boost::optional<dogen::quilt::cpp::formattables::facet_profile>&& v);

    const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& default_formatter_profile() const;
    boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& default_formatter_profile();
    void default_formatter_profile(const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>& v);
    void default_formatter_profile(const boost::optional<dogen::quilt::cpp::formattables::formatter_profile>&& v);

    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& facet_profiles() const;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& facet_profiles();
    void facet_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>& v);
    void facet_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile>&& v);

    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& formatter_profiles() const;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& formatter_profiles();
    void formatter_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>& v);
    void formatter_profiles(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile>&& v);

public:
    bool operator==(const profile_group& rhs) const;
    bool operator!=(const profile_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profile_group& other) noexcept;
    profile_group& operator=(profile_group other);

private:
    std::string name_;
    std::list<std::string> parent_;
    dogen::quilt::cpp::formattables::profile_types profile_type_;
    std::string bind_to_stereotype_;
    boost::optional<dogen::quilt::cpp::formattables::decoration_profile> decoration_profile_;
    boost::optional<dogen::quilt::cpp::formattables::facet_profile> default_facet_profile_;
    boost::optional<dogen::quilt::cpp::formattables::formatter_profile> default_formatter_profile_;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile> facet_profiles_;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile> formatter_profiles_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::profile_group& lhs,
    dogen::quilt::cpp::formattables::profile_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
