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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <forward_list>
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates a list of formattables from a given container of
 * SML elements.
 */
class workflow {
public:
    explicit workflow(const settings::workflow& w);

public:
    /**
     * @brief Executes the workflow.
     */
    std::forward_list<std::shared_ptr<formattables::formattable> >
    execute(const sml::model& m) const;

private:
    const settings::workflow& settings_workflow_;

};

} } }

#endif
