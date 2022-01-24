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

#include "VTFThumbCreator.h"

#include <QString>
#include <QImage>

#include <VTFFile.h>
#include <VTFLib.h>

bool CVTFThumbCreator::create( const QString &szPath, int nWidth, int nHeight, QImage &Image )
{
	if ( nWidth <= 0 || nHeight <= 0 )
	{
		return false;
	}

	VTFLib::CVTFFile File;

	if ( !File.Load( szPath.toLocal8Bit().constData() ) )
	{
		qDebug( "%s", VTFLib::LastError.Get() );
		return false;
	}

	const vlByte *pnFrame = 0;
	VTFImageFormat eSrcFormat;

	vlUInt uThumbnailWidth = File.GetThumbnailWidth();
	vlUInt uThumbnailHeight = File.GetThumbnailHeight();
	vlUInt uThumbnailDepth = File.GetDepth();

	if ( File.GetHasThumbnail() && ( uThumbnailWidth >= ( vlUInt )nWidth || uThumbnailHeight >= ( vlUInt )nHeight ) )
	{
		// VTF has a thumbnail; get its image data.

		eSrcFormat = File.GetThumbnailFormat();
		pnFrame = File.GetThumbnailData();
	}
	else
	{
		// VTF doesn't have a thumbnail; get the best fitting mipmaps image data.

		eSrcFormat = File.GetFormat();

		uThumbnailWidth = File.GetWidth();
		uThumbnailHeight = File.GetHeight();

		vlUInt uMipLevel = File.GetMipmapCount() - 1;
		vlUInt uMipWidth = 0;
		vlUInt uMipHeight = 0;
		vlUInt uMipDepth = 0;

		while ( uMipLevel > 0 )
		{
			VTFLib::CVTFFile::ComputeMipmapDimensions(
				uThumbnailWidth, uThumbnailHeight, uThumbnailDepth,
				uMipLevel,
				uMipWidth, uMipHeight, uMipDepth
			);

			if ( uMipWidth >= ( vlUInt )nWidth || uMipHeight >= ( vlUInt )nHeight )
			{
				uThumbnailWidth = uMipWidth;
				uThumbnailHeight = uMipHeight;
				uThumbnailDepth = uMipDepth;
				break;
			}
			uMipLevel--;
		}

		pnFrame = File.GetData( File.GetFrameCount() - 1, 0, 0, uMipLevel );
	}

	if ( !pnFrame )
	{
		return false;
	}

	QImage::Format qFormat;
	VTFImageFormat eDstFormat;
	if ( VTFLib::CVTFFile::GetImageFormatInfo( eSrcFormat ).uiAlphaBitsPerPixel > 0 )
	{
		qFormat = QImage::Format_ARGB32;
		eDstFormat = IMAGE_FORMAT_RGBA8888;
	}
	else
	{
		qFormat = QImage::Format_RGB888;
		eDstFormat = IMAGE_FORMAT_RGB888;
	}

	// Ensure the image has the requested dimensions.
	if ( ( vlUInt )Image.width() != ( vlUInt )uThumbnailWidth || ( vlUInt )Image.height() != ( vlUInt )uThumbnailHeight || Image.format() != qFormat )
	{
		Image = QImage( uThumbnailWidth, uThumbnailHeight, qFormat );
		if ( Image.isNull() )
		{
			return false;
		}
	}

	uchar *puBits = Image.bits();
	if ( !VTFLib::CVTFFile::Convert( pnFrame, puBits, uThumbnailWidth, uThumbnailHeight, eSrcFormat, eDstFormat ) )
	{
		qDebug( "%s", VTFLib::LastError.Get() );
		return false;
	}

	// HACK: Swap channels around to get around a bug somewhere in the library chain.
	if ( eDstFormat == IMAGE_FORMAT_RGBA8888 )
	{
		for ( size_t uIdx = 0, uPixelIdx = uThumbnailWidth * uThumbnailHeight * 4; uIdx < uPixelIdx; uIdx += 4 )
		{
			uchar uBlue = puBits[ uIdx + 0 ];
			uchar uRed = puBits[ uIdx + 2 ];

			puBits[ uIdx + 0 ] = uRed;
			puBits[ uIdx + 2 ] = uBlue;
		}
	}

	return true;
}

extern "C"
{
	Q_DECL_EXPORT ThumbCreator *new_creator()
	{
		return new CVTFThumbCreator();
	}
};
