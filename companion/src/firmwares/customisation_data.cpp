/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "customisation_data.h"

// cannot use QColor so use formula from libopenui_defines.h
#define RADIO_RGB(r, g, b) \
  (uint16_t)((((r)&0xF8) << 8) + (((g)&0xFC) << 3) + (((b)&0xF8) >> 3))
#define WHITE RADIO_RGB(0xFF, 0xFF, 0xFF)
#define RED RADIO_RGB(229, 32, 30)

inline void setZoneOptionValue(ZoneOptionValue& zov, bool value)
{
  zov.boolValue = value;
}

inline void setZoneOptionValue(ZoneOptionValue& zov, int value)
{
  zov.signedValue = value;
}

inline void setZoneOptionValue(ZoneOptionValue& zov, char value)
{
  memset(&zov.stringValue, value, LEN_ZONE_OPTION_STRING);
}

inline void setZoneOptionValue(ZoneOptionValue& zov, unsigned int value)
{
  zov.unsignedValue = value;
}

inline ZoneOptionValueEnum zoneValueEnumFromType(ZoneOption::Type type)
{
  switch(type) {
  case ZoneOption::File:
  case ZoneOption::String:
    return ZOV_String;

  case ZoneOption::Integer:
    return ZOV_Signed;

  case ZoneOption::Bool:
    return ZOV_Bool;

  case ZoneOption::Color:
  case ZoneOption::Timer:
  case ZoneOption::Switch:
  case ZoneOption::Source:
  case ZoneOption::TextSize:
  default:
    return ZOV_Unsigned;
  }
}

inline const char * zoneOptionValueEnumToString(ZoneOptionValueEnum zovenum) {
  switch (zovenum) {
    case ZOV_Unsigned:
      return "unsigned";
    case ZOV_Signed:
      return "signed";
    case ZOV_Bool:
      return "bool";
    case ZOV_String:
      return "string";
    default:
      return "unknown";
  }
}

void RadioTheme::init(const char* themeName, ThemeData& themeData)
{
  memset(&themeData, 0, sizeof(ThemeData));

  memcpy(&themeData.themeName, themeName, THEME_NAME_LEN);

  PersistentData& persistentData = themeData.themePersistentData;

  persistentData.options[0].type =
      zoneValueEnumFromType(ZoneOption::Type::Color);
  setZoneOptionValue(persistentData.options[0].value, (unsigned int)WHITE);

  persistentData.options[1].type =
      zoneValueEnumFromType(ZoneOption::Type::Color);
  setZoneOptionValue(persistentData.options[1].value, (unsigned int)RED);
}

void RadioLayout::init(const char* layoutId, CustomScreens& customScreens)
{
  memset(&customScreens, 0, sizeof(CustomScreens));

  for (int i = 0; i < MAX_CUSTOM_SCREENS; i++) {
    if (i == 0)
      memcpy(&customScreens.customScreenData[i].layoutId, layoutId,
             LAYOUT_ID_LEN);

    LayoutPersistentData& persistentData =
        customScreens.customScreenData[i].layoutPersistentData;

    int j = 0;
    persistentData.options[j].type =
        zoneValueEnumFromType(ZoneOption::Type::Bool);
    setZoneOptionValue(persistentData.options[j++].value, (bool)true);

    persistentData.options[j].type =
        zoneValueEnumFromType(ZoneOption::Type::Bool);
    setZoneOptionValue(persistentData.options[j++].value, (bool)true);

    persistentData.options[j].type =
        zoneValueEnumFromType(ZoneOption::Type::Bool);
    setZoneOptionValue(persistentData.options[j++].value, (bool)true);

    persistentData.options[j].type =
        zoneValueEnumFromType(ZoneOption::Type::Bool);
    setZoneOptionValue(persistentData.options[j++].value, (bool)true);

    persistentData.options[j].type =
        zoneValueEnumFromType(ZoneOption::Type::Bool);
    setZoneOptionValue(persistentData.options[j++].value, (bool)false);
  }
}
