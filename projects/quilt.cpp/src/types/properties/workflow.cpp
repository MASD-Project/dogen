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
#include <memory>
#include <algorithm>
#include <forward_list>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/memory_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings_factory.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository_factory.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/factory.hpp"
#include "dogen/quilt.cpp/types/properties/transformer.hpp"
#include "dogen/quilt.cpp/io/properties/formattable_io.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/element_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.properties.workflow"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

namespace {

/**
 * @brief Generates the properties.
 */
class generator final : public yarn::element_visitor {
public:
    explicit generator(const transformer& t) : transformer_(t) { }

private:
    template<typename Transformable>
    void transform(const Transformable& t) {
        if (t.generation_type() != yarn::generation_types::no_generation) {
            auto f(transformer_.transform(t));
            result_.splice_after(result_.before_begin(), f);
        }
    }

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::visitor& v) { transform(v); }
    void visit(const dogen::yarn::enumeration& e) { transform(e); }
    void visit(const dogen::yarn::object& o) { transform(o); }
    void visit(const dogen::yarn::exception& e) { transform(e); }

public:
    const std::forward_list<std::shared_ptr<properties::formattable> >&
    result() { return result_; }

private:
    std::forward_list<std::shared_ptr<properties::formattable> > result_;
    const transformer& transformer_;
};

}

std::unordered_map<std::string, settings::path_settings>
workflow::create_path_settings_activity(const dynamic::repository& drp,
    const dynamic::object& root_object,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating path settings for root object.";
    settings::path_settings_factory f(drp, fc.all_external_file_formatters());
    const auto r(f.make(root_object));
    BOOST_LOG_SEV(lg, debug) << "Created path settings for root object.";
    return r;
}

settings::helper_settings_repository workflow::
create_helper_settings_repository(const dynamic::repository& drp,
    const yarn::model& m) const {
    settings::helper_settings_repository_factory f;
    return f.make(drp, m);
}

settings::aspect_settings_repository
workflow::create_aspect_settings_repository(
    const dynamic::repository& drp, const yarn::model& m) const {
    settings::aspect_settings_repository_factory f;
    return f.make(drp, m);
}

path_derivatives_repository workflow::
create_path_derivatives_repository(const config::cpp_options& opts,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const yarn::model& m) const {
    path_derivatives_repository_factory f;
    return f.make(opts, ps, m);
}

formatter_properties_repository workflow::
create_formatter_properties(const dynamic::repository& drp,
    const dynamic::object& root_object,
    const path_derivatives_repository& pdrp,
    const formatters::container& fc,
    const yarn::model& m) const {

    formatter_properties_repository_factory f;
    return f.make(drp, root_object, pdrp, fc, m);
}

std::forward_list<std::shared_ptr<properties::formattable> >
workflow::from_transformer_activity(const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming properties.";

    transformer t;
    generator g(t);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        e.accept(g);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming properties.";
    return g.result();
}

std::forward_list<std::shared_ptr<properties::formattable> >
workflow::from_factory_activity(const config::cpp_options& opts,
    const dogen::formatters::file_properties_workflow& fpwf,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    formatter_properties_repository& fprp,
    const yarn::model& m) const {

    std::forward_list<std::shared_ptr<properties::formattable> > r;
    factory f;

    r.splice_after(r.before_begin(),
        f.make_cmakelists(opts, fpwf, ps, fprp, m));

    const auto oi(f.make_odb_options(opts, fpwf, ps, fprp, m));
    if (oi)
        r.push_front(oi);

    BOOST_LOG_SEV(lg, debug) << "Factory properties: " << r;
    return r;
}

element_properties_repository workflow::create_element_properties_repository(
    const dogen::formatters::file_properties_workflow& fpwf,
    const settings::helper_settings_repository& hsrp,
    const settings::aspect_settings_repository& asrp,
    const settings::streaming_settings_repository& ssrp,
    const formatters::container& fc,
    const formatter_properties_repository& fprp,
    const yarn::model& m) const {
    element_properties_repository_factory f;
    return f.make(fpwf, hsrp, asrp, ssrp, fc, fprp, m);
}

std::pair<
    element_properties_repository,
    std::forward_list<std::shared_ptr<properties::formattable> >
>
workflow::execute(const config::cpp_options& opts,
    const dynamic::repository& drp,
    const dynamic::object& root_object,
    const dogen::formatters::file_properties_workflow& fpwf,
    const formatters::container& fc,
    const settings::streaming_settings_repository& ssrp,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started creating properties.";

    const auto& ro(root_object);
    const auto ps(create_path_settings_activity(drp, ro, fc));
    const auto pdrp(create_path_derivatives_repository(opts, ps, m));
    auto fprp(create_formatter_properties(drp, ro, pdrp, fc, m));

    auto formattables(from_transformer_activity(m));
    formattables.splice_after(formattables.before_begin(),
        from_factory_activity(opts, fpwf, ps, fprp, m));
    BOOST_LOG_SEV(lg, debug) << "Formattables: " << formattables;

    BOOST_LOG_SEV(lg, debug) << "Finished creating formattables.";

    const auto hsrp(create_helper_settings_repository(drp, m));
    const auto asrp(create_aspect_settings_repository(drp, m));
    const auto eprp(create_element_properties_repository(
            fpwf, hsrp, asrp, ssrp, fc, fprp, m));
    return std::make_pair(eprp, formattables);
}

} } } }
