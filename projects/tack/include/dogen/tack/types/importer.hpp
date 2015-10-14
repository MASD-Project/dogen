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
#ifndef DOGEN_TACK_TYPES_IMPORTER_HPP
#define DOGEN_TACK_TYPES_IMPORTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <boost/optional.hpp>
#include "dogen/tack/types/model.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/tack/types/file_importer_registrar.hpp"
#include "dogen/tack/types/file_importer_interface.hpp"
#include "dogen/tack/types/input_descriptor.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Manages the entire importing workflow.
 */
class importer {
public:
    explicit importer(const dynamic::repository& rp);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static file_importer_registrar& registrar();

private:
    /**
     * @brief Given an input descriptor, creates the associated model.
     */
    tack::model import_model(const input_descriptor& d) const;

public:
    /**
     * @brief Process all of the inputs into models, using the
     * appropriate file importers.
     */
    std::list<tack::model>
    import(const std::list<input_descriptor>& descriptors);

private:
    static std::shared_ptr<file_importer_registrar> registrar_;
    const dynamic::repository& repository_;
    const dynamic::workflow dynamic_workflow_;
};

template<typename FileImporter>
inline void register_file_importer() {
    auto s(std::make_shared<FileImporter>());
    for (const auto& se : s->supported_extensions())
        importer::registrar().register_file_importer_for_extension(se, s);
}

} }

#endif
