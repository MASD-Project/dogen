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
#ifndef DOGEN_YARN_TYPES_HELPERS_TRANSFORM_METRICS_BUILDER_HPP
#define DOGEN_YARN_TYPES_HELPERS_TRANSFORM_METRICS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/helpers/transform_metrics_fwd.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class transform_metrics_builder final {
public:
    transform_metrics_builder() = default;
    transform_metrics_builder(const transform_metrics_builder&) = default;
    transform_metrics_builder(transform_metrics_builder&&) = default;
    ~transform_metrics_builder() = default;

public:
    transform_metrics_builder(
        const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& root,
        const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& current_);

public:
    const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& root() const;
    boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& root();
    void root(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& v);
    void root(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>&& v);

    const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& current_() const;
    boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& current_();
    void current_(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& v);
    void current_(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>&& v);

public:
    bool operator==(const transform_metrics_builder& rhs) const;
    bool operator!=(const transform_metrics_builder& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_metrics_builder& other) noexcept;
    transform_metrics_builder& operator=(transform_metrics_builder other);

private:
    boost::shared_ptr<dogen::yarn::helpers::transform_metrics> root_;
    boost::shared_ptr<dogen::yarn::helpers::transform_metrics> current__;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::helpers::transform_metrics_builder& lhs,
    dogen::yarn::helpers::transform_metrics_builder& rhs) {
    lhs.swap(rhs);
}

}

#endif
