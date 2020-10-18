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
#include <unordered_set>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/types/helpers/physical_id_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.orchestration/types/helpers/projection_error.hpp"
#include "dogen.orchestration/types/helpers/logical_to_physical_projector.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.logical_model_to_text_model_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_id("Duplicate ID for element: ");
const std::string duplicate_physical_name("Duplicate physical name: ");
const std::string expected_archetypes("Expected archetypes for: ");
const std::string unexpected_archetypes("Unexpected archetypes for: ");

}

namespace dogen::orchestration::helpers {

using identification::entities::logical_id;

namespace {

/**
 * @brief Projects logical entities to physical space.
 */
class projector {
public:
    projector(const physical::entities::meta_model& pmm)
        : physical_meta_model_(pmm) { }

private:
    /**
     * @brief If this logical ID was seen already, throw.
     */
    void ensure_not_yet_processed(const logical_id& id) const;

    /**
     * @brief Creates a logical provenance for an artefact.
     */
    identification::entities::logical_provenance
    make_logical_provenance(const logical::entities::element& e) const;

    /**
     * @brief Creates a physical region for the supplied logical
     * element, expanding it over that space.
     */
    void add(boost::shared_ptr<logical::entities::element> e);

public:
    void operator()(boost::shared_ptr<logical::entities::element> e) { add(e); }

public:
    /**
     * @brief Returns the result of the projection.
     */
    const std::list<text::entities::logical_physical_region>&
    result() const { return result_; }

private:
    const physical::entities::meta_model& physical_meta_model_;
    std::list<text::entities::logical_physical_region> result_;
    std::unordered_set<logical_id> processed_ids_;
};

void projector::ensure_not_yet_processed(const logical_id& id) const {
    const auto i(processed_ids_.find(id));
    if (i != processed_ids_.end()) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(projection_error(duplicate_id + id.value()));
    }
}

identification::entities::logical_provenance projector::
make_logical_provenance(const logical::entities::element& e) const {
    identification::entities::logical_provenance r;
    r.codec(e.provenance());
    r.logical_meta_name(e.meta_name());
    r.logical_name(e.name());
    return r;
}

void projector::add(boost::shared_ptr<logical::entities::element> e) {
    /*
     * Logical elements are expected to be processed exactly only
     * once.
     */
    const auto id(e->name().id());
    BOOST_LOG_SEV(lg, debug) << "Adding element: " << id;
    ensure_not_yet_processed(id);
    processed_ids_.insert(id);

    /*
     * The logical part of the element is very straightforward, just
     * add it to the region.
     */
    text::entities::logical_physical_region region;
    region.logical_element(e);

    /*
     * Create the artefact set, which represents the region in
     * physical space for this logical point. We start by populating
     * the set's logical properties. These just link it back to its
     * origin.
     */
    auto& pr(region.physical_region());
    const auto mid(e->meta_name().id());
    pr.provenance(make_logical_provenance(*e));
    pr.configuration(e->configuration());

    /*
     * We mainly care about sets that have the potential to be
     * generatable, though we keep all of them - even the
     * non-generatable ones. Note that this is only a hint from a
     * logical perspective though, and does not imply that there will
     * _actually_ be any generation; that is dependent on the physical
     * configuration and enablement.
     */
    using logical::entities::generability_status;
    const auto gs(generability_status::generatable);
    const auto gne(generability_status::generation_not_expected);
    pr.is_generatable(e->generability_status() == gs);

    /*
     * Obtain all of the archetypes associated with this element's
     * meta-type, if any. If there are none this just means this
     * element's logical meta-type is not expected to project into the
     * physical dimension. If so, the generability status should also
     * reflect this expectation.
     */
    const auto& pmm(physical_meta_model_);
    const auto& in(pmm.indexed_names());
    const auto& lmn(in.archetype_names_by_logical_meta_name());
    const auto i(lmn.find(mid));
    if (i == lmn.end()) {
        BOOST_LOG_SEV(lg, debug) << "No physical meta-names found for: " << mid;

        /*
         * The logical meta-model element hinted we should not expect
         * a physical representation. If the hints do not match our
         * findings, we must complain - it indicates some logic error.
         */
        if (e->generability_status() != gne) {
            BOOST_LOG_SEV(lg, error) << expected_archetypes << mid;
            BOOST_THROW_EXCEPTION(
                projection_error(expected_archetypes + mid.value()));
        }

        /*
         * We found no archetypes as expected, so populate our empty
         * region.
         */
        result_.push_back(region);
        return;
    }

    /*
     * If we do have physical projections, these must have been
     * expected by the logical model.
     */
    if (e->generability_status() == gne) {
        BOOST_LOG_SEV(lg, error) << unexpected_archetypes << mid;
        BOOST_THROW_EXCEPTION(
            projection_error(unexpected_archetypes + mid.value()));
    }

    /*
     * Since the element has a physical representation, we now need to
     * update the artefact set with it.
     */
    const auto& physical_meta_names(i->second.meta_names());
    BOOST_LOG_SEV(lg, debug) << "Element has physical meta-names: "
                             << physical_meta_names.size();

    /*
     * For each physical meta-name representing an archetype, create
     * an entry with the associated artefact. The artefact is an
     * instance of the archetype.
     */
    auto& aba(pr.artefacts_by_archetype());
    for (const auto& pmn : physical_meta_names) {
        BOOST_LOG_SEV(lg, debug) << "Processing: " << pmn.id();

        /*
         * Populate the provenance properties for both the logical and
         * physical dimensions of the artefact.
         */
        auto a(boost::make_shared<physical::entities::artefact>());
        a->name().simple(e->name().simple());
        a->meta_name(pmn);
        a->configuration(pr.configuration());

        identification::helpers::physical_id_factory f;
        using namespace identification::entities;
        const logical_id id(e->name().id());
        a->name().id(f.make(id, pmn.id()));
        a->provenance(pr.provenance());

        /*
         * Add the archetype to the region. For any position in
         * logical space, there can only be one corresponding position
         * in physical space as represented by the physical
         * meta-element; i.e., we only expect one instance of a
         * physical meta-name.
         */
        const auto pair(std::make_pair(pmn.id(), a));
        const auto inserted(aba.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_physical_name << pmn.id();
            BOOST_THROW_EXCEPTION(projection_error(
                    duplicate_physical_name + pmn .id().value()));
        }
        BOOST_LOG_SEV(lg, debug) << "Added artefact. Physical name: " << pmn;
    }
    result_.push_back(region);
}

}

std::list<text::entities::logical_physical_region>
logical_to_physical_projector::
project(const physical::entities::meta_model& pmm,
    const logical::entities::model& lm) {
    projector p(pmm);
    logical::entities::shared_elements_traversal(lm, p);
    return p.result();
}

}
