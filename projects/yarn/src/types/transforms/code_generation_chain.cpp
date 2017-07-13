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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.code_generation_chain"));

const std::string non_absolute_output(
    "The output directory path is not absolute: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

std::shared_ptr<kernel_registrar> code_generation_chain::registrar_;

kernel_registrar& code_generation_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<kernel_registrar>();

    return *registrar_;
}

void code_generation_chain::ensure_output_directory_path_is_absolute(
    const boost::filesystem::path& p) {
    if (!p.is_absolute()) {
        const auto gs(p.generic_string());
        BOOST_LOG_SEV(lg, error) << non_absolute_output << gs;
        BOOST_THROW_EXCEPTION(transformation_error(non_absolute_output + gs));
    }
}

dogen::formatters::decoration_properties_factory
code_generation_chain::create_decoration_properties_factory(
    const context& ctx, const annotations::annotation& ra) {
    using dogen::formatters::decoration_properties_factory;
    decoration_properties_factory r(ctx.type_repository(),
        ctx.formatters_repository(), ra);
    return r;
}

void code_generation_chain::
transform(const context& ctx, meta_model::model& /*m*/) {
    const auto& odp(ctx.options().output_directory_path());
    ensure_output_directory_path_is_absolute(odp);


}

} } }
