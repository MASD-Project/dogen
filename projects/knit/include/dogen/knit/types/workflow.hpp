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
#ifndef DOGEN_KNIT_TYPES_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <list>
#include <vector>
#include <string>
#include <ostream>
#include <functional>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/yarn/types/transforms/options.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/artefact_writer_interface.hpp"

namespace dogen {
namespace knit {

class workflow {
public:
    workflow() = delete;
    workflow& operator=(const workflow&) = default;
    workflow(const workflow&) = default;

public:
    typedef std::function<std::ostream& ()> output_fn;

public:
    workflow(workflow&& rhs);
    explicit workflow(const yarn::transforms::options& o);

public:
    /**
     * @brief Perform the entire code generation workflow.
     */
    void execute() const;

private:
    const yarn::transforms::options options_;
};

} }

#endif
