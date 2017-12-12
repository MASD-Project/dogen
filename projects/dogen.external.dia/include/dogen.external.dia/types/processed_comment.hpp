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
#ifndef DOGEN_EXTERNAL_DIA_TYPES_PROCESSED_COMMENT_HPP
#define DOGEN_EXTERNAL_DIA_TYPES_PROCESSED_COMMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen.external.dia/serialization/processed_comment_fwd_ser.hpp"

namespace dogen {
namespace external {
namespace dia {

/**
 * @brief Contains the same content as the original dia comment, but split by type of data.
 */
class processed_comment final {
public:
    processed_comment(const processed_comment&) = default;
    processed_comment(processed_comment&&) = default;
    ~processed_comment() = default;

public:
    processed_comment();

public:
    processed_comment(
        const std::string& documentation,
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const bool applicable_to_parent_object,
        const std::string& original_content,
        const std::string& external_modules);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::external::dia::processed_comment& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::external::dia::processed_comment& v, unsigned int version);

public:
    /**
     * @brief Text of the comment, excluding all Dogen instructions.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Dogen instructions, in the key-value-pair form.
     */
    /**@{*/
    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief If true, the comment should be attached to the dia object containing it.
     */
    /**@{*/
    bool applicable_to_parent_object() const;
    void applicable_to_parent_object(const bool v);
    /**@}*/

    /**
     * @brief Content of the field as it was read from the dia object.
     */
    /**@{*/
    const std::string& original_content() const;
    std::string& original_content();
    void original_content(const std::string& v);
    void original_content(const std::string&& v);
    /**@}*/

    /**
     * @brief The external module path, if any was supplied.
     */
    /**@{*/
    const std::string& external_modules() const;
    std::string& external_modules();
    void external_modules(const std::string& v);
    void external_modules(const std::string&& v);
    /**@}*/

public:
    bool operator==(const processed_comment& rhs) const;
    bool operator!=(const processed_comment& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(processed_comment& other) noexcept;
    processed_comment& operator=(processed_comment other);

private:
    std::string documentation_;
    std::list<std::pair<std::string, std::string> > tagged_values_;
    bool applicable_to_parent_object_;
    std::string original_content_;
    std::string external_modules_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::external::dia::processed_comment& lhs,
    dogen::external::dia::processed_comment& rhs) {
    lhs.swap(rhs);
}

}

#endif
