/*
 *  Copyright (C) 2016-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ContextMenus.h"

#include "FileItem.h"
#include "ServiceBroker.h"
#include "favourites/FavouritesService.h"
#include "favourites/GUIWindowFavourites.h"
#include "utils/URIUtils.h"


namespace CONTEXTMENU
{
  bool CFavouriteContextMenuAction::IsVisible(const CFileItem& item) const
  {
    return URIUtils::IsProtocol(item.GetPath(), "favourites");
  }

  bool CFavouriteContextMenuAction::Execute(const std::shared_ptr<CFileItem>& item) const
  {
    CFileItemList items;
    CServiceBroker::GetFavouritesService().GetAll(items);
    for (const auto& favourite : items)
    {
      if (favourite->GetPath() == item->GetPath())
      {
        if (DoExecute(items, favourite))
          return CServiceBroker::GetFavouritesService().Save(items);
      }
    }
    return false;
  }

  bool CMoveUpFavourite::DoExecute(CFileItemList& items,
                                   const std::shared_ptr<CFileItem>& item) const
  {
    return CGUIWindowFavourites::MoveItem(items, *item, -1);
  }

  bool CMoveUpFavourite::IsVisible(const CFileItem& item) const
  {
    return CFavouriteContextMenuAction::IsVisible(item) &&
           CGUIWindowFavourites::ShouldEnableMoveItems();
  }

  bool CMoveDownFavourite::DoExecute(CFileItemList& items,
                                     const std::shared_ptr<CFileItem>& item) const
  {
    return CGUIWindowFavourites::MoveItem(items, *item, +1);
  }

  bool CMoveDownFavourite::IsVisible(const CFileItem& item) const
  {
    return CFavouriteContextMenuAction::IsVisible(item) &&
           CGUIWindowFavourites::ShouldEnableMoveItems();
  }

  bool CRemoveFavourite::DoExecute(CFileItemList& items,
                                   const std::shared_ptr<CFileItem>& item) const
  {
    int iBefore = items.Size();
    items.Remove(item.get());
    return items.Size() == iBefore - 1;
  }

  bool CRenameFavourite::DoExecute(CFileItemList&, const std::shared_ptr<CFileItem>& item) const
  {
    return CGUIWindowFavourites::ChooseAndSetNewName(*item);
  }

  bool CChooseThumbnailForFavourite::DoExecute(CFileItemList&,
                                               const std::shared_ptr<CFileItem>& item) const
  {
    return CGUIWindowFavourites::ChooseAndSetNewThumbnail(*item);
  }

} // namespace CONTEXTMENU
