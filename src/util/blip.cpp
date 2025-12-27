#include "blip.hpp"
#include "natives.hpp"

namespace big::blip
{
	bool get_blip_location(Vector3& location, int sprite, int color)
	{
		Blip blip;
		for (blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite); HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color; blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite))
			;

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color))
			return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}

	bool get_blip_location_from_offset(Vector3& location, int sprite)
	{
		Blip blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite);
		if (HUD::DOES_BLIP_EXIST(blip))
		{
			location = HUD::GET_BLIP_COORDS(blip);
			return true;
		}
		return false;
	}
}