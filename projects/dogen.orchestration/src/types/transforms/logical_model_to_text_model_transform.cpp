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
#include "dogen.logical/io/entities/output_model_set_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
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

}

namespace dogen::orchestration::transforms {

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
    void ensure_not_yet_processed(const std::string& id) const {
        const auto i(processed_ids_.find(id));
        if (i != processed_ids_.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_id << id;
            BOOST_THROW_EXCEPTION(transform_exception(duplicate_id + id));
        }
    }

    /**
     * @brief Adds an element to the model, performing an expansion
     * across physical space.
     */
    void add(boost::shared_ptr<logical::entities::element> e) {
        /*
         * Element IDs are expected to be processed exactly only once.
         */
        const auto id(e->name().qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Adding element: " << id;
        ensure_not_yet_processed(id);
        processed_ids_.insert(id);

        /*
         * The logical part of the element is very straightforward,
         * just add it to the element_artefacts structure.
         */
        text::entities::element_artefacts ea;
        ea.element(e);

        /*
         * Obtain all of the archetypes associated with this element's
         * meta-type, if any. If there are none this just means this
         * element has a meta-type which is cannot be transformed into
         * text.
         */
        const auto& pmm(physical_meta_model_);
        const auto& nrp(pmm.kernels().cbegin()->second.indexed_names());
        const auto& lmn(nrp.by_logical_meta_name());
        const auto mn(e->meta_name().qualified().dot());
        const auto i(lmn.find(mn));
        if (i != lmn.end()) {
            const auto& physical_meta_names(i->second.meta_names());
            BOOST_LOG_SEV(lg, debug) << "Element has physical meta-names: "
                                     << physical_meta_names.size();

            /*
             * Now, for each physical meta-name, create an entry with the
             * associated artefact. We only expect one instance of a
             * physical meta-name.
             */
            auto& arts(ea.artefacts());
            for (const auto& pmn : physical_meta_names) {
                const auto pqn(pmn.qualified());
                BOOST_LOG_SEV(lg, debug) << "Processing: " << pqn;

                auto art(boost::make_shared<physical::entities::artefact>());
                const auto pair(std::make_pair(pqn, art));
                const auto inserted(arts.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_physical_name << pqn;
                    BOOST_THROW_EXCEPTION(
                        transform_exception(duplicate_physical_name + pqn));
                }
                BOOST_LOG_SEV(lg, debug) << "Added artefact. Physical name: "
                                         << pqn;
            }
        } else {
            BOOST_LOG_SEV(lg, debug) << "No physical names for meta-name: "
                                     << mn;
        }
        result_.elements().push_back(ea);
    }

public:
    void operator()(boost::shared_ptr<logical::entities::element> e) {
        add(e);
    }

    void operator()
    (boost::shared_ptr<logical::entities::structural::module> m) {
        result_.module_ids().insert(m->name().qualified().dot());
        add(m);
    }

public:
    const text::entities::model& result() const { return result_; }

private:
    const physical::entities::meta_model& physical_meta_model_;
    text::entities::model& result_;
    std::unordered_set<std::string> processed_ids_;
};

}

text::entities::model
logical_model_to_text_model_transform::apply(const text::transforms::context& ctx,
    const logical::entities::model& m) {
    text::entities::model r;
    r.name(m.name());
    r.meta_name(logical::helpers::meta_name_factory::make_model_name());

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
    r.extraction_properties(m.extraction_properties());
    r.origin_sha1_hash(m.origin_sha1_hash());
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
