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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_ELEMENT_PROPERTIES_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_ELEMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.text.cpp/types/formattables/aspect_properties.hpp"
#include "dogen.text.cpp/types/formattables/helper_properties.hpp"
#include "dogen.text.cpp/types/formattables/artefact_properties.hpp"
#include "dogen.text.cpp/types/formattables/test_data_properties.hpp"

namespace dogen::text::cpp::formattables {

/**
 * @brief All of the properties associated with an element.
 */
class element_properties final {
public:
    element_properties() = default;
    element_properties(const element_properties&) = default;
    element_properties(element_properties&&) = default;
    ~element_properties() = default;

public:
    element_properties(
        const dogen::text::cpp::formattables::aspect_properties& aspect_properties,
        const std::unordered_map<std::string, dogen::text::cpp::formattables::artefact_properties>& artefact_properties,
        const std::list<dogen::text::cpp::formattables::helper_properties>& helper_properties,
        const std::unordered_map<std::string, std::string>& canonical_archetype_to_archetype,
        const std::unordered_map<std::string, dogen::text::cpp::formattables::test_data_properties>& attribute_level_test_data_properties);

public:
    const dogen::text::cpp::formattables::aspect_properties& aspect_properties() const;
    dogen::text::cpp::formattables::aspect_properties& aspect_properties();
    void aspect_properties(const dogen::text::cpp::formattables::aspect_properties& v);
    void aspect_properties(const dogen::text::cpp::formattables::aspect_properties&& v);

    const std::unordered_map<std::string, dogen::text::cpp::formattables::artefact_properties>& artefact_properties() const;
    std::unordered_map<std::string, dogen::text::cpp::formattables::artefact_properties>& artefact_properties();
    void artefact_properties(const std::unordered_map<std::string, dogen::text::cpp::formattables::artefact_properties>& v);
    void artefact_properties(const std::unordered_map<std::string, dogen::text::cpp::formattables::artefact_properties>&& v);

    const std::list<dogen::text::cpp::formattables::helper_properties>& helper_properties() const;
    std::list<dogen::text::cpp::formattables::helper_properties>& helper_properties();
    void helper_properties(const std::list<dogen::text::cpp::formattables::helper_properties>& v);
    void helper_properties(const std::list<dogen::text::cpp::formattables::helper_properties>&& v);

    const std::unordered_map<std::string, std::string>& canonical_archetype_to_archetype() const;
    std::unordered_map<std::string, std::string>& canonical_archetype_to_archetype();
    void canonical_archetype_to_archetype(const std::unordered_map<std::string, std::string>& v);
    void canonical_archetype_to_archetype(const std::unordered_map<std::string, std::string>&& v);

    const std::unordered_map<std::string, dogen::text::cpp::formattables::test_data_properties>& attribute_level_test_data_properties() const;
    std::unordered_map<std::string, dogen::text::cpp::formattables::test_data_properties>& attribute_level_test_data_properties();
    void attribute_level_test_data_properties(const std::unordered_map<std::string, dogen::text::cpp::formattables::test_data_properties>& v);
    void attribute_level_test_data_properties(const std::unordered_map<std::string, dogen::text::cpp::formattables::test_data_properties>&& v);

public:
    bool operator==(const element_properties& rhs) const;
    bool operator!=(const element_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_properties& other) noexcept;
    element_properties& operator=(element_properties other);

private:
    dogen::text::cpp::formattables::aspect_properties aspect_properties_;
    std::unordered_map<std::string, dogen::text::cpp::formattables::artefact_properties> artefact_properties_;
    std::list<dogen::text::cpp::formattables::helper_properties> helper_properties_;
    std::unordered_map<std::string, std::string> canonical_archetype_to_archetype_;
    std::unordered_map<std::string, dogen::text::cpp::formattables::test_data_properties> attribute_level_test_data_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::cpp::formattables::element_properties& lhs,
    dogen::text::cpp::formattables::element_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
