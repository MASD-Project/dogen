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
#ifndef DOGEN_SML_TYPES_CONSUMPTION_WORKFLOW_HPP
#define DOGEN_SML_TYPES_CONSUMPTION_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <list>
#include <memory>
#include <unordered_map>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/grapher.hpp"
#include "dogen/sml/types/consumer_interface.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Performs the consumption workflow on a given model by a
 * given set of consumers.
 *
 * The purpose of the consumption workflow is to consume each model
 * element in order of dependency. There are two relationships we care
 * about:
 *
 * @li module containment;
 * @li parenting.
 *
 * The consumers will consume elements such that any element is only
 * consumed after all elements it depends on have already been
 * consumed.
 */
class consumption_workflow {
public:
    consumption_workflow() = default;
    consumption_workflow(const consumption_workflow&) = default;
    ~consumption_workflow() = default;
    consumption_workflow(consumption_workflow&&) = default;
    consumption_workflow& operator=(const consumption_workflow&) = default;

public:
    typedef std::list<std::shared_ptr<consumer_interface>> consumer_list_type;
    typedef std::map<unsigned int, consumer_list_type> consumers_by_pass_type;

private:
    /**
     * @brief Setup the DAG of model elements.
     */
    graph_type build_graph_activity(const model& m) const;

    /**
     * @brief Orders the supplied consumers by pass.
     *
     * Uses the special value of max unsigned int for consumers that
     * must be executed last.
     */
    consumers_by_pass_type
    obtain_consumers_by_pass_activity(
        const consumer_list_type& consumers) const;

    /**
     * @brief Consume all model elements.
     */
    void consume_elements_activity(const model& model,
        const consumers_by_pass_type& consumers_by_pass,
        const graph_type& graph) const;

public:
    /**
     * @brief Get all supplied consumers to consume the supplied model.
     */
    void execute(const model& m, const consumer_list_type& consumers);
};

} }

#endif
