#pragma once
#include <stdafx.h>

namespace SmartCampus { namespace Gui {

	class BuildingItem {
		public:
			explicit BuildingItem(const QList<QVariant> &data, BuildingItem *parent = nullptr);
			~BuildingItem();

			BuildingItem* appendChild(BuildingItem *childItem);

			BuildingItem *  child(uint32_t row);
			uint32_t childCount() const;
			uint32_t columnCount() const;
			QVariant data(uint32_t column) const;
			uint32_t row() const;
			BuildingItem * parentItem();		
			void removeChildren();
		protected:
		private:
			QList<BuildingItem*> m_childItems;
			QList<QVariant> m_itemData;
			BuildingItem *m_parentItem;
	};

}} // SmartCampus::Gui