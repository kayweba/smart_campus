#include <BuildingTreeItem.h>

namespace SmartCampus { namespace Gui {
	BuildingItem::BuildingItem(const QList<QVariant>& data, BuildingItem* parent)
		:m_itemData(data), m_parentItem(parent)
	{}

	BuildingItem::~BuildingItem()
	{
		qDeleteAll(m_childItems);
	}

	BuildingItem* BuildingItem::appendChild(BuildingItem* childItem)
	{
		m_childItems.append(childItem);
		return m_childItems.last();
	}

	BuildingItem* BuildingItem::child(uint32_t row)
	{
		if (row >= (uint32_t) m_childItems.size())
			return nullptr;
		return m_childItems.at(row);
	}

	uint32_t BuildingItem::childCount() const
	{
		return m_childItems.count();
	}

	uint32_t BuildingItem::row() const
	{
		if (m_parentItem)
			return m_parentItem->m_childItems.indexOf(const_cast<BuildingItem*>(this));
		return 0;
	}

	int BuildingItem::columnCount() const
	{
		return m_itemData.count();
	}

	QVariant BuildingItem::data(uint32_t column) const
	{
		if (column >= (uint32_t) m_itemData.size())
			return QVariant();
		return m_itemData.at(column);
	}

	BuildingItem* BuildingItem::parentItem()
	{
		return m_parentItem;
	}

	void BuildingItem::removeChildren()
	{
		m_childItems.clear();
	}
}} // SmartCampus::Gui