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
#ifndef DOGEN_DIA_TO_SML_TYPES_WORKFLOW_HPP
#define DOGEN_DIA_TO_SML_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia_to_sml/types/graph_builder.hpp"
#include "dogen/dia_to_sml/types/context_fwd.hpp"
#include "dogen/dia_to_sml/types/workflow_interface.hpp"

namespace dogen {
namespace dia_to_sml {

class workflow : public workflow_interface {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;
    virtual ~workflow() noexcept;

private:
    graph_type build_graph(const dia::diagram& diagram, context& c) const;
    void initialise_context(const std::string& model_name,
        const std::string& external_package_path,
        bool is_target, context& c) const;
    void graph_to_context(const graph_type& g, context& c) const;
    void post_process_model(context& c) const;

public:
    virtual sml::model execute(const dia::diagram& diagram,
        const std::string& model_name,
        const std::string& external_package_path,
        bool is_target) override;
};

} }

#endif
