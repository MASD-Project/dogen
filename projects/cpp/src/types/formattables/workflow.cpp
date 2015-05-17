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
#include <memory>
#include <forward_list>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/memory_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository_factory.hpp"
#include "dogen/cpp/types/formattables/workflow.hpp"

namespace {

const std::string id("cpp.formattables.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates the formattables.
 */
class generator {
public:
    explicit generator(const transformer& t) : transformer_(t) { }

private:
    void add(std::forward_list<std::shared_ptr<formattables::formattable> > f) {
        result_.splice_after(result_.before_begin(), f);
    }

    template<typename Generatable>
    bool ignore(const Generatable& g) const {
        return
            g.generation_type() == sml::generation_types::no_generation ||
            g.generation_type() == sml::generation_types::partial_generation;
    }

    template<typename Transformable>
    void transform(const Transformable& t) {
        if (!ignore(t))
            add(transformer_.transform(t));
    }

public:
    void operator()(const dogen::sml::object& o) { transform(o); }
    void operator()(const dogen::sml::enumeration& e) { transform(e); }
    void operator()(const dogen::sml::primitive& p) { transform(p); }
    void operator()(const dogen::sml::module& m) { transform(m); }
    void operator()(const dogen::sml::concept& c) { transform(c); }

public:
    const std::forward_list<std::shared_ptr<formattables::formattable> >&
    result() { return result_; }

private:
    std::forward_list<std::shared_ptr<formattables::formattable> > result_;
    const transformer& transformer_;
};

}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::execute(const config::cpp_options& opts,
    const dynamic::repository& srp,
    const dynamic::object& root_object,
    const formatters::container& fc,
    const settings::bundle_repository& brp,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started creating formattables.";

    formatter_properties_repository_factory f;
    const auto fprp(f.make(opts, srp, root_object, fc, m));

    const transformer t(brp, fprp, m);
    generator g(t);
    all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished creating formattables.";
    const auto r(g.result());
    BOOST_LOG_SEV(lg, debug) << "Formattables: " << r;
    return r;
}

} } }
