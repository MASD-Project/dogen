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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_CODE_GENERATION_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_CODE_GENERATION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/transforms/kernel_registrar.hpp"
#include "dogen/yarn/types/transforms/configuration.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"
#include "dogen/yarn/types/transforms/code_generation_output.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class code_generation_chain final {
private:
    struct type_group {
        annotations::type enable_kernel_directories;
        std::list<annotations::type> enabled;
    };

    static type_group make_type_group(const annotations::type_repository& atrp,
        const std::list<annotations::archetype_location>& als);

    static std::unordered_set<std::string> obtain_enabled_kernels(
        const type_group& tg, const annotations::annotation& ra);

    static bool obtain_enable_kernel_directories(const type_group& tg,
        const annotations::annotation& ra);

    static configuration make_configuration(const context& ctx,
        const std::list<annotations::archetype_location>& als,
        const annotations::annotation& ra);

public:
    /**
     * @brief Registrar that keeps track of the available kernels.
     */
    static kernel_registrar& registrar();

private:
    /**
     * @brief Checks that the supplied path is absolute.
     *
     * We expect the output directory to be absolute. This just makes
     * our life easier in terms of assumptions. Note that this does
     * not mean the end user must supply an absolute path, just that
     * someone above must have ensured they converted it into
     * absolute.
     */
    static void ensure_output_directory_path_is_absolute(
        const boost::filesystem::path& p);

    /**
     * @brief Create the decoration configuration factory.
     */
    static dogen::formatters::decoration_properties_factory
    create_decoration_properties_factory(
        const context& ctx,
        const annotations::annotation& ra);

    /**
     * @brief Returns all of the available archetype locations across
     * all kernels.
     */
    static std::list<annotations::archetype_location>
    archetype_locations();

public:
    static code_generation_output
    transform(const context& ctx, const std::list<meta_model::model>& models);

private:
    static std::shared_ptr<kernel_registrar> registrar_;
};

/*
 * Helper method to register kernels.
 */
template<typename Kernel>
inline void register_kernels() {
    auto k(std::make_shared<Kernel>());
    auto& rg(code_generation_chain::registrar());
    rg.register_kernel(k);
}

} } }

#endif
