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
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/logical_model_to_m2t_model_transform.hpp"

namespace {

const std::string transform_id(
    "engine.transforms.logical_model_to_m2t_model_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_qualified_name("Duplicate qualified name: ");
const std::string expected_one_output_technical_space(
    "Expected exactly one output technical space.");

}

namespace dogen::orchestration::transforms {

namespace {

class model_populator {
public:
    explicit model_populator(m2t::entities::model& m) : result_(m) { }

private:
    void ensure_not_yet_processed(const std::string& id) {
        const auto i(processed_ids_.find(id));
        if (i != processed_ids_.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
            BOOST_THROW_EXCEPTION(
                transform_exception(duplicate_qualified_name + id));
        }
    }

    void add(boost::shared_ptr<logical::entities::element> e) {
        const auto id(e->name().qualified().dot());
        ensure_not_yet_processed(id);
        processed_ids_.insert(id);

        m2t::entities::logical_physical_pair pair;
        pair.logical_element(e);
        result_.elements().push_back(pair);
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
    void add(
        const std::list<boost::shared_ptr<logical::entities::element>>& ie) {
        for (const auto& e : ie)
            add(e);
    }

public:
    const m2t::entities::model& result() const { return result_; }

private:
    m2t::entities::model& result_;
    std::unordered_set<std::string> processed_ids_;
};

}

m2t::entities::model logical_model_to_m2t_model_transform::
apply(const logical::entities::model& m) {
    m2t::entities::model r;
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

    model_populator mp(r);
    logical::entities::shared_elements_traversal(m, mp);

    return r;
}

std::list<m2t::entities::model>
logical_model_to_m2t_model_transform::
apply(const m2t::transforms::context& ctx,
    const std::list<logical::entities::model>& ms) {
    tracing::scoped_transform_tracer stp(lg,
        "logical model to generation model transform",
        transform_id, *ctx.tracer(), ms);

    std::list<m2t::entities::model> r;
    for(const auto& m : ms)
        r.push_back(apply(m));

    stp.end_transform(r);
    return r;
}

}
