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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ELEMENT_CONFIGURATION_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ELEMENT_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/formatters/types/decoration_configuration.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_configuration.hpp"
#include "dogen/quilt.cpp/serialization/formattables/element_configuration_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief All of the configuration associated with an element.
 */
class element_configuration final {
public:
    element_configuration() = default;
    element_configuration(const element_configuration&) = default;
    ~element_configuration() = default;

public:
    element_configuration(element_configuration&& rhs);

public:
    element_configuration(
        const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration,
        const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& formatter_configuration,
        const std::list<dogen::quilt::cpp::formattables::helper_configuration>& helper_configuration,
        const dogen::quilt::cpp::formattables::aspect_configuration& aspect_configuration,
        const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& streaming_annotations);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::element_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::element_configuration& v, unsigned int version);

public:
    const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration() const;
    boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration();
    void decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>& v);
    void decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>&& v);

    const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& formatter_configuration() const;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& formatter_configuration();
    void formatter_configuration(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>& v);
    void formatter_configuration(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration>&& v);

    const std::list<dogen::quilt::cpp::formattables::helper_configuration>& helper_configuration() const;
    std::list<dogen::quilt::cpp::formattables::helper_configuration>& helper_configuration();
    void helper_configuration(const std::list<dogen::quilt::cpp::formattables::helper_configuration>& v);
    void helper_configuration(const std::list<dogen::quilt::cpp::formattables::helper_configuration>&& v);

    const dogen::quilt::cpp::formattables::aspect_configuration& aspect_configuration() const;
    dogen::quilt::cpp::formattables::aspect_configuration& aspect_configuration();
    void aspect_configuration(const dogen::quilt::cpp::formattables::aspect_configuration& v);
    void aspect_configuration(const dogen::quilt::cpp::formattables::aspect_configuration&& v);

    const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& streaming_annotations() const;
    boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& streaming_annotations();
    void streaming_annotations(const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>& v);
    void streaming_annotations(const boost::optional<dogen::quilt::cpp::annotations::streaming_annotations>&& v);

public:
    bool operator==(const element_configuration& rhs) const;
    bool operator!=(const element_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_configuration& other) noexcept;
    element_configuration& operator=(element_configuration other);

private:
    boost::optional<dogen::formatters::decoration_configuration> decoration_configuration_;
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration> formatter_configuration_;
    std::list<dogen::quilt::cpp::formattables::helper_configuration> helper_configuration_;
    dogen::quilt::cpp::formattables::aspect_configuration aspect_configuration_;
    boost::optional<dogen::quilt::cpp::annotations::streaming_annotations> streaming_annotations_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::element_configuration& lhs,
    dogen::quilt::cpp::formattables::element_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
