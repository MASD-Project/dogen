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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const dogen::annotations::type_repository& type_repository,
        const dogen::options::knitting_options& options);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    std::vector<boost::filesystem::path>& data_directories();
    void data_directories(const std::vector<boost::filesystem::path>& v);
    void data_directories(const std::vector<boost::filesystem::path>&& v);

    const dogen::annotations::type_repository& type_repository() const;
    dogen::annotations::type_repository& type_repository();
    void type_repository(const dogen::annotations::type_repository& v);
    void type_repository(const dogen::annotations::type_repository&& v);

    const dogen::options::knitting_options& options() const;
    dogen::options::knitting_options& options();
    void options(const dogen::options::knitting_options& v);
    void options(const dogen::options::knitting_options&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    std::vector<boost::filesystem::path> data_directories_;
    dogen::annotations::type_repository type_repository_;
    dogen::options::knitting_options options_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::transforms::context& lhs,
    dogen::yarn::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
