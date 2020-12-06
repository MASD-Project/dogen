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
#ifndef DOGEN_TEXT_CSHARP_TYPES_MODEL_TO_TEXT_CSHARP_CHAIN_HPP
#define DOGEN_TEXT_CSHARP_TYPES_MODEL_TO_TEXT_CSHARP_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.text/types/entities/model.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.text/types/transforms/model_to_text_technical_space_chain.hpp"
#include "dogen.text.csharp/types/transforms/repository.hpp"

namespace dogen::text::csharp {

/**
 * @brief Manages the c# backend.
 */
class model_to_text_csharp_chain final
    : public text::transforms::model_to_text_technical_space_chain {
public:
    model_to_text_csharp_chain() = default;
    model_to_text_csharp_chain(
        const model_to_text_csharp_chain&) = delete;
    model_to_text_csharp_chain(
        model_to_text_csharp_chain&&) = default;

public:
    ~model_to_text_csharp_chain() noexcept;

private:
    void apply(const text::transforms::context& ctx,
        text::entities::model& fm) const;

public:
    std::string description() const override;
    identification::entities::physical_meta_id id() const override;

public:
    identification::entities::technical_space technical_space() const override;

    void apply(const text::transforms::context& ctx,
        const bool enable_backend_directories,
        text::entities::model& m) const override;
};

}

#endif
