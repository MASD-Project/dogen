/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TYPES_TAG_ADAPTOR_HPP
#define DOGEN_SML_TYPES_TAG_ADAPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>

namespace dogen {
namespace sml {

class tag_adaptor {
public:
    tag_adaptor() = delete;
    ~tag_adaptor() noexcept = default;
    tag_adaptor(const tag_adaptor&) = default;
    tag_adaptor(tag_adaptor&&) = default;

public:
    tag_adaptor(const std::unordered_map<std::string, std::string>& simple_tags,
        const std::unordered_map<std::string, std::list<std::string> >&
        complex_tags);

public:
    /**
     * @brief Returns true if the tags contain the comment key, false
     * otherwise.
     */
    bool has_comment() const;

    /**
     * @brief Returns true if the tags contain the identity key, false
     * otherwise.
     */
    bool has_identity() const;

    /**
     * @brief Returns the value of "generate explicitly defaulted functions".
     */
    bool generate_explicitly_defaulted_functions() const;

    /**
     * @brief Returns the value of "requires manual default constructor".
     */
    bool requires_manual_default_constructor() const;

    /**
     * @brief Returns the value of "requires manual move constructor".
     */
    bool requires_manual_move_constructor() const;

public:
    /**
     * @brief Returns the odb pragmas.
     *
     * @deprecated this method is only needed for the transition to
     * OM.
     */
    std::list<std::pair<std::string,std::string> > odb_pragma() const;

private:
    const std::unordered_map<std::string, std::string>& simple_tags_;
    const std::unordered_map<std::string, std::list<std::string> >&
    complex_tags_;
};

template<typename Taggable>
inline tag_adaptor make_tag_adaptor(const Taggable& t) {
    return tag_adaptor(t.simple_tags(), t.complex_tags());
}

} }

#endif
