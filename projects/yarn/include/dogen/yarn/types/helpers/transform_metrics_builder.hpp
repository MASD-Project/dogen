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

#include <stack>
#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/helpers/transform_metrics_fwd.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class transform_metrics_builder final {
public:
    transform_metrics_builder(const std::string& log_level,
        const bool writing_probe_data);

private:
    void ensure_stack_not_empty() const;
    boost::shared_ptr<transform_metrics>
    create_metrics(const std::string& transform_id,
        const std::string& model_id) const;
    void update_end();

public:
    void start(const std::string& transform_id, const std::string& model_id);
    void end();

public:
    const boost::shared_ptr<const transform_metrics> current() const;

public:
    boost::shared_ptr<transform_metrics> build();

private:
    std::stack<boost::shared_ptr<transform_metrics>> stack_;
};

} } }


#endif
