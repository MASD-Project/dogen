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
#ifndef DOGEN_YARN_TYPES_HELPERS_TRANSFORM_METRICS_HPP
#define DOGEN_YARN_TYPES_HELPERS_TRANSFORM_METRICS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/helpers/transform_metrics_fwd.hpp"
#include "dogen/yarn/serialization/helpers/transform_metrics_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class transform_metrics final {
public:
    transform_metrics(const transform_metrics&) = default;
    transform_metrics(transform_metrics&&) = default;
    ~transform_metrics() = default;

public:
    transform_metrics();

public:
    transform_metrics(
        const std::string& id,
        const std::string& guid,
        const unsigned long start,
        const unsigned long end,
        const std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> >& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::helpers::transform_metrics& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::helpers::transform_metrics& v, unsigned int version);

public:
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);

    const std::string& guid() const;
    std::string& guid();
    void guid(const std::string& v);
    void guid(const std::string&& v);

    unsigned long start() const;
    void start(const unsigned long v);

    unsigned long end() const;
    void end(const unsigned long v);

    const std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> >& children() const;
    std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> >& children();
    void children(const std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> >& v);
    void children(const std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> >&& v);

public:
    bool operator==(const transform_metrics& rhs) const;
    bool operator!=(const transform_metrics& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(transform_metrics& other) noexcept;
    transform_metrics& operator=(transform_metrics other);

private:
    std::string id_;
    std::string guid_;
    unsigned long start_;
    unsigned long end_;
    std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> > children_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::helpers::transform_metrics& lhs,
    dogen::yarn::helpers::transform_metrics& rhs) {
    lhs.swap(rhs);
}

}

#endif
