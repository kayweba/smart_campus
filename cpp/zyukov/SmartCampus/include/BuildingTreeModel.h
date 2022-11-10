#pragma once
#include <stdafx.h>
#include <QAbstractItemModel>

namespace SmartCampus { namespace Gui {
	class BuildingTreeModel : public QAbstractItemModel {
		public:
			explicit BuildingTreeModel(QObject* parent = nullptr);
			~BuildingTreeModel();

			QVariant data(const QModelIndex& index, int role) const override;
			QVariant data(const QModelIndex& index, int role, int column) const;
			Qt::ItemFlags flags(const QModelIndex& index) const override;
			QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
			QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
			QModelIndex parent(const QModelIndex& index) const override;
			int rowCount(const QModelIndex& parent = QModelIndex()) const override;
			int columnCount(const QModelIndex& parent = QModelIndex()) const override;
			QModelIndex addItem(QVariantList data, const QModelIndex& parent = QModelIndex()) const;
			void redrawData();
		protected:
	
		private:
			BuildingItem* rootItem;
	};
}} // SmartCampus::Gui
