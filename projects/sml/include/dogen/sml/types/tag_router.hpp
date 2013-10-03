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
#ifndef DOGEN_SML_TYPES_TAG_ROUTER_HPP
#define DOGEN_SML_TYPES_TAG_ROUTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>

namespace dogen {
namespace sml {

/**
 * @brief Given one or more key-value pairs, routes them to the
 * appropriate tag container.
 */
class tag_router {
public:
    tag_router() = delete;
    ~tag_router() noexcept = default;
    tag_router(const tag_router&) = default;
    tag_router(tag_router&&) = default;

public:
    tag_router(std::unordered_map<std::string, std::string>& simple_tags,
        std::unordered_map<std::string, std::list<std::string> >& complex_tags);

private:
    /**
     * @brief Returns true if the key belongs to the set of complex
     * tag keys.
     */
    bool is_complex(const std::string& key) const;

    /**
     * @brief Returns true if the key exists in the simple tags
     * container.
     */
    bool has_key(const std::string& key) const;

public:
    /**
     * @brief Routes the key-value pair to the appropriate tag
     * container, based on the key.
     */
    void route(const std::string& key, const std::string& value);

    /**
     * @brief Routes all key-value pairs to the appropriate tag
     * container, based on the key.
     */
    void route(const std::list<std::pair<std::string, std::string> >& kvps);

    /**
     * @brief Routes only if @e marker is in the input kvp container,
     * as a key.
     *
     * @return true if routing was done, false otherwise.
     */
    bool route_if_marker_found(const std::string& marker,
        const std::list<std::pair<std::string, std::string> >& kvps);

    /**
     * @brief Routes only if @e key is not in the simple tags
     * container.
     *
     * @return true if routing was done, false otherwise.
     */
    bool route_if_key_not_found(const std::string& key,
        const std::string& value);

private:
    std::unordered_map<std::string, std::string>& simple_tags_;
    std::unordered_map<std::string, std::list<std::string> >& complex_tags_;
};

template<typename Taggable>
inline tag_router make_tag_router(Taggable& t) {
    return tag_router(t.simple_tags(), t.complex_tags());
}

} }

#endif
