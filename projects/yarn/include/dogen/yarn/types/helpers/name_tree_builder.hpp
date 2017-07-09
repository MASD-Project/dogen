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
#ifndef DOGEN_YARN_TYPES_HELPERS_NAME_TREE_BUILDER_HPP
#define DOGEN_YARN_TYPES_HELPERS_NAME_TREE_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen/yarn/types/location.hpp"
#include "dogen/yarn/types/helpers/node_fwd.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class name_tree_builder final {
public:
    name_tree_builder() = default;
    name_tree_builder(const name_tree_builder&) = default;
    name_tree_builder(name_tree_builder&&) = default;
    ~name_tree_builder() = default;

public:
    name_tree_builder(
        const std::unordered_set<std::string>& top_level_modules_,
        const dogen::yarn::location& model_location_,
        const std::list<std::string>& names,
        const std::shared_ptr<dogen::yarn::helpers::node>& root,
        const std::shared_ptr<dogen::yarn::helpers::node>& current);

public:
    const std::unordered_set<std::string>& top_level_modules_() const;
    std::unordered_set<std::string>& top_level_modules_();
    void top_level_modules_(const std::unordered_set<std::string>& v);
    void top_level_modules_(const std::unordered_set<std::string>&& v);

    const dogen::yarn::location& model_location_() const;
    dogen::yarn::location& model_location_();
    void model_location_(const dogen::yarn::location& v);
    void model_location_(const dogen::yarn::location&& v);

    const std::list<std::string>& names() const;
    std::list<std::string>& names();
    void names(const std::list<std::string>& v);
    void names(const std::list<std::string>&& v);

    const std::shared_ptr<dogen::yarn::helpers::node>& root() const;
    std::shared_ptr<dogen::yarn::helpers::node>& root();
    void root(const std::shared_ptr<dogen::yarn::helpers::node>& v);
    void root(const std::shared_ptr<dogen::yarn::helpers::node>&& v);

    const std::shared_ptr<dogen::yarn::helpers::node>& current() const;
    std::shared_ptr<dogen::yarn::helpers::node>& current();
    void current(const std::shared_ptr<dogen::yarn::helpers::node>& v);
    void current(const std::shared_ptr<dogen::yarn::helpers::node>&& v);

public:
    bool operator==(const name_tree_builder& rhs) const;
    bool operator!=(const name_tree_builder& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name_tree_builder& other) noexcept;
    name_tree_builder& operator=(name_tree_builder other);

private:
    std::unordered_set<std::string> top_level_modules__;
    dogen::yarn::location model_location__;
    std::list<std::string> names_;
    std::shared_ptr<dogen::yarn::helpers::node> root_;
    std::shared_ptr<dogen::yarn::helpers::node> current_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::helpers::name_tree_builder& lhs,
    dogen::yarn::helpers::name_tree_builder& rhs) {
    lhs.swap(rhs);
}

}

#endif
