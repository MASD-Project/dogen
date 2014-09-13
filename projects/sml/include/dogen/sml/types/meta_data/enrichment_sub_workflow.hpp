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
#ifndef DOGEN_SML_TYPES_META_DATA_ENRICHMENT_SUB_WORKFLOW_HPP
#define DOGEN_SML_TYPES_META_DATA_ENRICHMENT_SUB_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/meta_data/enrichment_types.hpp"
#include "dogen/sml/types/meta_data/enricher_grapher.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

/**
 * @brief Responsible for enriching a supplied entity with all the
 * available enrichers.
 */
class enrichment_sub_workflow {
public:
    /**
     * @param m model that the qnames belong to.
     * @param g graph of enrichers previously setup.
     */
    enrichment_sub_workflow(model& m, enricher_graph& g);

private:
    class context {
    public:
        context(const qname& qname, const enrichment_types enrichment_type);

    public:
        sml::qname qname() const;
        enrichment_types enrichment_type() const;

    private:
        sml::qname qname_;
        enrichment_types enrichment_type_;
    };

private:
    /**
     * @brief Tries to apply the enrichment to the qname.
     *
     * @return true if application was done, false otherwise.
     */
    template<typename T>
    bool apply_enrichment(const qname& qn,
        const enrichment_types enrichment_type,
        std::unordered_map<qname, T> map,
        enricher_interface& e) {
        auto i(map.find(qn));
        if (i == map.end())
            return false;

        e.enrich(model_, enrichment_type, i->second);
        return true;
    }

private:
    /**
     * @brief Applies the supplied enricher to the entity.
     *
     * @pre current_qname_ must be set.
     */
    void apply_enricher_activity(std::shared_ptr<enricher_interface> e);

public:
    /**
     * @brief Executes the enrichment sub-workflow on the supplied
     * qname.
     *
     * @pre qn must exist in the supplied model.
     */
    void execute(const qname& qn, const enrichment_types enrichment_type);

private:
    model& model_;
    enricher_graph& graph_;
    std::shared_ptr<context> context_;
};

} } }

#endif
