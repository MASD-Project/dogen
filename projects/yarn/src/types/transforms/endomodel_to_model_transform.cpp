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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/endomodel_to_model_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.endomodel_to_model_transform"));

const std::string duplicate_qualified_name("Duplicate qualified name: ");
const std::string expected_one_output_language(
    "Expected exactly one output language.");

}

namespace dogen {
namespace yarn {
namespace transforms {

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
    void operator()(boost::shared_ptr<meta_model::concept> c) { add(c); }
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
compute_total_size(const meta_model::endomodel& im) {
    std::size_t r;
    r = im.modules().size();
    r += im.concepts().size();
    r += im.builtins().size();
    r += im.enumerations().size();
    r += im.primitives().size();
    r += im.objects().size();
    r += im.exceptions().size();
    r += im.visitors().size();
    r += im.injected_elements().size();
    return r;
}

meta_model::model
endomodel_to_model_transform::transform(const meta_model::endomodel& im) {
    meta_model::model r;
    r.name(im.name());
    r.meta_name(helpers::meta_name_factory::make_model_name());

    r.input_language(im.input_language());
    if (im.output_languages().size() != 1) {
        BOOST_LOG_SEV(lg, error) << expected_one_output_language
                                 << " Output languages: "
                                 << im.output_languages();
        BOOST_THROW_EXCEPTION(
            transformation_error(expected_one_output_language));
    }
    const auto ol(im.output_languages().front());
    r.output_language(ol);

    r.root_module(im.root_module());
    r.has_generatable_types(im.has_generatable_types());
    r.orm_properties(im.orm_properties());
    r.facet_properties(im.facet_properties());

    const auto size(compute_total_size(im));
    r.elements().reserve(size);

    model_populator mp(r);
    meta_model::shared_elements_traversal(im, mp);

    // FIXME: not using:
    // shared_elements_traversal(im, mp, true/*include_injected_elements*/);
    // as its causing issues at present.
    mp.add(im.injected_elements());

    return r;
}

std::list<meta_model::model> endomodel_to_model_transform::
transform(const std::list<meta_model::endomodel>& ims) {
    std::list<meta_model::model> r;
    for(const auto& im : ims)
        r.push_back(transform(im));

    return r;
}

} } }
