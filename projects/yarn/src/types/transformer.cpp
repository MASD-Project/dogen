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
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/transformation_error.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transformer"));

const std::string duplicate_qualified_name("Duplicate qualified name: ");
const std::string expected_one_output_language(
    "Expected exactly one output language.");


}

namespace dogen {
namespace yarn {

namespace {

class model_populator {
public:
    explicit model_populator(model& m) : result_(m) { }

private:
    void ensure_not_yet_processed(const std::string& id) {
        const auto i(processed_ids_.find(id));
        if (i != processed_ids_.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_qualified_name + id));
        }
    }

    void add_element(boost::shared_ptr<element> e) {
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

    template<typename Element>
    void add(const Element& e) { add_element(boost::make_shared<Element>(e)); }

public:
    void operator()(const yarn::module& m) {
        result_.module_ids().insert(m.name().id());
        add(m);
    }
    void operator()(const yarn::concept& c) { add(c); }
    void operator()(const yarn::builtin& b) { add(b); }
    void operator()(const yarn::enumeration& e) { add(e); }
    void operator()(const yarn::primitive& p) { add(p); }
    void operator()(const yarn::object& o) { add(o); }
    void operator()(const yarn::exception& e) { add(e); }
    void operator()(const yarn::visitor& v) { add(v); }

public:
    void add_injected_elements(
        const std::unordered_map<std::string, boost::shared_ptr<element>>& ie) {
        for (const auto& pair : ie)
            add_element(pair.second);
    }

public:
    const model& result() const { return result_; }

private:
    model& result_;
    std::unordered_set<std::string> processed_ids_;
};

}

std::size_t
transformer::compute_total_size(const intermediate_model& im) const {
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

model transformer::transform(const intermediate_model& im) const {
    model r;
    r.name(im.name());
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

    const auto size(compute_total_size(im));
    r.elements().reserve(size);

    model_populator mp(r);
    yarn::elements_traversal(im, mp);
    mp.add_injected_elements(im.injected_elements());

    return r;
}

} }
