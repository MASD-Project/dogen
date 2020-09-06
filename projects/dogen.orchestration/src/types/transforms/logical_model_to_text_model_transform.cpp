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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/types/helpers/physical_id_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/io/entities/output_model_set_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/logical_model_to_text_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.logical_model_to_text_model_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_id("Duplicate ID for element: ");
const std::string duplicate_physical_name("Duplicate physical name: ");
const std::string expected_one_output_technical_space(
    "Expected exactly one output technical space.");
const std::string expected_archetypes("Expected archetypes for: ");
const std::string unexpected_archetypes("Unexpected archetypes for: ");

}

namespace dogen::orchestration::transforms {

using identification::entities::logical_id;
using identification::helpers::logical_meta_name_factory;

namespace {

/**
 * @brief Populates a text model with entities from a logical model.
 */
class populator {
public:
    populator(const physical::entities::meta_model& pmm,
        text::entities::model& m) : physical_meta_model_(pmm), result_(m) { }

private:
    /**
     * @brief If this ID was seen already, throws.
     */
    void ensure_not_yet_processed(const logical_id& id) const;

    /**
     * @brief Creates a logical provenance for an artefact.
     */
    identification::entities::logical_provenance
    make_logical_provenance(const logical::entities::element& e) const;

    /**
     * @brief Adds an element to the model, performing an expansion
     * across physical space.
     */
    void add(boost::shared_ptr<logical::entities::element> e);

public:
    void operator()(boost::shared_ptr<logical::entities::element> e) { add(e); }

public:
    const text::entities::model& result() const { return result_; }

private:
    const physical::entities::meta_model& physical_meta_model_;
    text::entities::model& result_;
    std::unordered_set<logical_id> processed_ids_;
};

void populator::ensure_not_yet_processed(const logical_id& id) const {
    const auto i(processed_ids_.find(id));
    if (i != processed_ids_.end()) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(
            transform_exception(duplicate_id + id.value()));
    }
}

identification::entities::logical_provenance
populator::make_logical_provenance(const logical::entities::element& e) const {
    identification::entities::logical_provenance r;
    r.injection(e.provenance());

    using identification::entities::logical_meta_id;
    logical_meta_id mid(e.meta_name().id());
    r.logical_meta_name().id(mid);
    r.logical_meta_name().simple(e.meta_name().simple());

    const auto& n(e.name());
    r.logical_name().simple(n.simple());

    using identification::entities::logical_id;
    r.logical_name().id(logical_id(n.qualified().dot()));

    auto& qn(r.logical_name().qualified());
    qn.dot(n.qualified().dot());
    qn.colon(n.qualified().colon());
    qn.identifiable(n.qualified().identifiable());

    auto& l(r.logical_name().location());
    l.external_modules(n.location().external_modules());
    l.model_modules(n.location().model_modules());
    l.internal_modules(n.location().internal_modules());

    return r;
}

void populator::add(boost::shared_ptr<logical::entities::element> e) {
    /*
     * Element IDs are expected to be processed exactly only once.
     */
    const auto id(e->name().id());
    BOOST_LOG_SEV(lg, debug) << "Adding element: " << id;
    ensure_not_yet_processed(id);
    processed_ids_.insert(id);

    /*
     * The logical part of the element is very straightforward, just
     * add it to the element_artefacts structure.
     */
    text::entities::element_artefacts ea;
    ea.element(e);

    /*
     * Create the artefact set, which represents the region in
     * physical space for this logical position. We start by
     * populating the set's logical properties. These just link it
     * back to its origin.
     */
    auto& as(ea.artefacts());
    const auto mid(e->meta_name().id());
    as.provenance(make_logical_provenance(*e));
    as.configuration(e->configuration());

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
    as.is_generatable(e->generability_status() == gs);

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
                transform_exception(expected_archetypes + mid.value()));
        }

        /*
         * We found no archetypes as expected, so populate our empty
         * manifold.
         */
        result_.elements().push_back(ea);
        return;
    }

    /*
     * If we do have physical projects, these must have been expected
     * by the logical model.
     */
    if (e->generability_status() == gne) {
        BOOST_LOG_SEV(lg, error) << unexpected_archetypes << mid;
        BOOST_THROW_EXCEPTION(
            transform_exception(unexpected_archetypes + mid.value()));
    }

    /*
     * The element does have a physical representation. We need to
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
    auto& aba(as.artefacts_by_archetype());
    for (const auto& pmn : physical_meta_names) {
        BOOST_LOG_SEV(lg, debug) << "Processing: " << pmn.id();

        /*
         * Populate the provenance properties for both the logical and
         * physical dimensions of the artefact.
         */
        auto a(boost::make_shared<physical::entities::artefact>());
        a->name().simple(e->name().simple());
        a->meta_name(pmn);

        identification::helpers::physical_id_factory f;
        using namespace identification::entities;
        const logical_id id(e->name().qualified().dot());
        a->name().id(f.make(id, pmn.id()));
        a->provenance(as.provenance());

        /*
         * Add the archetype to the plane. For any position in logical
         * space, there can only be one corresponding position in
         * physical space as represented by the physical
         * meta-element. We only expect one instance of a physical
         * meta-name.
         */
        const auto pair(std::make_pair(pmn.id(), a));
        const auto inserted(aba.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_physical_name << pmn.id();
            BOOST_THROW_EXCEPTION(transform_exception(
                    duplicate_physical_name + pmn .id().value()));
        }
        BOOST_LOG_SEV(lg, debug) << "Added artefact. Physical name: " << pmn;
    }
    result_.elements().push_back(ea);
}

}

text::entities::model logical_model_to_text_model_transform::
apply(const text::transforms::context& ctx, const logical::entities::model& m) {
    text::entities::model r;
    r.name(m.name());
    r.meta_name(logical_meta_name_factory::make_model_name());

    r.input_technical_space(m.input_technical_space());
    if (m.output_technical_spaces().size() != 1) {
        BOOST_LOG_SEV(lg, error) << expected_one_output_technical_space
                                 << " Output technical spaces: "
                                 << m.output_technical_spaces();
        BOOST_THROW_EXCEPTION(
            transform_exception(expected_one_output_technical_space));
    }
    const auto ts(m.output_technical_spaces().front());
    r.output_technical_space(ts);

    r.leaves(m.leaves());
    r.references(m.references());
    r.root_module(m.root_module());
    r.orm_properties(m.orm_properties());
    r.provenance(m.provenance());
    r.all_technical_spaces(m.all_technical_spaces());

    populator p(*ctx.physical_meta_model(), r);
    logical::entities::shared_elements_traversal(m, p);

    return r;
}

text::entities::model_set logical_model_to_text_model_transform::
apply(const text::transforms::context& ctx,
    const logical::entities::output_model_set& loms) {
    tracing::scoped_transform_tracer stp(lg,
        "logical model to text model transform",
        transform_id, loms.name().qualified().dot(), *ctx.tracer(), loms);

    text::entities::model_set r;
    for(const auto& lm : loms.models())
        r.models().push_back(apply(ctx, lm));

    stp.end_transform(r);
    return r;
}

}
