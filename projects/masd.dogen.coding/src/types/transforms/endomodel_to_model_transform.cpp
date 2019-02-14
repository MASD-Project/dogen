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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/endomodel_to_model_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.endomodel_to_model_transform");
using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_qualified_name("Duplicate qualified name: ");
const std::string expected_one_output_language(
    "Expected exactly one output language.");

}

namespace masd::dogen::coding::transforms {

namespace {

class model_populator {
public:
    explicit model_populator(meta_model::model& m) : result_(m) { }

private:
    void ensure_not_yet_processed(const std::string& id) {
        const auto i(processed_ids_.find(id));
        if (i != processed_ids_.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_qualified_name + id));
        }
    }

    void add(boost::shared_ptr<meta_model::element> e) {
        /*
         * Element extensions share the same id as the original
         * element, so they are not considered duplicates. All other
         * elements must have unique element ids.
         */
        if (!e->is_element_extension()) {
            const auto id(e->name().id());
            ensure_not_yet_processed(id);
            processed_ids_.insert(id);
        }
        result_.elements().push_back(e);
    }

public:
    void operator()(boost::shared_ptr<meta_model::element>) { }
    void operator()(boost::shared_ptr<meta_model::module> m) {
        result_.module_ids().insert(m->name().id());
        add(m);
    }
    void operator()(boost::shared_ptr<meta_model::object_template> ot) {
        add(ot);
    }
    void operator()(boost::shared_ptr<meta_model::builtin> b) { add(b); }
    void operator()(boost::shared_ptr<meta_model::enumeration> e) { add(e); }
    void operator()(boost::shared_ptr<meta_model::primitive> p) { add(p); }
    void operator()(boost::shared_ptr<meta_model::object> o) { add(o); }
    void operator()(boost::shared_ptr<meta_model::exception> e) { add(e); }
    void operator()(boost::shared_ptr<meta_model::visitor> v) { add(v); }

public:
    void add(const std::list<boost::shared_ptr<meta_model::element>>& ie) {
        for (const auto& e : ie)
            add(e);
    }

public:
    const meta_model::model& result() const { return result_; }

private:
    meta_model::model& result_;
    std::unordered_set<std::string> processed_ids_;
};

}

std::size_t endomodel_to_model_transform::
compute_total_size(const meta_model::endomodel& em) {
    std::size_t r;
    r = em.modules().size();
    r += em.object_templates().size();
    r += em.builtins().size();
    r += em.enumerations().size();
    r += em.primitives().size();
    r += em.objects().size();
    r += em.exceptions().size();
    r += em.visitors().size();
    return r;
}

meta_model::model
endomodel_to_model_transform::transform(const meta_model::endomodel& em) {
    meta_model::model r;
    r.name(em.name());
    r.meta_name(helpers::meta_name_factory::make_model_name());

    r.input_language(em.input_language());
    if (em.output_languages().size() != 1) {
        BOOST_LOG_SEV(lg, error) << expected_one_output_language
                                 << " Output languages: "
                                 << em.output_languages();
        BOOST_THROW_EXCEPTION(
            transformation_error(expected_one_output_language));
    }
    const auto ol(em.output_languages().front());
    r.output_language(ol);

    r.leaves(em.leaves());
    r.references(em.references());
    r.root_module(em.root_module());
    r.orm_properties(em.orm_properties());
    r.extraction_properties(em.extraction_properties());

    const auto size(compute_total_size(em));
    r.elements().reserve(size);

    model_populator mp(r);
    meta_model::shared_elements_traversal(em, mp);

    return r;
}

std::list<meta_model::model> endomodel_to_model_transform::
transform(const context& ctx, const std::list<meta_model::endomodel>& ems) {
    tracing::scoped_transform_tracer stp(lg, "endomodel to model transform",
        transform_id, ctx.tracer(), ems);

    std::list<meta_model::model> r;
    for(const auto& em : ems)
        r.push_back(transform(em));

    stp.end_transform(r);
    return r;
}

}
