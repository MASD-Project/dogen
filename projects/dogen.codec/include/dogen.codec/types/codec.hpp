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
#ifndef DOGEN_CODEC_TYPES_CODEC_HPP
#define DOGEN_CODEC_TYPES_CODEC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Provides support for encoding and decoding of external models.
 *
 * An external model is defined as:
 *
 * - a third-party format that is not owned or controlled by Dogen, such as Dia or
 *   org-mode.
 * - a Dogen format designed for interoperability (JSON).
 *
 * External models are converted into an intermediate format called the @e codec
 * model, because it is the original entry point into the dogen processing
 * pipeline. It also reflects the notion that we are injecting external technical
 * spaces into the MASD technical technical space.
 *
 * A codec must be created for each external model that is to be injected,
 * providing a transformation between the native formats and the codec model. The
 * codecs are created as transforms in the present model, and should reuse common
 * infrastructure where possible. There should also be a "native" model
 * representing the original codec format as much as possible (e.g. "dogen.dia").
 * The idea for those models is just to provide a faithful representation of the
 * native codec domain model (though it may not necessarily be complete).
 *
 * In general, codecs use file extensions to determine the type of the codec.
 *
 * UML representation:
 *
 * \image html dogen.codec/modeling/dogen.codec.svg
 */
namespace dogen::codec {
}

#endif
