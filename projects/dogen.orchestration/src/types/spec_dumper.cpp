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
#include <map>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "dogen/types/spec_entry.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/entities/text.hpp"
#include "dogen.variability/types/entities/boolean.hpp"
#include "dogen.variability/types/entities/number.hpp"
#include "dogen.variability/types/entities/value_visitor.hpp"
#include "dogen.variability/lexical_cast/entities/value_type_lc.hpp"
#include "dogen.variability/lexical_cast/entities/binding_point_lc.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.codec/types/transforms/model_production_chain.hpp"
#include "dogen.text/types/transforms/model_to_text_chain.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.orchestration/types/spec_dumper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("orchestration.spec_dumper"));

const std::string empty_output_directory;
const std::string dumping_activity("dumpspecs");

using namespace dogen::variability::entities;
class visitor : public value_visitor {
public:
    using value_visitor::visit;
    void visit(const number& v) {
        result_ = boost::lexical_cast<std::string>(v.content());
    }

    void visit(const text& v) {
        result_ = v.content();
    }

    void visit(const boolean& v) {
        result_ = v.content() ? "true" : "false";
    }

public:
    std::string result() { return result_; }

private:
    std::string result_;
};

}

namespace dogen::orchestration {

std::string spec_dumper::preprocess(std::string s) const {
    if (s.empty())
        return "<missing description>.";

    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    return s;
}

std::string spec_dumper::
process_binding_point(const variability::entities::binding_point bp) const {
    std::string r(" Binding point: '");
    r += boost::lexical_cast<std::string>(bp) + "'.";
    boost::replace_all(r, "binding_point::", "");
    return r;
}

std::string spec_dumper::process_value(
    const boost::shared_ptr<variability::entities::value> v) const {
    visitor vis;
    std::string r;
    if (v) {
        v->accept(vis);
        r = " Default value: ";
        if (vis.result().empty())
            r += "''.";
        else
            r += vis.result() + ".";
    }
    return r;
}

std::string spec_dumper::process_value_type(
    const variability::entities::value_type vt) const {
    std::string r(" Value type: '");
    r += boost::lexical_cast<std::string>(vt) + "'.";
    boost::replace_all(r, "value_type::", "masd::variability::");
    return r;
}

spec_category spec_dumper::create_codec_category() const {
    spec_category r;
    r.name("Codec");
    r.description("Read external formats into Dogen.");

    // FIXME: waiting for codec meta-model.
    // using codec::transforms::model_production_chain;
    // auto& rg(model_production_chain::registrar());
    // for (const auto& ext : rg.registered_decoding_extensions()) {
    //     const auto& d(rg.decoding_transform_for_extension(ext));
    //     spec_entry e;
    //     e.name(d.id());

    //     std::ostringstream s;
    //     s << preprocess(d.description())
    //       << " Extension: '" << d.extension() << "'";
    //     e.description(s.str());
    //     r.entries().push_back(e);
    // }
    return r;
}

spec_category spec_dumper::create_conversion_category() const {
    spec_category r;
    r.name("Conversion");
    r.description("Output to an external format from a Dogen model.");

    // FIXME: waiting for codec meta-model.
    // using codec::transforms::model_production_chain;
    // auto& rg(model_production_chain::registrar());
    // for (const auto& ext : rg.registered_encoding_extensions()) {
    //     const auto& d(rg.encoding_transform_for_extension(ext));
    //     spec_entry e;
    //     e.name(d.id());

    //     std::ostringstream s;
    //     s << preprocess(d.description())
    //       << " Extension: '" << d.extension() << "'";
    //     e.description(s.str());
    //     r.entries().push_back(e);
    // }

    return r;
}

spec_category spec_dumper::
create_generation_category(const physical::entities::meta_model& pmm) const {
    spec_category r;
    r.name("Generators");
    r.description("Available backends for code generation.");

    for (const auto& be : pmm.backends()) {
        spec_entry e;
        e.name(be.meta_name().id().value());
        e.description(be.description());
        r.entries().push_back(e);
    }
    return r;
}

spec_category spec_dumper::
create_features_category(const variability::entities::feature_model& fm) const {
    spec_category r;
    r.name("Features");
    r.description("Available features for configuration.");
    std::map<std::string, std::string> map;
    for (const auto& f : fm.all()) {
        const auto qn(f.name().qualified());

        std::ostringstream s;
        s << preprocess(f.description())
          << process_binding_point(f.binding_point())
          << process_value(f.default_value())
          << process_value_type(f.value_type());
        map.insert(std::make_pair(qn, s.str()));
    }

    for (const auto& pair : map) {
        spec_entry e;
        e.name(pair.first);
        e.description(pair.second);
        r.entries().push_back(e);
    }
    return r;
}

spec_category spec_dumper::create_variability_domains_category(
    const std::unordered_map<std::string, std::vector<std::string>>& ds) const {
    spec_category r;
    r.name("Template Instantiation Domains");
    r.description("Available domains for template instantiation.");

    for (const auto& pair : ds) {
        spec_entry e;
        e.name(pair.first);

        std::ostringstream s;
        s << "Values in domain: ";
        bool first(true);
        for (const auto& v : pair.second) {
            if (!first)
                s << ", ";
            s << v;
            first = false;
        }
        e.description(s.str());
        r.entries().push_back(e);
    }
    return r;
}

specs spec_dumper::dump(const configuration& cfg) const {
    BOOST_LOG_SEV(lg, debug) << "Started dumping specs.";

    {
        /*
         * Generate the specs for codec, conversion and
         * generation.
         */
        specs r;
        r.categories().push_back(create_codec_category());
        r.categories().push_back(create_conversion_category());

        /*
         * Bootstrap the top-level context. We need a full context
         * because we require some models that are created in the
         * bootstrapping process.
         */
        using cbc = transforms::context_bootstrapping_chain;
        const auto& a(dumping_activity);
        const auto& od(empty_output_directory);
        const auto ctx(cbc::bootstrap_full_context(cfg, a, od));

        /*
         * Bind the tracer to the current scope.
         */
        const auto& t(*ctx.codec_context().tracer());
        tracing::scoped_tracer st(t);

        /*
         * Convert all features in the feature model to categories.
         */
        const auto& fm(*ctx.logical_context().feature_model());
        r.categories().push_back(create_features_category(fm));

        /*
         * Convert the template instantiation domains into categories.
         */
        const auto& pmm(*ctx.logical_context().physical_meta_model());
        const auto tid(pmm.template_instantiation_domains());
        r.categories().push_back(create_variability_domains_category(tid));

        /*
         * Dump data about the physical meta-model.
         */
        r.categories().push_back(create_generation_category(pmm));

        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished dumping specs.";
}

}
