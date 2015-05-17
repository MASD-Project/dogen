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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/io/formattables/enablement_repository_io.hpp"
#include "dogen/cpp/types/formattables/enablement_factory.hpp"
#include "dogen/cpp/types/formattables/enablement_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.enablement_repository_factory"));

const std::string duplicate_qname("Duplicate qname: ");
const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all inclusion dependencies.
 */
class generator final {
public:
    explicit generator(const enablement_factory& f) : factory_(f) {}

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename SmlEntity>
    void generate(const SmlEntity& e) {
        result_.enablement_by_qname()[e.name()] = factory_.make(e.extensions());
    }

public:
    void operator()(const dogen::sml::object& o) { generate(o); }
    void operator()(const dogen::sml::enumeration& e) { generate(e); }
    void operator()(const dogen::sml::primitive& p) { generate(p); }
    void operator()(const dogen::sml::module& m) { generate(m); }
    void operator()(const dogen::sml::concept& c) { generate(c); }

public:
    const enablement_repository& result() const { return result_; }

private:
    const enablement_factory& factory_;
    enablement_repository result_;
};

}

std::unordered_map<std::string,
                   enablement_repository_factory::field_definitions>
enablement_repository_factory::create_field_definitions(
    const dynamic::repository& rp,
    const formatters::container& fc) const {
    const dynamic::repository_selector s(rp);
    std::unordered_map<std::string, field_definitions> r;
    for (const auto& f : fc.all_formatters()) {
        const auto oh(f->ownership_hierarchy());

        field_definitions fd;
        const auto& mn(oh.model_name());
        fd.model_enabled = s.select_field_by_name(mn, traits::enabled());

        const auto& fctn(oh.facet_name());
        fd.facet_enabled = s.select_field_by_name(fctn, traits::enabled());

        const auto& fn(oh.formatter_name());
        fd.formatter_enabled = s.select_field_by_name(fn, traits::enabled());

        r[fn] = fd;
    }

    return r;
}


std::unordered_map<std::string, global_enablement_properties>
enablement_repository_factory::obtain_global_properties(
    const std::unordered_map<std::string, field_definitions>& field_definitions,
    const dynamic::object& root_object) const {
    std::unordered_map<std::string, global_enablement_properties> r;
    const dynamic::field_selector fs(root_object);
    for (const auto& pair : field_definitions) {
        const auto& fn(pair.first);
        const auto& fd(pair.second);

        global_enablement_properties gep;
        gep.model_enabled(fs.get_boolean_content_or_default(fd.model_enabled));
        gep.facet_enabled(fs.get_boolean_content_or_default(fd.facet_enabled));
        gep.formatter_enabled(
            fs.get_boolean_content_or_default(fd.formatter_enabled));

        r[fn] = gep;
    }
    return r;
}

enablement_repository enablement_repository_factory::make(
    const dynamic::repository& rp,
    const dynamic::object& root_object,
    const formatters::container& fc,
    const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started computing enablement.";

    const auto fd(create_field_definitions(rp, fc));
    const auto gep(obtain_global_properties(fd, root_object));
    const enablement_factory f(rp, fc, gep);
    generator g(f);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished computing enablement:" << g.result();
    return g.result();
}

} } }
