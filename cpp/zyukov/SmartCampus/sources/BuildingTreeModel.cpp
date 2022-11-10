#include <BuildingTreeModel.h>
#include <BuildingTreeItem.h>

namespace SmartCampus { namespace Gui {
	BuildingTreeModel::BuildingTreeModel(QObject* parent)
		: QAbstractItemModel(parent)
	{
		rootItem = new BuildingItem({ QString::fromLocal8Bit("Корпусы") });
	}

	BuildingTreeModel::~BuildingTreeModel()
	{
		delete rootItem;
	}

	QVariant BuildingTreeModel::data(const QModelIndex& index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		if (role != Qt::DisplayRole)
			return QVariant();

		BuildingItem* item = static_cast<BuildingItem*>(index.internalPointer());

		return item->data(index.column());
	}

	QVariant BuildingTreeModel::data(const QModelIndex& index, int role, int column) const
	{
		if (!index.isValid())
			return QVariant();
		if (role != Qt::DisplayRole)
			return QVariant();
		BuildingItem* item = static_cast<BuildingItem*>(index.internalPointer());
		if (column < 0 || column > item->columnCount())
			return QVariant();
		return item->data(column);
	}

	Qt::ItemFlags BuildingTreeModel::flags(const QModelIndex& index) const
	{
		if (!index.isValid())
			return Qt::NoItemFlags;

		return QAbstractItemModel::flags(index);
	}

	QVariant BuildingTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return rootItem->data(section);

		return QVariant();
	}

	QModelIndex BuildingTreeModel::index(int row, int column, const QModelIndex& parent) const
	{
		if (!hasIndex(row, column, parent))
			return QModelIndex();

		BuildingItem* parentItem;

		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<BuildingItem*>(parent.internalPointer());

		BuildingItem* childItem = parentItem->child(row);
		if (childItem)
			return createIndex(row, column, childItem);
		return QModelIndex();
	}

	QModelIndex BuildingTreeModel::parent(const QModelIndex& index) const
	{
		if (!index.isValid())
			return QModelIndex();

		BuildingItem* childItem = static_cast<BuildingItem*>(index.internalPointer());
		BuildingItem* parentItem = childItem->parentItem();

		if (parentItem == rootItem)
			return QModelIndex();

		return createIndex(parentItem->row(), 0, parentItem);
	}

	int BuildingTreeModel::rowCount(const QModelIndex& parent) const
	{
		BuildingItem* parentItem;
		if (parent.column() > 0)
			return 0;

		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<BuildingItem*>(parent.internalPointer());

		return parentItem->childCount();
	}

	int BuildingTreeModel::columnCount(const QModelIndex& parent) const
	{
		if (parent.isValid())
			return static_cast<BuildingItem*>(parent.internalPointer())->columnCount();
		return rootItem->columnCount();
	}

	QModelIndex BuildingTreeModel::addItem(QVariantList data, const QModelIndex& parent) const
	{
		BuildingItem* lastAddedItem;
		if (parent.isValid()) {
			BuildingItem* ptrParent = static_cast<BuildingItem*>(parent.internalPointer());
			lastAddedItem = ptrParent->appendChild(new BuildingItem(data, ptrParent));
		}
		else {
			lastAddedItem = rootItem->appendChild(new BuildingItem(data, rootItem));
		}
		return createIndex(lastAddedItem->row(), 0, lastAddedItem);
	}

	void BuildingTreeModel::redrawData()
	{
		beginResetModel();
		rootItem->removeChildren();
		endResetModel();
	}

}} // SmartCampus::Gui