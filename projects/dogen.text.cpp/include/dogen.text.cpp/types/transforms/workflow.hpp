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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_WORKFLOW_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text/types/entities/element_archetype.hpp"
#include "dogen.text.cpp/types/formattables/locator.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"
#include "dogen.text.cpp/types/transforms/registrar.hpp"
#include "dogen.text.cpp/types/transforms/stitch_transform.hpp"

namespace dogen::text::cpp::transforms {

/**
 * @brief Generates all files for the supplied entity.
 */
class workflow final {
public:
    workflow(const formattables::locator& l,
        const variability::entities::feature_model& fm,
        const variability::helpers::configuration_factory& cf);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::transforms::registrar& registrar();

private:
    const logical::entities::artefact_properties&
    get_artefact_properties(const logical::entities::element& e,
        const std::string& archetype) const;

    boost::shared_ptr<physical::entities::artefact>
    get_artefact(const std::unordered_map<std::string,
        boost::shared_ptr<physical::entities::artefact>>& artefacts,
        const std::string& archetype) const;

private:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        const std::unordered_set<text::entities::element_archetype>&
        enabled_archetype_for_element, const formattables::model& fm,
        formattables::formattable& fbl) const;

public:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        const std::unordered_set<text::entities::element_archetype>&
        enabled_archetype_for_element, formattables::model& fm) const;

private:
    static std::shared_ptr<cpp::transforms::registrar> registrar_;
    const stitch_transform stitch_formatter_;
    const formattables::locator& locator_;
};

}

#endif
