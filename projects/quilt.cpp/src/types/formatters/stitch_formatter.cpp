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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/stitch_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formatters.stitch_formatter"));

const std::string stitch_extension(".stitch");

const std::string empty;
const std::string ist_not_supported("not_supported");
const std::string ist_regular_support("regular_support");
const std::string ist_canonical_support("canonical_support");
const std::string unsupported_type("Inclusion support type is not supported.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class element_name_generator : public yarn::element_visitor {
public:
    const std::string result() { return element_name_; }

public:
    using yarn::element_visitor::visit;
    void visit(const yarn::object&) override { element_name_ = "object"; }
    void visit(const yarn::primitive&) override { element_name_ = "primitive"; }
    void visit(const yarn::module&) override { element_name_ = "module"; }
    void visit(const yarn::concept&) override { element_name_ = "concept"; }
    void visit(const yarn::visitor&) override { element_name_ = "visitor"; }
    void visit(const yarn::exception&) override { element_name_ = "exception"; }
    void visit(const yarn::enumeration&) override {
        element_name_ = "enumeration";
    }

private:
    std::string element_name_;
};

stitch_formatter::stitch_formatter(const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& af,
    const dogen::formatters::repository& frp)
    : instantiator_(atrp, af, frp) {}


std::string
stitch_formatter::to_string(const inclusion_support_types ist) const {
    switch (ist) {
    case inclusion_support_types::not_supported:
        return ist_not_supported;
    case inclusion_support_types::regular_support:
        return ist_regular_support;
    case inclusion_support_types::canonical_support:
        return ist_canonical_support;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_type;
        BOOST_THROW_EXCEPTION(formatting_error(unsupported_type));
    }
}

bool stitch_formatter::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

dogen::formatters::artefact stitch_formatter::
format(const artefact_formatter_interface& stock_formatter, const context& ctx,
    const yarn::element& e, const bool generate_wale_kvps) const {
    const auto al(stock_formatter.archetype_location());
    const auto needs_guard(is_header(stock_formatter.inclusion_support_type()));
    const auto id(e.name().id());

    assistant a(ctx, al, needs_guard, id);
    std::unordered_map<std::string, std::string> wale_kvps;
    if (generate_wale_kvps) {
        const auto sn(e.name().simple());
        const auto ist(to_string(stock_formatter.inclusion_support_type()));
        element_name_generator g;
        e.accept(g);
        const auto ye(g.result());

        auto asn(al.archetype());
        boost::replace_first(asn, al.facet(), empty);

        wale_kvps = std::unordered_map<std::string, std::string> {
            { "class.simple_name", sn },
            { "class.inclusion_support_type", ist },
            { "yarn_element", ye },
            { "archetype.simple_name", asn }
        };
    }

    const auto& fp(a.artefact_properties().file_path());
    boost::filesystem::path stitch_template(fp);
    stitch_template.replace_extension(stitch_extension);

    auto r(instantiator_.instantiate(stitch_template, wale_kvps));
    r.overwrite(a.artefact_properties().overwrite());
    return r;
}

} } } }
