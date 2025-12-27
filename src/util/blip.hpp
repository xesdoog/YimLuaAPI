/**
 * @file blip.hpp
 * @brief Map blip related functions.
 */

#pragma once

namespace big::blip
{
	/**
	 * @brief Searches for blips based on the sprite and color provided.
	 * 
	 * @param location Blip location output.
	 * @param sprite Blip sprite to search for.
	 * @param color Color to search for, use -1 to ignore color search.
	 * @return True if blip exists, otherwise returns false.
	 */
	bool get_blip_location(Vector3& location, int sprite, int color = -1);

	bool get_blip_location_from_offset(Vector3& location, int sprite);
}