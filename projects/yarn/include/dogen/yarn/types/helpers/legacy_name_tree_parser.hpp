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
#ifndef DOGEN_YARN_TYPES_HELPERS_LEGACY_NAME_TREE_PARSER_HPP
#define DOGEN_YARN_TYPES_HELPERS_LEGACY_NAME_TREE_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>

namespace dogen {
namespace yarn {
namespace helpers {

class legacy_name_tree_parser final {
public:
    legacy_name_tree_parser() = default;
    legacy_name_tree_parser(const legacy_name_tree_parser&) = default;
    legacy_name_tree_parser(legacy_name_tree_parser&&) = default;
    ~legacy_name_tree_parser() = default;

public:
    legacy_name_tree_parser(
        const std::unordered_set<std::string>& modules,
        const std::list<std::string>& external_modules,
        const std::string& model_name);

public:
    const std::unordered_set<std::string>& modules() const;
    std::unordered_set<std::string>& modules();
    void modules(const std::unordered_set<std::string>& v);
    void modules(const std::unordered_set<std::string>&& v);

    const std::list<std::string>& external_modules() const;
    std::list<std::string>& external_modules();
    void external_modules(const std::list<std::string>& v);
    void external_modules(const std::list<std::string>&& v);

    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);

public:
    bool operator==(const legacy_name_tree_parser& rhs) const;
    bool operator!=(const legacy_name_tree_parser& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(legacy_name_tree_parser& other) noexcept;
    legacy_name_tree_parser& operator=(legacy_name_tree_parser other);

private:
    std::unordered_set<std::string> modules_;
    std::list<std::string> external_modules_;
    std::string model_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::helpers::legacy_name_tree_parser& lhs,
    dogen::yarn::helpers::legacy_name_tree_parser& rhs) {
    lhs.swap(rhs);
}

}

#endif
