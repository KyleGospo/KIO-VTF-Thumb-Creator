/**
 * Copyright (C) 2014 Mathias Panzenböck
 * Copyright Andrew Betson.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <kio/thumbcreator.h>

class CVTFThumbCreator : public ThumbCreator
{
public:
	bool create( const QString &szPath, int nWidth, int nHeight, QImage &Image ) override;
	Flags flags() const override
	{
		return None;
	}

};
