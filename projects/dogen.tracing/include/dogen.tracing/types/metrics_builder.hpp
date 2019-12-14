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
#ifndef DOGEN_TRACING_TYPES_METRICS_BUILDER_HPP
#define DOGEN_TRACING_TYPES_METRICS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <stack>
#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/metrics_fwd.hpp"

namespace dogen::tracing {

class metrics_builder final {
public:
    metrics_builder(const std::string& version, const std::string& run_id,
        const std::string& logging_impact, const std::string& tracing_impact);

private:
    void ensure_stack_not_empty() const;
    boost::shared_ptr<metrics> create_metrics(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const;
    void update_end();

public:
    void start(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id);
    void end();

public:
    const boost::shared_ptr<const metrics> current() const;

public:
    boost::shared_ptr<metrics> build();

private:
    std::stack<boost::shared_ptr<metrics>> stack_;
};

}

#endif
